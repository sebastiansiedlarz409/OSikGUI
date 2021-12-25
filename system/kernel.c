#include "common.h"
#include "drawing.h"
#include "windows.h"
#include "menu.h"
#include "heap.h"
#include "streams.h"
#include "string.h"
#include "keyboard.h"
#include "interrupt.h"

#include <stdint.h>

void KERN_Load(void* kernelEntryPointAddress, void* stackAddress){
    GetSystemContext()->kernelAddress=(uint64_t)kernelEntryPointAddress;
    GetSystemContext()->stackAddress=(uint64_t)stackAddress;

    DrawString(520, 145, "OSik", 30, RED, BLACK);
    DrawString(700, 520, "Booting!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 0, GREEN, GREY3);
    InitHeap(0x500000, 0x100000);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(610, 520, "Setup Interrupts!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 20, GREEN, GREY3);
    InitInterrupt();
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(635, 520, "Start Timers!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 50, GREEN, GREY3);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(620, 520, "Start Usermode!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 100, GREEN, GREY3);
    WaitSeconds(1);
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress){
    KERN_Load(kernelEntryPointAddress, stackAddress);

    DrawUI();

    //streams tests
    /*GetSystemContext()->PushInStream(53);
    uint8_t value = GetSystemContext()->PopInSteam();
    char buffer[100];
    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "STDIN %u", value);
    DrawString(320, 720, buffer, 2, BLUE, GREY1);*/

    //windows api tests
    /*WindowContext* welcomeWindowContext = CreateWindowContext(
        GetSystemContext()->mainWindow,
        10, 10, 400, 400, "Welcome", LIGHTBLUE, GREYE, BLACK
    );
    DrawWindow(welcomeWindowContext);

    char buffer[100];
    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "1 HF: 0x%x SOF(W): 0x%x Id: %u CC: %u",
                        GetSystemContext()->heapNextFree,
                        sizeof(WindowContext),
                         (uint64_t)GetSystemContext()->mainWindow->id,
                         GetSystemContext()->mainWindow->childrenCount);
    DrawString(320, 720, buffer, 2, BLUE, GREY1);
    
    WindowContext* welcomeWindowTextContext = CreateTextWindowContext(welcomeWindowContext, 20, 20, welcomeWindowContext->background, BROWN, 2);
    DrawTextWindow(welcomeWindowTextContext, "Welcome inside OSikGUI");

    WindowContext* welcomeWindowProgressBarContext = CreateProgressBarWindowContext(welcomeWindowContext, 20, 40, 230, 80, RED, GREEN);
    DrawProgressBarWindow(welcomeWindowProgressBarContext, 80);

    WindowContext* welcomeWindowButtonContext = CreateDescButtonWindowContext(welcomeWindowContext, 20, 90, 100, 150, GREEN, BLUE, RED, 2);
    DrawDescButtonWindow(welcomeWindowButtonContext, "Button");
    
    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "2 HF: 0x%x SOF(W): 0x%x Id: %u CC: %u",
                        GetSystemContext()->heapNextFree,
                        sizeof(WindowContext),
                         welcomeWindowContext->id,
                         welcomeWindowContext->childrenCount);
    DrawString(320, 750, buffer, 2, BLUE, GREY1);

    //WaitSeconds(3);
    //CloseWindow(welcomeWindowContext);
    
    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "3 HF: 0x%x SOF(W): 0x%x Id: %u CC: %u",
                        GetSystemContext()->heapNextFree,
                        sizeof(WindowContext),
                         (uint64_t)GetSystemContext()->mainWindow->id,
                         GetSystemContext()->mainWindow->childrenCount);
    DrawString(320, 780, buffer, 2, BLUE, GREY1);*/

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