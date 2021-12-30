#pragma once

#include <stdint.h>

//palette for 256 colors
typedef enum _COLORS {
    NOCOLOR = -0x01,
    BLACK = 0x00,
    BLUE = 0x01,
    DARKGREEN = 0x02,
    CYAN = 0x03,
    DARKRED = 0x04,
    MAGENTA = 0x05,
    BROWN = 0x06,
    LIGHTBLACK = 0x07,
    DARKGREY = 0x08,
    BRIGHTBLUE = 0x09,
    LIGHTGREEN = 0x0A,
    LIGHTCYAN = 0x0B,
    LIGHTRED = 0x0C,
    LIGHTMAGENTA = 0x0D,
    LIGHTYELLOW = 0x0E,
    WHITE = 0x0F,
    GREY0 = 0x10,
    GREY1 = 0x11,
    GREY2 = 0x12,
    GREY3 = 0x13,
    GREY4 = 0x14,
    GREY5 = 0x15,
    GREY6 = 0x16,
    GREY7 = 0x17,
    GREY8 = 0x18,
    GREY9 = 0x19,
    GREYA = 0x1A,
    GREYB = 0x1B,
    GREYC = 0x1C,
    GREYD = 0x1D,
    GREYE = 0x1E,
    GREYF = 0x1F,
    LIGHTBLUE = 0x20,
    HANPURPLE = 0x21,
    ELECTRICINDIGO = 0x22,
    ELECTRICPURPLE = 0x23,
    FUCHSIA = 0x24,
    HOTMAGENTA = 0x25,
    DEEPPINK = 0x26,
    TORCHRED = 0x27,
    RED = 0x28,
    ORANGERED = 0x29,
    DARKORANGE = 0x2A,
    AMBER = 0x2B,
    YELLOW = 0x2C,
    ELECTRICLIME = 0x2D,
    CHARTREUSEGREEN = 0x2E,
    HARLEQUINGREEN = 0x2F,
    GREEN = 0x30,
    MALACHITE = 0x31,
    SPRINGGREEN = 0x32,
    MEDIUMSPRINGGREEN = 0x33,
    AQUA = 0x34,
    DEEPSKYBLUE = 0x35,
    DODGERBLUE = 0x36,
    NAVYBLUE = 0x37,
    LIGHTSLATEBLUE = 0x38,
    SLATEBLUE = 0x39,
    HELIOTROPE = 0x3A,
    LIGHTHELIOTROPE = 0x3B,
    FUCHSIAPINK = 0x3C,
    PERSIAPINK = 0x3D,
    PALEMAGENTA = 0x3E,
    PINK = 0x3F,
} COLORS;

//size for vesa mode
#define HEIGHT 1200
#define WIDTH 1600

void RefreshScreen(void);
void RefreshPartOfScreen(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);
void DrawPixel(uint16_t x, uint16_t y, COLORS color);
void DrawHorizontalLine(uint16_t x, uint16_t y, uint16_t len, COLORS color);
void DrawVerticalLine(uint16_t x, uint16_t y, uint16_t len, COLORS color);
void DrawLine(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, COLORS color);
void DrawWLine(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t width, COLORS color);
void DrawRectangle(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey, COLORS border_color, COLORS fill_color);
void DrawQuarterCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t quarter, COLORS border_color, COLORS fill_color);
void DrawCircle(uint16_t x, uint16_t y, uint16_t r, COLORS border_color, COLORS fill_color);
void DrawWCircle(uint16_t x, uint16_t y, uint16_t r1, uint16_t r2, COLORS border_color, COLORS fill_color);
void DrawChar(uint16_t x, uint16_t y, char chr, uint8_t font_size, COLORS color, COLORS background);
void DrawString(int x, int y, const char* str, uint8_t font_size, COLORS color, COLORS background);
void ClearFullScreen(void);
void ClearPartScreen(uint16_t sx, uint16_t sy,uint16_t ex, uint16_t ey);
void FillScreen(COLORS color);
void DrawProgressBar(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t percent, COLORS border_color, COLORS fill_color);