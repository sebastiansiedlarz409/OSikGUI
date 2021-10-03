#include "windows.h"
#include "drawing.h"

#include <stdint.h>

#define TITLE_BAR_WIDTH 12
#define MIN_WIDTH 80
#define MIN_HEIGHT (TITLE_BAR_WIDTH+20)

void DrawTitleBar(uint16_t sx, uint16_t sy, uint16_t width, const char* title, uint8_t theme){
    DrawRectangle(sx, sy, sx+width, sy+TITLE_BAR_WIDTH, theme, theme);
    DrawString(sx+5, sy+2, title, 1, BLACK, theme);
}

void DrawWindow(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, const char* title, uint8_t theme){
    if(height <= MIN_HEIGHT || width < MIN_WIDTH){
        return;
    }

    //whole window border
    DrawRectangle(sx, sy, sx+width, sy+height, theme, BLACK);

    DrawTitleBar(sx+1, sy+1, width-1, title, theme);
}