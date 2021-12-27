#include "../../system/include/api.h"

SystemAPI* api;

void infoWindowInputHandle(WindowContext* context){
    uint8_t value = api->GetSystemContext()->PopInSteam();

    char buffer[100];

    WindowContext* textContext = context->children[0];

    if(textContext == NULL){
        textContext = api->CreateTextWindowContext(context, 10, 10, GREY1, RED, 2);
                
        api->MemsetBuffer(buffer, 0, 100);
        api->FormatString(buffer, "%c", value);
    }
    else{    
        api->MemsetBuffer(buffer, 0, 100);
        api->FormatString(buffer, "%s%%c",textContext->data.content, value);
    }

    api->DrawTextWindow(textContext, buffer);
}

void APP_Start(){
    api = (SystemAPI*)0x800000;

    WindowContext* infoWindowContext = api->CreateWindowContext(
        api->GetSystemContext()->mainWindow,
        430, 10, 830, 410, "Info", GREEN, GREYE, BLACK, infoWindowInputHandle
    );
    api->DrawWindow(infoWindowContext);
}