#include "bsod.h"
#include "drawing.h"
#include "windows.h"
#include "common.h"

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

    DrawText(&(GetSystemContext()->mainWindow), 30, 400, "R15:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 424, "R14:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 448, "R13:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 472, "R12:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 498, "R11:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 522, "R10:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 546, "R9:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 570, "R8:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 596, "RIP:", 2, WHITE, WHITE);

    
    DrawText(&(GetSystemContext()->mainWindow), 440, 400, "RBP:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 440, 424, "RDI:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 440, 448, "RSI:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 440, 472, "RDX:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 440, 498, "RCX:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 440, 522, "RBX:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 440, 546, "RAX:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 440, 570, "RSP:", 2, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 440, 596, "EFLAGS:", 2, WHITE, WHITE);

    DrawText(&(GetSystemContext()->mainWindow), 1500, 880, "SS", 2, WHITE, WHITE);

    for(;;);
}