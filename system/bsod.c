#include "bsod.h"
#include "drawing.h"
#include "windows.h"
#include "common.h"
#include "menu.h"
#include "string.h"

void BSOD(const char* str, void* trapFrame){
    GetSystemContext()->window = 0; //set to BSOD
    DrawUI();
    DrawText(&(GetSystemContext()->mainWindow), 30, 30, ":", 30, WHITE, BLACK);
    DrawText(&(GetSystemContext()->mainWindow), 105, 30, "(", 30, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 280, str, 6, WHITE, WHITE);

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
    DrawText(&(GetSystemContext()->mainWindow), 30, 400, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R14: 0x%x", r14);
    DrawText(&(GetSystemContext()->mainWindow), 30, 424, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R13: 0x%x", r13);
    DrawText(&(GetSystemContext()->mainWindow), 30, 448, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R12: 0x%x", r12);
    DrawText(&(GetSystemContext()->mainWindow), 30, 472, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R11: 0x%x", r11);
    DrawText(&(GetSystemContext()->mainWindow), 30, 498, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R10: 0x%x", r10);
    DrawText(&(GetSystemContext()->mainWindow), 30, 522, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R9: 0x%x", r9);
    DrawText(&(GetSystemContext()->mainWindow), 30, 546, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "R8: 0x%x", r8);
    DrawText(&(GetSystemContext()->mainWindow), 30, 570, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RIP: 0x%x", rip);
    DrawText(&(GetSystemContext()->mainWindow), 30, 596, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RBP: 0x%x", rbp);
    DrawText(&(GetSystemContext()->mainWindow), 440, 400, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RDI: 0x%x", rdi);
    DrawText(&(GetSystemContext()->mainWindow), 440, 424, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RSI: 0x%x", rsi);
    DrawText(&(GetSystemContext()->mainWindow), 440, 448, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RDX: 0x%x", rdx);
    DrawText(&(GetSystemContext()->mainWindow), 440, 472, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RCX: 0x%x", rcx);
    DrawText(&(GetSystemContext()->mainWindow), 440, 498, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RBX: 0x%x", rbx);
    DrawText(&(GetSystemContext()->mainWindow), 440, 522, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RAX: 0x%x", rax);
    DrawText(&(GetSystemContext()->mainWindow), 440, 546, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "RSP: 0x%x", rsp);
    DrawText(&(GetSystemContext()->mainWindow), 440, 570, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    FormatString(buffer, "EFLAGS: 0x%x", eflags);
    DrawText(&(GetSystemContext()->mainWindow), 440, 596, buffer, 2, WHITE, WHITE);
    MemsetBuffer(buffer, 0, 100);

    DrawText(&(GetSystemContext()->mainWindow), 1500, 880, "SS", 2, WHITE, WHITE);

    for(;;);
}