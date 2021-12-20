#include "menu.h"
#include "common.h"
#include "drawing.h"
#include "windows.h"

void DrawMainWindow(){
    DrawWindow(0, 0, 1600, 1200, "Desktop", RED, WHITE);
}

void DrawUI(void){

    if(GetSystemContext()->window == 0){
        DrawMainWindow();       
    }

}