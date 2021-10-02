#include "drawing.h"

#include <stdint.h>

void DrawPixel(uint16_t x, uint16_t y, uint8_t color){
    uint8_t* frame = (uint8_t*)0xA0000;
    y++;

    frame[(y*WIDTH)+x] = color;
}

void DrawHorizontalLine(uint16_t x, uint16_t y, uint16_t len, uint8_t color){
    len+=x;
    for(uint16_t i = x;i<len;i++){
        DrawPixel(i, y, color);
    }
}

void DrawVerticalLine(uint16_t x, uint16_t y, uint16_t len, uint8_t color){
    len+=y;
    for(uint16_t i = y;i<len;i++){
        DrawPixel(x, i, color);
    }
}

void DrawLine(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, uint8_t color){
    uint16_t dx = ex - sx;
    uint16_t dy = ey - sy;

    for(uint16_t i = sx; i<ex;i++){
        uint16_t y = sy + dy * (i - sx) / dx;
        DrawPixel(i, y, color);
    }
}

void DrawRectangle(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, uint8_t border_color, uint8_t fill_color){
    //border
    DrawHorizontalLine(sx, sy, ex-sx, border_color); //top
    DrawHorizontalLine(sx, ey, ex-sx+1, border_color); //bottom

    DrawVerticalLine(sx, sy, ey-sy, border_color); //left
    DrawVerticalLine(ex, sy, ey-sy, border_color); //right

    //fill
    for(uint16_t i = sy+1; i<ey;i++){
        DrawHorizontalLine(sx+1, i, ey-sx-1, fill_color);
    }
}

void DrawCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t border_color, uint8_t fill_color){
    for(uint16_t dy = 0;dy<HEIGHT;dy++){
        for(uint16_t dx = 0;dx<WIDTH;dx++){
            uint16_t distance = (uint16_t)isqrt((dx-x)*(dx-x)+(dy-y)*(dy-y));

            if(distance == r){
                DrawPixel(dx, dy, border_color);
            }
            else if(distance < r){
                DrawPixel(dx, dy, fill_color);
            }
        }
    }
}