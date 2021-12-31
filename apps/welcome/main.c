#include "../../system/include/api.h"

SystemAPI* api;

void welcomeWindowInputHandle(WindowContext* context){
    uint8_t value = api->GetSystemContext()->PopInSteam();
    UNUSED(value);
    UNUSED(context);
}

void APP_Start(void* entry){
    api = (SystemAPI*)0x800000;

    WindowContext* welcomeWindowContext = api->CreateWindowContext(
        api->GetSystemContext()->mainWindow,
        30, 10, 420, 410, "Welcome", GREY3, GREY1, WHITE, entry,
         welcomeWindowInputHandle, NULL, NULL
    );

    api->DrawWindow(welcomeWindowContext);

    WindowContext* textContext = api->CreateTextWindowContext(welcomeWindowContext, 10, 10, GREY1, BROWN, 8);

    api->DrawTextWindow(textContext, "OSikGUI");

    WindowContext* textDescContext = api->CreateTextWindowContext(welcomeWindowContext, 10, 85, GREY1, BLUE, 4);

    api->DrawTextWindow(textDescContext, "Just for fun! :)");
    api->RefreshScreen();
}