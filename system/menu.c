#include "menu.h"
#include "common.h"
#include "drawing.h"
#include "windows.h"

void DrawInfoWindow(WindowContext* parent){
    WindowContext context = DrawWindow(parent, 600, 40, 960, 1140, "Information", BLUE, LIGHTGREY, BLACK);
    DrawText(&context, 30, 30, "OSikGUI", 10, BRONZE, LIGHTGREY);
    //WaitSeconds(1);

    //CloseWindow(&context);
}

void DrawUI(void){
    WindowContext context;
    if(GetSystemContext()->window!=0){
        context = DrawWindow(NULL, 0, 0, 1600, 1200, "Desktop", RED, GREY, WHITE);
        GetSystemContext()->mainWindow = context;
    }
    else{
        context = DrawWindow(NULL, 0, 0, 1600, 1200, "BSOD", DARKBLUE, BLACK, WHITE); //BSOD
        GetSystemContext()->mainWindow = context;
    }

    if(GetSystemContext()->window == 1){
        DrawInfoWindow(&context);
    }

}