#include "../../system/include/api.h"

SystemAPI* api;

void notepadOnFocusInHandler(WindowContext* context){
    context->keys = 1;
}

void notepadOnFocusOutHandler(WindowContext* context){
    context->keys = 0;
}

void notepadWindowInputHandle(WindowContext* context){
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
    api->RefreshScreen();
}

void APP_Start(){
    api = (SystemAPI*)0x800000;

    WindowContext* notepadWindowContext = api->CreateWindowContext(
        api->GetSystemContext()->mainWindow,
        1020, 10, 1570, 410, "Notepad", LIGHTHELIOTROPE, GREYE, BLACK, notepadWindowInputHandle, notepadOnFocusInHandler, notepadOnFocusOutHandler
    );

    notepadOnFocusInHandler(notepadWindowContext);

    api->DrawWindow(notepadWindowContext);
}