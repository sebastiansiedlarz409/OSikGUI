#include "common.h"
#include <stdint.h>

#define BLACK 0x00
#define BLUE 0x01
#define DARKGREEN 0x02
#define CYAN 0x03
#define DARKRED 0x04
#define PURPLE 0x05
#define BRONZE 0x06
#define LIGHTGREY 0x07
#define GREY 0x08
#define CONRFLOWERBLUE 0x09
#define GREEN 0x0A
#define LIGHTCYAN 0x0B
#define LIGHTORANGE 0x0C
#define LIGHTPINK 0x0D
#define YELLOW 0x0E
#define WHITE 0x0F
//---
#define RED 0x28
#define ORANGE 0x29
#define GREEN 0x30

#define HEIGHT 200
#define WIDTH 320

int32_t isqrt(int32_t num) {
    int32_t res = 0;
    int32_t bit = 1 << 30; 
    
    while (bit > num)
        bit >>= 2;

    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        } else
            res >>= 1;
        bit >>= 2;
    }
    return res;
}

void KERN_DrawPixel(uint16_t x, uint16_t y, uint8_t color){
    uint8_t* frame = (uint8_t*)0xA0000;
    y++;

    frame[(y*WIDTH)+x] = color;
}

void KERN_DrawHorizontalLine(uint16_t x, uint16_t y, uint16_t len, uint8_t color){
    len+=x;
    for(uint16_t i = x;i<len;i++){
        KERN_DrawPixel(i, y, color);
    }
}

void KERN_DrawVerticalLine(uint16_t x, uint16_t y, uint16_t len, uint8_t color){
    len+=y;
    for(uint16_t i = y;i<len;i++){
        KERN_DrawPixel(x, i, color);
    }
}

void KERN_DrawLine(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, uint8_t color){
    uint16_t dx = ex - sx;
    uint16_t dy = ey - sy;

    for(uint16_t i = sx; i<ex;i++){
        uint16_t y = sy + dy * (i - sx) / dx;
        KERN_DrawPixel(i, y, color);
    }
}

void KERN_DrawRectangle(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, uint8_t border_color, uint8_t fill_color){
    //border
    KERN_DrawHorizontalLine(sx, sy, ex-sx, border_color); //top
    KERN_DrawHorizontalLine(sx, ey, ex-sx+1, border_color); //bottom

    KERN_DrawVerticalLine(sx, sy, ey-sy, border_color); //left
    KERN_DrawVerticalLine(ex, sy, ey-sy, border_color); //right

    //fill
    for(uint16_t i = sy+1; i<ey;i++){
        KERN_DrawHorizontalLine(sx+1, i, ey-sx-1, fill_color);
    }
}

void KERN_DrawCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t border_color, uint8_t fill_color){
    for(uint16_t dy = 0;dy<HEIGHT;dy++){
        for(uint16_t dx = 0;dx<WIDTH;dx++){
            uint16_t distance = (uint16_t)isqrt((dx-x)*(dx-x)+(dy-y)*(dy-y));

            if(distance == r){
                KERN_DrawPixel(dx, dy, border_color);
            }
            else if(distance < r){
                KERN_DrawPixel(dx, dy, fill_color);
            }
        }
    }
}

void KERN_WaitSeconds(uint64_t seconds){
    uint64_t clock_speed = 400000000;
    seconds*=clock_speed;
    while(seconds--){
        __asm("nop");
    }
}

void KERN_Welcome(void* kernelEntryPointAddress, void* stackAddress)
{
    uint64_t KEPAddr = (uint64_t)kernelEntryPointAddress;
    uint64_t SAddr = (uint64_t)stackAddress;
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress)
{
    KERN_DrawRectangle(10, 10, 40, 40, GREEN, GREY);

    KERN_DrawHorizontalLine(5, 5, 310, DARKRED);
    KERN_DrawVerticalLine(5, 5, 190, GREEN);
    KERN_DrawVerticalLine(315, 5, 190, GREEN);
    KERN_DrawHorizontalLine(5,195, 311, DARKRED);
    
    KERN_WaitSeconds(2);

    KERN_DrawLine(5, 5, 50, 50, YELLOW);

    KERN_DrawCircle(80, 80, 12, LIGHTCYAN, ORANGE);

    for(;;);
}