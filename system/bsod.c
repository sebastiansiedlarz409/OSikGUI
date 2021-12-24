#include "bsod.h"
#include "drawing.h"
#include "windows.h"
#include "common.h"
#include "menu.h"
#include "string.h"

void BSOD(const char* str, void* trapFrame){
    GetSystemContext()->window = 0; //set to BSOD
    DrawUI();
    DrawString(30, 50, ":", 30, WHITE, BLACK);
    DrawString(105, 50, "(", 30, WHITE, BLACK);
    DrawString(30, 300, str, 6, WHITE, BLACK);

    uint64_t* frameBuffer = (uint64_t*)trapFrame;

    uint64_t r15 = *(frameBuffer);
    uint64_t r14 = *(frameBuffer+1);
    uint64_t r13 = *(frameBuffer+2);
    uint64_t r12 = *(frameBuffer+3);
    uint64_t r11 = *(frameBuffer+4);
    uint64_t r10 = *(frameBuffer+5);
    uint64_t r9 = *(frameBuffer+6);
    uint64_t r8 = *(frameBuffer+7);
    uint64_t rbp = *(frameBuffer+8);
    uint64_t rdi = *(frameBuffer+9);
    uint64_t rsi = *(frameBuffer+10);
    uint64_t rdx = *(frameBuffer+11);
    uint64_t rcx = *(frameBuffer+12);
    uint64_t rbx = *(frameBuffer+13);
    uint64_t rax = *(frameBuffer+14);
    uint64_t rsp = *(frameBuffer+15);
    uint64_t eflags = *(frameBuffer+16);
    uint64_t rip = *(frameBuffer+17);

    char buffer[100];
    MemsetBuffer(buffer, 0, 100);
    
    FormatString(buffer, "R15: 0x%x", r15);
    DrawString(30, 400, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R14: 0x%x", r14);
    DrawString(30, 424, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R13: 0x%x", r13);
    DrawString(30, 448, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R12: 0x%x", r12);
    DrawString(30, 472, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R11: 0x%x", r11);
    DrawString(30, 498, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R10: 0x%x", r10);
    DrawString(30, 522, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R9: 0x%x", r9);
    DrawString(30, 546, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R8: 0x%x", r8);
    DrawString(30, 570, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RIP: 0x%x", rip);
    DrawString(30, 596, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RBP: 0x%x", rbp);
    DrawString(440, 400, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RDI: 0x%x", rdi);
    DrawString(440, 424, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RSI: 0x%x", rsi);
    DrawString(440, 448, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RDX: 0x%x", rdx);
    DrawString(440, 472, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RCX: 0x%x", rcx);
    DrawString(440, 498, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RBX: 0x%x", rbx);
    DrawString(440, 522, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RAX: 0x%x", rax);
    DrawString(440, 546, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RSP: 0x%x", rsp);
    DrawString(440, 570, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "EFLAGS: 0x%x", eflags);
    DrawString(440, 596, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    DrawString(1500, 880, "SS", 2, WHITE, WHITE);

    for(;;);
}