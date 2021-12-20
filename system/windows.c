#include "windows.h"
#include "drawing.h"

#include <stdint.h>

#define TITLE_BAR_WIDTH 20
#define MIN_WIDTH 80
#define MIN_HEIGHT (TITLE_BAR_WIDTH+20)

void DrawButtonWithDesc(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, const char* title, const char* desc, uint8_t border_color, uint8_t fill_color){
    DrawRectangle(sx, sy, ex, ey, border_color, fill_color);

    //title
    DrawString(sx+10, sy+10, title, 4, RED, BLACK);

    //desc
    DrawString(sx+10, sy+30, desc, 1, RED, BLACK);
}

void DrawTitleBar(uint16_t sx, uint16_t sy, uint16_t width, const char* title, uint8_t theme){
    DrawRectangle(sx, sy, sx+width, sy+TITLE_BAR_WIDTH, theme, theme);
    
    //title
    DrawString(sx+5, sy+2, title, 2, BLACK, theme);

    //icons
    DrawCircle(sx+width-10, sy+10, 6, BLUE, BLUE);
    DrawCircle(sx+width-25, sy+10, 6, GREEN, GREEN);
    DrawCircle(sx+width-40, sy+10, 6, BRONZE, BRONZE);
}

void DrawWindow(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, const char* title, uint8_t theme, uint8_t font_color){
    if(height <= MIN_HEIGHT || width < MIN_WIDTH){
        return;
    }

    //whole window border
    DrawRectangle(sx, sy, sx+width, sy+height, theme, BLACK);

    DrawTitleBar(sx+1, sy+1, width-1, title, theme);

    //DrawButtonWithDesc(sx+10, sy+5, sx+70, sx+45, "F1", "Kalkulator", BLUE, BLUE);
}