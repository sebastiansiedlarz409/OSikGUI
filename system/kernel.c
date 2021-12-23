#include "common.h"
#include "drawing.h"
#include "windows.h"
#include "menu.h"
#include "heap.h"
#include "string.h"
#include "keyboard.h"
#include "interrupt.h"
#include <stdint.h>

void KERN_Load(void* kernelEntryPointAddress, void* stackAddress){
    GetSystemContext()->kernelAddress=(uint64_t)kernelEntryPointAddress;
    GetSystemContext()->stackAddress=(uint64_t)stackAddress;

    DrawString(520, 145, "OSik", 30, RED, BLACK);
    DrawString(700, 520, "Booting!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 0, GREEN, GREYB);
    InitHeap(0x500000, 0x100000);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(610, 520, "Setup Interrupts!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 20, GREEN, GREYB);
    InitInterrupt();
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(635, 520, "Start Timers!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 50, GREEN, GREYB);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(620, 520, "Start Usermode!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 100, GREEN, GREYB);
    WaitSeconds(1);
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress){
    KERN_Load(kernelEntryPointAddress, stackAddress);

    DrawUI();

    //heap tests
    /*char buffer[100];
    MemsetBuffer(buffer, 0, 100);
    void* p1 = MallocHeap(20);
    FormatString(buffer, "P1: 0x%x", (uint64_t)p1);
    DrawString(320, 520, buffer, 2, BLUE, LIGHTGREY);

    MemsetBuffer(buffer, 0, 100);
    void* p2 = MallocHeap(20);
    FormatString(buffer, "P2: 0x%x", (uint64_t)p2);
    DrawString(320, 540, buffer, 2, BLUE, LIGHTGREY);

    MemsetBuffer(buffer, 0, 100);
    FreeHeap(p2);
    void* p3 = MallocHeap(10);
    FormatString(buffer, "P3: 0x%x", (uint64_t)p3);
    DrawString(320, 560, buffer, 2, BLUE, LIGHTGREY);

    MemsetBuffer(buffer, 0, 100);
    void* p4 = MallocHeap(20);
    FormatString(buffer, "P4: 0x%x", (uint64_t)p4);
    DrawString(320, 580, buffer, 2, BLUE, LIGHTGREY);*/

    //test int 0
    /*WaitSeconds(5);
    int a = 0, b = 0;
    __asm__ volatile("div %2\n"
       : "=d" (a), "=a" (b)
       : "r" (a), "d" (a), "a" (a));*/

    for(;;);
}