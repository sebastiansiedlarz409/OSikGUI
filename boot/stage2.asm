[bits 16]
[org 0x0000]                            ;I choose to load stage2 to 0x10000
                                        ;check "Real mode address space" -> https://wiki.osdev.org/Memory_Map_(x86)

start:
    ;enable line A20
    ;https://wiki.osdev.org/A20_Line
    mov ax, 0x2401
    int 0x15
    in al, 0x92
    or al, 2
    out 0x92, al

    cli

    mov ax, 0x1000
    mov ds, ax                          ;set data segment address
    mov es, ax                          ;set extra segment address

    mov ax, 0x0f00                      
    mov ss, ax                          ;set stack segment address
    mov sp, 0                           ;0 to stack pointer register

    lgdt [GDT_ADR32]                    ;loads GDT to GDTR GDT register
                                        ;intel manual 2A -> page 663

    mov eax, cr0                        ;set processor flag
    or al, 1                            ;set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov cr0, eax                        ;protected mode = 32 bits, real = 16 bits
                                        ;CR0 — Contains system control flags that control operating mode and states of the processor
                                        ;intel 3A -> page 76
                                        ;https://wiki.osdev.org/Protected_Mode

    ;0x8 is code segment id
    ;intel 3A - page 95
    ;jmp actualy switch modes
    ;we moved to 32 bits addresses
    jmp dword 0x8:(0x10000+stage32)

stage32:
    [bits 32]
    mov ax, 0x10                        ;0x10 is data segment id from GDT below
    mov ds, ax
    mov es, ax
    mov ss, ax

    ;here we display sign, we will know that execution arrives here
    lea eax, [0xb8000]                  ;lea toggele big/little endian, 0xb8000 is address in video ram
    mov word [eax+160*18], 0x0133       ;byte for colors, byte for char
    mov word [eax+160*18+2], 0x0132     ;https://pl.wikipedia.org/wiki/Color_Graphics_Adapter
    mov word [eax+160*18+4], 0x0162     ;one line = 160 bytes
    mov word [eax+160*18+6], 0x0169     ;we moved to line 18
    mov word [eax+160*18+8], 0x0174
    mov word [eax+160*18+10], 0x0120
    mov word [eax+160*18+12], 0x016f
    mov word [eax+160*18+14], 0x016b

    mov eax, (PML4 - $$) + 0x10000      ;move main paging table address to cr3
    mov cr3, eax                        ;Intel 3A -> page 75

    mov eax, cr4                        ;Intel 3A -> page 79
    or eax, (1 << 5)                    ;CR4.PAE must be set before enter to long mode
    mov cr4, eax

    mov ecx, 0xC0000080                 ;set the long mode bit in the EFER MSR
    rdmsr                               ;https://en.wikipedia.org/wiki/Control_register#EFER
    or eax, (1 << 8)                    ;set 8 bit
    wrmsr                               ;enable IE-32e operation
                                        ;Intel 3A -> page 71

    mov eax, cr0                        ;enable paging in 32 bit mode
    or eax, (1 << 31)                   ;Intel 3A -> page 76
    mov cr0, eax

    lgdt [GDT_ADR64 + 0x10000]          ;reload GDT for 64 bits

    ;0x8 is code segment id
    ;intel 3A - page 95
    ;jmp actualy switch modes
    ;we moved to 32 bits addresses
    jmp dword 0x8:(0x10000+stage64)

stage64:
    [bits 64]
    mov ax, 0x10                        ;0x10 is data segment id from GDT below
    mov ds, ax
    mov es, ax
    mov ss, ax
    
    ;here we display sign, we will know that execution arrives here
    mov rax, 0xb8000
    mov word [rax+160*19], 0x0E36
    mov word [rax+160*19+2], 0x0E34
    mov word [rax+160*19+4], 0x0E62
    mov word [rax+160*19+6], 0x0E69
    mov word [rax+160*19+8], 0x0E74
    mov word [rax+160*19+10], 0x0E20
    mov word [rax+160*19+12], 0x0E6f
    mov word [rax+160*19+14], 0x0E6b

