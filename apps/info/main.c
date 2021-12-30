#include "../../system/include/api.h"

SystemAPI* api;

void infoWindowInputHandle(WindowContext* context){
    uint8_t value = api->GetSystemContext()->PopInSteam();
    UNUSED(value);
    UNUSED(context);
}

void APP_Start(){
    api = (SystemAPI*)0x800000;

    WindowContext* infoWindowContext = api->CreateWindowContext(
        api->GetSystemContext()->mainWindow,
        460, 10, 1000, 210, "Info", GREEN, GREYE, BLACK, infoWindowInputHandle
    );
    api->DrawWindow(infoWindowContext);

    char buffer[100];
    WindowContext* textContext = NULL;

    api->MemsetBuffer(buffer, 0, 100);
    api->FormatString(buffer, "Kernel Entry: 0x%x", api->GetSystemContext()->kernelAddress);
    
    textContext = api->CreateTextWindowContext(infoWindowContext, 10, 10, GREY1, RED, 2);
    api->DrawTextWindow(textContext, buffer);

    api->MemsetBuffer(buffer, 0, 100);
    api->FormatString(buffer, "Stack Address: 0x%x", api->GetSystemContext()->stackAddress);
    
    textContext = api->CreateTextWindowContext(infoWindowContext, 10, 30, GREY1, RED, 2);
    api->DrawTextWindow(textContext, buffer);

    api->MemsetBuffer(buffer, 0, 100);
    api->FormatString(buffer, "Apps Address: 0x%x", api->GetSystemContext()->appsTableAddress);
    
    textContext = api->CreateTextWindowContext(infoWindowContext, 10, 50, GREY1, RED, 2);
    api->DrawTextWindow(textContext, buffer);

    api->MemsetBuffer(buffer, 0, 100);
    api->FormatString(buffer, "Heap Address: 0x%x", api->GetSystemContext()->heapAddress);
    
    textContext = api->CreateTextWindowContext(infoWindowContext, 10, 70, GREY1, RED, 2);
    api->DrawTextWindow(textContext, buffer);

    api->MemsetBuffer(buffer, 0, 100);
    api->FormatString(buffer, "Heap Size: 0x%x", api->GetSystemContext()->heapSize);
    
    textContext = api->CreateTextWindowContext(infoWindowContext, 10, 90, GREY1, RED, 2);
    api->DrawTextWindow(textContext, buffer);

    api->MemsetBuffer(buffer, 0, 100);
    api->FormatString(buffer, "Heap Next Free: 0x%x", api->GetSystemContext()->heapNextFree);
    
    textContext = api->CreateTextWindowContext(infoWindowContext, 10, 110, GREY1, RED, 2);
    api->DrawTextWindow(textContext, buffer);

    api->RefreshScreen();
}