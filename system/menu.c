#include "menu.h"
#include "common.h"
#include "drawing.h"
#include "string.h"
#include "windows.h"

void DrawInfoWindow(WindowContext* parent){
    WindowContext* context = DrawWindow(parent, 600, 40, 960, 1140, "Information", BLUE, LIGHTGREY, BLACK);
    DrawText(context, 30, 30, "OSikGUI", 10, BRONZE, LIGHTGREY);

    /*DrawWindow(context, 620, 260, 200, 600, "Subwindow 1", GREEN, GREY, BLACK);
    DrawWindow(context, 840, 260, 200, 600, "Subwindow 2", PINK, GREY, BLACK);

    WaitSeconds(1);

    CloseWindow(context);*/

    /*WaitSeconds(1);

    CloseWindowX(context);*/
}

void DrawCalculatorWindow(WindowContext* parent){
    WindowContext* context = DrawWindow(parent, 600, 40, 960, 1140, "Calculator App", CYAN, LIGHTGREY, BLACK);
    DrawText(context, 30, 30, "Calculator", 10, BLACK, LIGHTGREY);
}

void DrawStateWindow(WindowContext* parent){
    WindowContext* context = DrawWindow(parent, 30, 600, 560, 580, "Stats", GREEN, LIGHTGREY, BLACK);

    char buffer[100];

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Kernel Entry: 0x%x", GetSystemContext()->kernelAddress);
    DrawText(context, 30, 30, buffer, 2, BLACK, LIGHTGREY);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Stack Address: 0x%x", GetSystemContext()->stackAddress);
    DrawText(context, 30, 50, buffer, 2, BLACK, LIGHTGREY);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Heap Address: 0x%x", GetSystemContext()->heapAddress);
    DrawText(context, 30, 70, buffer, 2, BLACK, LIGHTGREY);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Heap Size: 0x%x", GetSystemContext()->heapSize);
    DrawText(context, 30, 90, buffer, 2, BLACK, LIGHTGREY);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Heap Next Free: 0x%x", GetSystemContext()->heapNextFree);
    DrawText(context, 30, 110, buffer, 2, BLACK, LIGHTGREY);

    MemsetBuffer(buffer, 0, 100);
    FormatString(buffer, "Current Menu Position: %u", GetSystemContext()->window);
    DrawText(context, 30, 130, buffer, 2, BLACK, LIGHTGREY);
}

void DrawUI(void){
    ClearFullScreen();

    WindowContext* context;
    if(GetSystemContext()->window!=0){
        context = DrawWindow(NULL, 0, 0, 1600, 1200, "Desktop", RED, GREY, WHITE);
        GetSystemContext()->mainWindow = context;

        DrawStateWindow(context);
    }
    else{
        context = DrawWindow(NULL, 0, 0, 1600, 1200, "BSOD", DARKBLUE, BLACK, WHITE); //BSOD
        GetSystemContext()->mainWindow = context;
    }

    if(GetSystemContext()->window == 1){
        DrawInfoWindow(context);
    }
    else if(GetSystemContext()->window == 2){
        DrawCalculatorWindow(context);
    }

}

void SwichWindow(void){
    GetSystemContext()->window++;
    if(GetSystemContext()->window>GetSystemContext()->windowsCount){
        GetSystemContext()->window=1;
    }

    DrawUI();
}