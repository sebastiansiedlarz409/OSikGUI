#pragma once

#include <stdint.h>

//palette for 256 colors
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
#define LIGHTGREEN 0x0A
#define LIGHTCYAN 0x0B
#define LIGHTORANGE 0x0C
#define LIGHTPINK 0x0D
#define YELLOW 0x0E
#define WHITE 0x0F
//---
#define RED 0x28
#define ORANGE 0x29
#define GREEN 0x30

//palette for 16 colors
/*#define BLACK 0x0
#define DRED 0x1
#define DGREEN 0x2
#define DYELLOW 0x3
#define DBLUE 0x4
#define DPURPLE 0x5
#define DCYAN 0x6
#define DGREY 0x7
#define GREY 0x8
#define RED 0x9
#define GREEN 0xA
#define YELLOW 0xB
#define BLUE 0xC
#define PURPLE 0xD
#define CYAN 0xE
#define WHITE 0xF*/

//size for 256 colors
/*#define HEIGHT 200
#define WIDTH 320*/

//size for 16 colors
/*#define HEIGHT 640
#define WIDTH 480*/

//size for vesa mode
#define HEIGHT 1200
#define WIDTH 1600

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure VESA_MODEINFO;

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