#include "../include/drawing.h"
#include "../include/common.h"
#include "../include/font.h"
#include "../include/math.h"
#include "../include/string.h"

#include <stdint.h>

void RefreshScreen(void){
    //paging map 0x10000000 to 0xFD000000 where frame buffer is
    char* frame = (char*)0x10000000;
    char* buffer = (char*)0x10200000;

    MemcpyBuffers(frame, buffer, WIDTH*961);
}

void DrawPixel(uint16_t x, uint16_t y, COLORS color){
    uint8_t* frame = (uint8_t*)0x10200000;

    frame[(y*WIDTH)+x] = color;
}

void DrawHorizontalLine(uint16_t x, uint16_t y, uint16_t len, COLORS color){
    len+=x;
    for(uint16_t i = x;i<len;i++){
        DrawPixel(i, y, color);
    }
}

void DrawVerticalLine(uint16_t x, uint16_t y, uint16_t len, COLORS color){
    len+=y;
    for(uint16_t i = y;i<len;i++){
        DrawPixel(x, i, color);
    }
}

void DrawLine(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, COLORS color){
    uint16_t dx = ex - sx;
    uint16_t dy = ey - sy;

    for(uint16_t i = sx; i<ex;i++){
        uint16_t y = sy + dy * (i - sx) / dx;
        DrawPixel(i, y, color);
    }
}

void DrawRectangle(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, COLORS border_color, COLORS fill_color){
    //border
    ex--;
    ey--;
    
    DrawHorizontalLine(sx, sy, ex-sx, border_color); //top
    DrawHorizontalLine(sx, ey, ex-sx, border_color); //bottom

    DrawVerticalLine(sx, sy, ey-sy, border_color); //left
    DrawVerticalLine(ex, sy, ey-sy+1, border_color); //right

    //fill
    for(uint16_t i = sy+1; i<ey;i++){
        DrawHorizontalLine(sx+1, i, ex-sx-1, fill_color);
    }
}

void DrawCircle(uint16_t x, uint16_t y, uint16_t r, COLORS border_color, COLORS fill_color){
    for(uint16_t dy = 0;dy<HEIGHT;dy++){
        for(uint16_t dx = 0;dx<WIDTH;dx++){
            uint16_t distance = (uint16_t)MathSqrt((dx-x)*(dx-x)+(dy-y)*(dy-y));

            if(distance == r){
                DrawPixel(dx, dy, border_color);
            }
            else if(distance < r){
                DrawPixel(dx, dy, fill_color);
            }
        }
    }
}

void DrawQuarterCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t quarter, COLORS border_color, COLORS fill_color){
    for(uint16_t dy = 0;dy<HEIGHT;dy++){
        for(uint16_t dx = 0;dx<WIDTH;dx++){
            uint16_t distance = (uint16_t)MathSqrt((dx-x)*(dx-x)+(dy-y)*(dy-y));

            if(quarter == 4 && dx>=x && dy>=y){ //first quarter
                if(distance == r){
                    DrawPixel(dx, dy, border_color);
                }
                else if(distance < r){
                    DrawPixel(dx, dy, fill_color);
                }
            }
            else if(quarter == 3 && dx<=x && dy>=y){ //second quarter
                if(distance == r){
                    DrawPixel(dx, dy, border_color);
                }
                else if(distance < r){
                    DrawPixel(dx, dy, fill_color);
                }
            }
            else if(quarter == 2 && dx<=x && dy<=y){ //third quarter
                if(distance == r){
                    DrawPixel(dx, dy, border_color);
                }
                else if(distance < r){
                    DrawPixel(dx, dy, fill_color);
                }
            }
            else if(quarter == 1 && dx>=x && dy<=y){ //fourth quarter
                if(distance == r){
                    DrawPixel(dx, dy, border_color);
                }
                else if(distance < r){
                    DrawPixel(dx, dy, fill_color);
                }
            }
        }
    }
}

void DrawProgressBar(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t percent, COLORS border_color, COLORS fill_color){
    if(percent == 0){
        DrawRectangle(sx, sy, ex, ey, border_color, BLACK);
    }
    else if(percent == 100){
        DrawRectangle(sx, sy, ex, ey, border_color, fill_color);
    }
    else{
        DrawRectangle(sx, sy, ex, ey, border_color, BLACK);
        ex--;
        sx++;
        ey--;
        sy++;
        /*
        float pr = percent;
        float temp = pr/100;
        uint16_t p = (ex-sx)*temp;
        */
        uint16_t p = ((ex-sx)*percent)/100;

        DrawRectangle(sx, sy, sx+p, ey, fill_color, fill_color);
    }
}

void DrawChar(uint16_t x, uint16_t y, char chr, uint8_t font_size, COLORS color, COLORS background){
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
            		DrawRectangle(x+i*font_size, y+j*font_size, x+i*font_size+font_size, y+j*font_size+font_size, color, color);
            }
            else if(background == 0)
            {
            	if(font_size == 1)
					DrawPixel(x+i, y+j, background);
				else
					DrawRectangle(x+i*font_size, y+j*font_size, x+i*font_size, y+j*font_size, background, background);
            }
        }
    }
}

void DrawString(int x, int y, const char* str, uint8_t font_size, COLORS color, COLORS background)
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

void FillScreen(COLORS color){
    for(uint16_t y = 0;y<HEIGHT;y++){
        for(uint16_t x = 0;x<WIDTH;x++){
            DrawPixel(x, y, color);
        }
    }
}

void ClearFullScreen(void){
    FillScreen(BLACK);
}

void ClearPartScreen(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey){
    DrawRectangle(sx, sy, ex, ey, BLACK, BLACK);
}