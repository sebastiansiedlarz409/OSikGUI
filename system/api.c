#include "include/api.h"
#include "include/common.h"
#include "include/heap.h"
#include "include/math.h"
#include "include/windows.h"

void InitAPI(void){
    SystemAPI* api = (SystemAPI*)0x800000;

    api->MathSqrt = MathSqrt;
    
    api->GetSystemContext = GetSystemContext;

    api->MallocHeap = MallocHeap;
    api->FreeHeap = FreeHeap;

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