#include "menu.h"
#include "common.h"
#include "drawing.h"
#include "string.h"
#include "heap.h"
#include "windows.h"

/*void DrawInfoWindow(WindowContext* parent){
    WindowContext* context = DrawWindow(CreateWindowContext(parent, 600, 40, 960, 900, "Information", BLUE, GREYE, BLACK));
    DrawText(context, 30, 30, "OSikGUI", 10, BROWN, GREYE);
}

void DrawCalculatorWindow(WindowContext* parent){
    WindowContext* context = DrawWindow(CreateWindowContext(parent, 600, 40, 960, 900, "Calculator App", CYAN, GREYE, BLACK));
    DrawText(context, 30, 30, "Calculator", 10, BLACK, GREYE);
}

void DrawStateWindow(WindowContext* parent){
    //free memory before redraw
    if(GetSystemContext()->mainWindow->children[0] != NULL){
        FreeHeap(GetSystemContext()->mainWindow->children[0]);
    }

    WindowContext* context = DrawWindow(CreateWindowContext(parent, 30, 500, 560, 840, "Stats", GREEN, GREYE, BLACK));

    char buffer[100];

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Kernel Entry: 0x%x", GetSystemContext()->kernelAddress);
    DrawText(context, 30, 30, buffer, 2, BLACK, GREYE);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Stack Address: 0x%x", GetSystemContext()->stackAddress);
    DrawText(context, 30, 50, buffer, 2, BLACK, GREYE);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Heap Address: 0x%x", GetSystemContext()->heapAddress);
    DrawText(context, 30, 70, buffer, 2, BLACK, GREYE);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Heap Size: 0x%x", GetSystemContext()->heapSize);
    DrawText(context, 30, 90, buffer, 2, BLACK, GREYE);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Heap Next Free: 0x%x", GetSystemContext()->heapNextFree);
    DrawText(context, 30, 110, buffer, 2, BLACK, GREYE);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Current Menu Position: %u", GetSystemContext()->window);
    DrawText(context, 30, 130, buffer, 2, BLACK, GREYE);
}

void DrawSubWindow(WindowContext* context){
    if(GetSystemContext()->window != 0)
        DrawStateWindow(context);

    if(GetSystemContext()->window == 1){
        DrawInfoWindow(context);
    }
    else if(GetSystemContext()->window == 2){
        DrawCalculatorWindow(context);
    }
}*/

void DrawUI(void){
    ClearFullScreen();

    //create main system window
    WindowContext* context;
    if(GetSystemContext()->window!=0){
        context = CreateWindowContext(NULL, 0, 0, 1600, 950, "Desktop", RED, GREYA, WHITE);
        DrawWindow(context);
        GetSystemContext()->mainWindow = context;

    }
    else{
        context = CreateWindowContext(NULL, 0, 0, 1600, 950, "BSOD", BLUE, BLACK, WHITE);
        DrawWindow(context); //BSOD
        GetSystemContext()->mainWindow = context;
    }
}

/*void SwichWindow(void){
    FreeHeap(GetSystemContext()->mainWindow->children[GetSystemContext()->mainWindow->childrenCount-1]);

    GetSystemContext()->window++;
    if(GetSystemContext()->window>GetSystemContext()->windowsCount){
        GetSystemContext()->window=1;
    }

    DrawSubWindow(GetSystemContext()->mainWindow);
}*/