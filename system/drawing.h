#pragma once

#include <stdint.h>

//palette for 256 colors
#define BLACK 0x00
#define DARKBLUE 0x01
#define DARKGREEN 0x02
#define DARKCYAN 0x03
#define DARKRED 0x04
#define DARKPURPLE 0x05
#define BRONZE 0x06
#define LIGHTGREY 0x07
#define GREY 0x08
#define CONRFLOWERBLUE 0x09
#define LIGHTGREEN 0x0A
#define LIGHTCYAN 0x0B
#define LIGHTORANGE 0x0C
#define LIGHTPINK 0x0D
#define DARKYELLOW 0x0E
#define WHITE 0x0F
//--
#define LIGHTBLACK 0x12
//--
#define DARKGREY 0x14
//--
#define BLUE 0x20
//--
#define LIGHTPURPLE 0x22
//--
#define PINK 0x24
//--
#define RED 0x28
#define ORANGE 0x29
//--
#define YELLOW 0x2C
#define GREEN 0x2F
//--
#define CYAN 0x34

//size for vesa mode
#define HEIGHT 1200
#define WIDTH 1600

void DrawPixel(uint16_t x, uint16_t y, uint8_t color);
void DrawHorizontalLine(uint16_t x, uint16_t y, uint16_t len, uint8_t color);
void DrawVerticalLine(uint16_t x, uint16_t y, uint16_t len, uint8_t color);
void DrawLine(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, uint8_t color);
void DrawRectangle(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, uint8_t border_color, uint8_t fill_color);
void DrawCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t border_color, uint8_t fill_color);
void DrawChar(uint16_t x, uint16_t y, char chr, uint8_t font_size, uint8_t color, uint8_t background);
void DrawString(int x, int y, uint8_t font_size, uint8_t color, uint8_t background, const char* str, ...);
void ClearFullScreen(void);
void ClearPartScreen(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey);
void FillScreen(uint8_t color);
void DrawProgressBar(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t percent, uint8_t border_color, uint8_t fill_color);