#include "../../system/include/api.h"

SystemAPI* api;

void APP_Start(){
    api = (SystemAPI*)0x800000;

    WindowContext* notepad1WindowContext = api->CreateWindowContext(
        api->GetSystemContext()->mainWindow,
        430, 10, 830, 410, "Info", AMBER, GREYE, BLACK, NULL
    );
    api->DrawWindow(notepad1WindowContext);
}