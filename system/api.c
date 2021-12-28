#include "include/api.h"
#include "include/common.h"
#include "include/heap.h"
#include "include/math.h"
#include "include/windows.h"
#include "include/string.h"
#include "include/drawing.h"

void InitAPI(void){
    SystemAPI* api = (SystemAPI*)0x800000;

    api->MathSqrt = MathSqrt;
    
    api->GetSystemContext = GetSystemContext;

    api->MallocHeap = MallocHeap;
    api->FreeHeap = FreeHeap;

    api->StringLength = StringLength;
    api->FormatString = FormatString;
    api->MemcpyBuffers = MemcpyBuffers;
    api->MemsetBuffer = MemsetBuffer;

    api->RefreshScreen = RefreshScreen;
    api->RefreshPartOfScreen = RefreshPartOfScreen;
    api->DrawPixel = DrawPixel;
    api->DrawHorizontalLine = DrawHorizontalLine;
    api->DrawVerticalLine = DrawVerticalLine;
    api->DrawLine = DrawLine;
    api->DrawWLine = DrawWLine;
    api->DrawRectangle = DrawRectangle;
    api->DrawQuarterCircle = DrawQuarterCircle;
    api->DrawCircle = DrawCircle;
    api->DrawChar = DrawChar;
    api->DrawString = DrawString;
    api->ClearFullScreen = ClearFullScreen;
    api->ClearPartScreen =ClearPartScreen;
    api->FillScreen = FillScreen;
    api->DrawProgressBar = DrawProgressBar;

    api->CreateWindowContext = CreateWindowContext;
    api->CreateTextWindowContext = CreateTextWindowContext;
    api->CreateProgressBarWindowContext = CreateProgressBarWindowContext;
    api->CreateDescButtonWindowContext = CreateDescButtonWindowContext;
    api->CloseWindow = CloseWindow;
    api->DrawWindow = DrawWindow;
    api->DrawTextWindow = DrawTextWindow;
    api->DrawProgressBarWindow = DrawProgressBarWindow;
    api->DrawDescButtonWindow = DrawDescButtonWindow;
}