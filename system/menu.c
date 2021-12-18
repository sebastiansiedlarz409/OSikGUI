#include "menu.h"
#include "common.h"
#include "drawing.h"
#include "windows.h"

void DrawMainWindow(){
    DrawWindow(0, 0, 320, 200, "Okno glowne!", RED, WHITE);
}

void DrawUI(void){

    if(GetSystemContext()->window == 0){
        DrawMainWindow();       
    }

}