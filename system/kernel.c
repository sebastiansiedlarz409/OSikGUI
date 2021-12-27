#include "include/api.h"
#include "include/common.h"
#include "include/drawing.h"
#include "include/windows.h"
#include "include/menu.h"
#include "include/heap.h"
#include "include/loader.h"
#include "include/streams.h"
#include "include/string.h"
#include "include/keyboard.h"
#include "include/interrupt.h"

#include <stdint.h>

void notepadWindowInputHandle(WindowContext* context){
    uint8_t value = GetSystemContext()->PopInSteam();

    char buffer[100];

    WindowContext* textContext = context->children[0];

    if(textContext == NULL){
        textContext = CreateTextWindowContext(context, 10, 10, GREY1, RED, 2);
                
        MemsetBuffer(buffer, 0, 100);
        FormatString(buffer, "%c", value);
    }
    else{    
        MemsetBuffer(buffer, 0, 100);
        FormatString(buffer, "%s%%c",textContext->data.content, value);
    }

    DrawTextWindow(textContext, buffer);
}

void KERN_Load(void* kernelEntryPointAddress, void* stackAddress, void* appsTableAddress){
    GetSystemContext()->kernelAddress=(uint64_t)kernelEntryPointAddress;
    GetSystemContext()->stackAddress=(uint64_t)stackAddress;
    GetSystemContext()->appsTableAddress=(uint64_t)appsTableAddress;

    DrawString(520, 145, "OSik", 30, RED, BLACK);
    DrawString(700, 520, "Booting!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 0, GREEN, GREY3);
    RefreshScreen();
    InitHeap(0x600000, 0x200000);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(610, 520, "Setup Interrupts!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 20, GREEN, GREY3);
    RefreshScreen();
    InitInterrupt();
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(635, 520, "Start Timers!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 50, GREEN, GREY3);
    RefreshScreen();
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(620, 520, "Start Usermode!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 100, GREEN, GREY3);
    InitAPI();
    RefreshScreen();
    WaitSeconds(1);
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress, void* appsTableAddress){
    KERN_Load(kernelEntryPointAddress, stackAddress, appsTableAddress);

    DrawUI();

    //testloader
    uint64_t firstappPointer = 0x10000 + *((uint64_t*)GetSystemContext()->appsTableAddress);
    void* entry = LoadApp((void*)firstappPointer);
    RunApp(entry);

    //tests stdin and keyboard
    /*WindowContext* notepad1WindowContext = CreateWindowContext(
        GetSystemContext()->mainWindow,
        30, 10, 430, 410, "Notepad1", LIGHTBLUE, GREYE, BLACK, notepadWindowInputHandle
    );
    DrawWindow(notepad1WindowContext);
    
    WindowContext* notepad2WindowContext = CreateWindowContext(
        GetSystemContext()->mainWindow,
        600, 10, 1000, 410, "Notepad2", AMBER, GREYE, BLACK, notepadWindowInputHandle
    );
    DrawWindow(notepad2WindowContext);*/

    WindowContext* notepad3WindowContext = CreateWindowContext(
        GetSystemContext()->mainWindow,
        1100, 10, 1500, 410, "Notepad3", LIGHTMAGENTA, GREYE, BLACK, notepadWindowInputHandle
    );
    DrawWindow(notepad3WindowContext);

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
        400, 100, 800, 400, "Welcome", LIGHTBLUE, GREYE, BLACK, NULL
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