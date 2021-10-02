[bits 16]                       ;we start in 16 bits mode
[org 0x7c00]                    ;adres in memory where bios upload our image is 0x0000:0x7c00
                                ;THERE IS ONLY 512 BYTES SPACE -> https://wiki.osdev.org/Memory_Map_(x86)
                                ;its 16bit address mode
                                ;address = segment * 0x10 + offset
                                ;segment go to segment register CS, DS, ES, FS, GS, and SS
                                ;offset go to IP register
                                ;so CS = 0x0000, IP == 0x7c00
                                ;check "Memory Addressing" -> https://wiki.osdev.org/Real_Mode

jmp word 0x0000:stage1          ;just jump to stage1 label

stage1:
    mov ax, 0x1000              ;we can not mov const to segment register directly
    mov es, ax                  ;so we mov register to segment register
    mov bx, 0                   ;bx is offset in address
                                ;[es:bx] (0x1000*0x10+0x0) is where stage2 will be loaded by int 13h

    mov ah, 0x02                ;interrupt 13h command

    mov al, 0x97                ;count of sector to load from stage2, 1 sector = 512 bytes
    nop
    nop
    mov ch, 0                   ;cylinder index, in case of floppy it is 0
    mov dh, 0                   ;head index, in case of floppy it is 0
    mov cl, 2                   ;index of first stage2 sector, index start from 1, bits 7-6 = 00
    ;mov dl, 0                  ;drive index, BIOS set it for us
                                ;check page 6 -> http://www.gabrielececchetti.it/Teaching/CalcolatoriElettronici/Docs/i8086_and_DOS_interrupts.pdf

    int 13h                     ;interrupt from link above
                                ;move to stage2

    jmp word 0x1000:0x0000      ;we loaded stage2 so now we jump there

ending:
%if ($ - $$) > 510
  %fatal "STAGE1 code cant exceed 512 bytes!!!"
%endif

times 510 - ($ - $$) db 0       ;if stage1 size is less than 510 add some trash
db 0x55                         ;last to bytes
db 0xAA                         ;check "MBR Format" -> https://wiki.osdev.org/MBR_(x86)