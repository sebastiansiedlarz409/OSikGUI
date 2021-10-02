#include "drawing.h"
#include "common.h"
#include "font.h"

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

void DrawChar(uint16_t x, uint16_t y, char chr, uint8_t font_size, uint8_t color, uint8_t background){
	if(chr > 0x7E) return; // chr > '~'

	for(uint8_t i=0; i<font[1]; i++ )
	{
        uint8_t line = (uint8_t)font[(chr-0x20) * font[1] + i + 2];

        for(int8_t j=0; j<font[0]; j++, line >>= 1)
        {
            if(line & 1)
            {
            	if(font_size == 1)
            		DrawPixel(x+i, y+j, color);
            	else
            		DrawRectangle(x+i*font_size, y+j*font_size, font_size, font_size, color, color);
            }
            else if(background == 0)
            {
            	if(font_size == 1)
					DrawPixel(x+i, y+j, background);
				else
					DrawRectangle(x+i*font_size, y+j*font_size, font_size, font_size, background, background);
            }
        }
    }
}

void DrawString(int x, int y, char* str, uint8_t font_size, uint8_t color, uint8_t background)
{
	int x_tmp = x;
	char znak;
	znak = *str;
	while(*str++)
	{
		DrawChar(x_tmp, y, znak, font_size, color, background);
		x_tmp += ((uint8_t)font[1] * font_size) + 1;
		if(background == 0)
		{
			for(uint8_t i=0; i<(font[0]*font_size); i++)
			{
				DrawPixel(x_tmp-1, y+i, BLACK);
			}
		}
		znak = *str;
	}
}