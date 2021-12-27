#include "../../system/include/api.h"

SystemAPI* api;

void APP_Start(){
    api = (SystemAPI*)0x800000;

    WindowContext* notepad1WindowContext = api->CreateWindowContext(
        api->GetSystemContext()->mainWindow,
        30, 10, 430, 410, "Welcome", LIGHTBLUE, GREYE, BLACK, NULL
    );
    api->DrawWindow(notepad1WindowContext);
}