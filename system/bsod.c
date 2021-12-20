#include "bsod.h"
#include "drawing.h"
#include "windows.h"
#include "common.h"

void BSOD(const char* str, void* trapFrame){
    GetSystemContext()->window = 0; //set to BSOD
    DrawUI();
    DrawText(&(GetSystemContext()->mainWindow), 30, 30, ":", 30, WHITE, BLACK);
    DrawText(&(GetSystemContext()->mainWindow), 105, 30, "(", 30, WHITE, WHITE);
    DrawText(&(GetSystemContext()->mainWindow), 30, 280, str, 6, WHITE, WHITE);

    for(;;);
}