loader:
    ;PE FILE STRUCTURE
    ;https://raw.githubusercontent.com/corkami/pics/master/binary/PE101.png
    ;https://wiki.osdev.org/PE

    ;extract offset of PE header 4byte value e_lfanew
    ;we skip MZ part
    mov esi, [0x10000 + kernel64 + 0x3C]                    ;in rsi we have PE Header in file
    add esi, 0x10000 + kernel64                             ;we add to this offset memory offset

    ;section count 1 byte value NumberOfSections
    xor rcx, rcx
    mov cx, [esi + 0x6]                                     ;how many section is in PE file
    
    ;extract entry point 4 byte value AddressOfEntryPoint
    mov ebx, [esi + 0x28]

    ;ImageBase
    ;mov r11, [esi + 0x30]
    mov r11, 0x400000

    ;offset of first section in table
    add esi, 0x108

    cld                                                     ;clear direction flag

    .ph_loop:

    mov r8d, [rsi + 0x8]                                    ;size of segment in memory
    mov r13d, [rsi + 0x10]                                  ;size of segment in file
    mov r9d, [rsi + 0xC]                                    ;vaddr where it should be copied
    add r9, r11                                             ;add 0x400000
    mov r10d, [rsi + 0x14]                                  ;section offset in file

    ;backup registers
    mov r14, rsi
    mov r15, rcx

    ;clear destination memory
    mov rdi, r9
    mov rcx, r8
    xor al, al
    rep stosb

    ;copy sections
    lea rsi, [0x10000 + kernel64 + r10d]                    ;what should be copied, remember to add offset in image
    mov rdi, r9                                             ;where it should be copied in memory
    mov rcx, r13                                            ;how many bytes copy
    rep movsb                                               ;execute copy

    ;restor registers
    mov rsi, r14
    mov rcx, r15
    
    ;next iteration
    add rsi, 0x28                                           ;next section is 40 bytes further
    loop .ph_loop

    ;place stack in memory
    lea rsp, [0x3ff000]
    
    ;args to _start
    ;page 10 -> https://www.agner.org/optimize/calling_conventions.pdf
    lea rcx, [ebx + r11d]                                   ;first argument
    mov rdx, rsp                                            ;second argument

    lea rax, [ebx + r11d]                                   ;jump to entry point, _start in kernel
    call rax

    jmp $

;https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html
;intel manuals 3
;segment selector (16-bit identifier for a segment) -> page 95

;GLOBAL DESCRIPTOR TABLE 32-BIT
GDT32:

; Null segment
dd 0, 0

; Code segment -> page 97
dd 0xffff                                   ;lower 16 bits from base address, lower 16 bits from segment limit
;BA - bits [7:0] - bits[16:23] from base address
;Type - bits [11:8] - read/execution -> 0b1010 -> Table 3.1 page 100
;S - bit 12 - the segment descriptor is for a system segment (S flag is clear) or a code or data segment (S flag is set)
;DPL - bits[14:13] - DPL (descriptor privilege level) field specifies the privilege level of the segment -> 0 to 3
;P - bit 15 - indicates whether the segment is present in memory (set) or not present (clear)
;SegLimit - bits [19:16] - its bits [19:16] from 20 bits segment limit
;AVL - bit 20 - Available for use by system software
;L - bit 21 - 1 64 bit segment, 0 no 64 bits segment
;D/B - bit 22 - 0 16 bi segment, 1 32 bits segment
;G - bit 23 - Granularity -  granularity flag is clear, the segment limit is interpreted in byte units; when flag is set, the segment limit is interpreted in 4-KByte units.
;BA - bits [31:24] - bits[24:31] from base address
dd (10 << 8) | (1 << 12) | (1 << 15) | (15 << 16) | (1 << 22) | (1 << 23)

; Data segment
dd 0xffff
dd (2 << 8) | (1 << 12) | (1 << 15) | (15 << 16) | (1 << 22) | (1 << 23)

; Its helpfull when number of segment is multiply of 2
dd 0, 0

GDT_END32:

;this is GDT address structure for lgdt instruction
;intel manuals 2A -> page 663
;2Bytes limit/size, 4Bytes Address
GDT_ADR32:
dw (GDT_END32 - GDT32) - 1                  ;size of GDT above as 2Bytes
dd 0x10000 + GDT32                          ;16 bit mode address GDT
times (32 - ($ - $$) % 32) dd 0xcc

;GLOBAL DESCRIPTOR TABLE 64-BIT
;L -> 1
;D/B -> 0
GDT64:

; Null segment
dd 0, 0

; Code segment -> page 97
dd 0xffff                                   ;lower 16 bits from base address, lower 16 bits from segment limit
;BA - bits [7:0] - bits[16:23] from base address
;Type - bits [11:8] - read/execution -> 0b1010 -> Table 3.1 page 100
;S - bit 12 - the segment descriptor is for a system segment (S flag is clear) or a code or data segment (S flag is set)
;DPL - bits[14:13] - DPL (descriptor privilege level) field specifies the privilege level of the segment -> 0 to 3
;P - bit 15 - indicates whether the segment is present in memory (set) or not present (clear)
;SegLimit - bits [19:16] - its bits [19:16] from 20 bits segment limit
;AVL - bit 20 - Available for use by system software
;L - bit 21 - 1 64 bit segment, 0 no 64 bits segment
;D/B - bit 22 - 0 16 bit segment, 1 32 bits segment
;G - bit 23 - Granularity -  granularity flag is clear, the segment limit is interpreted in byte units; when flag is set, the segment limit is interpreted in 4-KByte units.
;BA - bits [31:24] - bits[24:31] from base address
dd (10 << 8) | (1 << 12) | (1 << 15) | (15 << 16) | (1 << 21) | (1 << 23)

