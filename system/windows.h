#pragma once

#include <stdint.h>

typedef struct _WindowContext{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint8_t theme;
    uint8_t background;
    uint8_t font_color;
    char title[100];
    struct _WindowContext* parent;
    struct _WindowContext* children[5];
    uint8_t childrenCount;
} WindowContext;

void CloseWindow(WindowContext* w);
void CloseWindowX(WindowContext* w);
WindowContext* DrawWindow(WindowContext* ctx, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, const char* title, uint8_t theme, uint8_t backgroud, uint8_t font_color);
void DrawTitleBar(uint16_t sx, uint16_t sy, uint16_t width, const char* title, uint8_t theme, uint8_t font_color);
void DrawText(WindowContext* context, uint16_t x, uint16_t y, const char* str, uint8_t font_size, uint8_t color, uint8_t background);