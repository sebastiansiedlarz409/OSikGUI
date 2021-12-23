#pragma once

#include <stdint.h>

//palette for 256 colors
#define BLACK 0x00
#define BLUE 0x01
#define DARKGREEN 0x02
#define CYAN 0x03
#define DARKRED 0x04
#define MAGENTA 0x05
#define BROWN 0x06
#define LIGHTBLACK 0x07
#define DARKGREY 0x08
#define BRIGHTBLUE 0x09
#define LIGHTGREEN 0x0A
#define LIGHTCYAN 0x0B
#define LIGHTRED 0x0C
#define LIGHTMAGENTA 0x0D
#define LIGHTYELLOW 0x0E
#define WHITE 0x0F
#define GREY0 0x10
#define GREY1 0x11
#define GREY2 0x12
#define GREY3 0x13
#define GREY4 0x14
#define GREY5 0x15
#define GREY6 0x16
#define GREY7 0x17
#define GREY8 0x18
#define GREY9 0x19
#define GREYA 0x1A
#define GREYB 0x1B
#define GREYC 0x1C
#define GREYD 0x1D
#define GREYE 0x1E
#define GREYF 0x1F
#define LIGHTBLUE 0x20
#define HANPURPLE 0x21
#define ELECTRICINDIGO 0x22
#define ELECTRICPURPLE 0x23
#define FUCHSIA 0x24
#define HOTMAGENTA 0x25
#define DEEPPINK 0x26
#define TORCHRED 0x27
#define RED 0x28
#define ORANGERED 0x29
#define DARKORANGE 0x2A
#define AMBER 0x2B
#define YELLOW 0x2C
#define ELECTRICLIME 0x2D
#define CHARTREUSEGREEN 0x2E
#define HARLEQUINGREEN 0x2F
#define GREEN 0x30
#define MALACHITE 0x31
#define SPRINGGREEN 0x32
#define MEDIUMSPRINGGREEN 0x33
#define AQUA 0x34
#define DEEPSKYBLUE 0x35
#define DODGERBLUE 0x36
#define NAVYBLUE 0x37
#define LIGHTSLATEBLUE 0x38
#define SLATEBLUE 0x39
#define HELIOTROPE 0x3A
#define LIGHTHELIOTROPE 0x3B
#define FUCHSIAPINK 0x3C
#define PERSIAPINK 0x3D
#define PALEMAGENTA 0x3E
#define PINK

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
void DrawString(int x, int y, const char* str, uint8_t font_size, uint8_t color, uint8_t background);
void ClearFullScreen(void);
void ClearPartScreen(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey);
void FillScreen(uint8_t color);
void DrawProgressBar(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t percent, uint8_t border_color, uint8_t fill_color);