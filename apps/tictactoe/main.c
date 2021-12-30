#include "../../system/include/api.h"

SystemAPI* api;

void tttWindowInputHandle(WindowContext* context){
    uint8_t value = api->GetSystemContext()->PopInSteam();
    

}

void DrawField(WindowContext* context){
    //540 w
    //700 h
    api->DrawWLine(context->position.sx, context->position.sy+220, context->position.ex, context->position.sy+220, 20, BRIGHTBLUE);
}

void APP_Start(){
    api = (SystemAPI*)0x800000;

    WindowContext* tttWindowContext = api->CreateWindowContext(
        api->GetSystemContext()->mainWindow,
        460, 230, 1000, 930, "Tic Tac Toe", DODGERBLUE, GREYE, BLACK, tttWindowInputHandle
    );
    api->DrawWindow(tttWindowContext);

    DrawField(tttWindowContext);

    api->RefreshScreen();
}