; Data segment
dd 0xffff
dd (2 << 8) | (1 << 12) | (1 << 15) | (15 << 16) | (1 << 21) | (1 << 23)

; Its helpfull when number of segment is multiply of 2
dd 0, 0

GDT_END64:

;this is GDT address structure for lgdt instruction
;intel manuals 2A -> page 663
;2Bytes limit/size, 4Bytes Address
GDT_ADR64:
dw (GDT_END64 - GDT64) - 1                  ;size of GDT above as 2Bytes
dd 0x10000 + GDT64                          ;16 bit mode address GDT
times (32 - ($ - $$) % 32) dd 0xcc

times 4096 - ($ - $$) db 0

;IE-32e Paging
;Intel 3A -> page 124
;its a paging for long mode
;!!!MAP 2 MB!!!
;Intel 3A -> page 126 Figure 4-9

PML4:

;this PML4 allow as to add 512 page address because we have 9 bits in virtual address for PML4
;below we define one page
;Intel 3A -> page 124

;P - bit 0 - must be 1
;R/W - bit 1 - 0 means only read, 1 means read and write
;U/S - bit 2 - 0 means that only ring 0 can access this region -> https://en.wikipedia.org/wiki/Protection_ring
;PWT - bit 3 - caching type ?
;PWD - bit 4 - cache disable if 1
;A - bit 5 - indicates whether this entry has been used for linear-address translation ?
;bit 6 - ignored
;PS - bit 7 - must be 0
;bits[8:11] - ignored
;bits[12:PDPTE size - 1] - pointer to PDPTE, bits [12:] from PDPTE goes here
;bits[PDPTE size:51] - this bits must be 0
;bits[52:62] - ignored
;XD - bit 63 - 1 block code execution from this page, 0 allowes execution
;intel 3A - page 129, table 4.15
dq 1 | (1 << 1) | (PDPTE - $$ + 0x10000)        ;$$ means nasm code begin, $ end, its just bitewise add address so lower 12 bits change
times 511 dq 0                                  ;we add 1 record, so we must add other 511 record * 4 bytes

;Directory-Pointer
;this PDPTE allow as to add 512 page address because we have 9 bits in virtual address for PDPTE
;below we define one page
;Intel 3A -> page 124

PDPTE:

;intel 3A - page 130, table 4.17
dq 1 | (1 << 1) | (PDE - $$ + 0x10000)
times 511 dq 0

;Directory
;this PDE allow as to add 512 page address because we have 9 bits in virtual address for PDE
;below we define six page
;Intel 3A -> page 124

PDE:
;P - bit 0 - must be 1
;R/W - bit 1 - 0 means only read, 1 means read and write
;U/S - bit 2 - 0 means that only ring 0 can access this region -> https://en.wikipedia.org/wiki/Protection_ring
;PWT - bit 3 - caching type ?
;PWD - bit 4 - cache disable if 1
;A - bit 5 - indicates whether software has accessed the 2mb page referenced by this entry
;D - bit 6 - indicates whether software has written to the 2mb page referenced by this entry
;PS - bit 7 - page size, must be 1
;G - bit 8 - define if translation is global
;bits[9:11] - ignored
;PAT - bit 12 - determines the memory type used to access the 2mb page referenced by this entry
;bits[13:20] - must be 0
;bits[21:memory address size - 1] - bits [21:] from physical address goes here
;bits[memory address size:51] - must be 0
;bits[52:58] - ignored
;bits[59:62] - access level, set 0 for ring 0
;bits[63] - 1 block code execution from this page, 0 allowes execution
;intel 3A - page 130, table 4.18
;dq 1 | (1 << 1) | (1 << 7)
;dq 1 | (1 << 1) | (1 << 7) | (0x00200000)
;dq 1 | (1 << 1) | (1 << 7) | (0x00400000)
;dq 1 | (1 << 1) | (1 << 7) | (0x00600000)
;dq 1 | (1 << 1) | (1 << 7) | (0x00800000)
;dq 1 | (1 << 1) | (1 << 7) | (0x00A00000)
;times 506 dq 0
%assign i 0
%rep 512
  dq 0x200000*i+0x83 ;2MB Pages
%assign i i+1
%endrep

times (512 - ($ - $$) % 512) db 0
kernel64: