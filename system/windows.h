#pragma once

#include "drawing.h"

#include <stdint.h>

typedef struct _WindowContext{
    uint32_t id;
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint8_t theme;
    uint8_t background;
    uint8_t font_color;
    char title[30];
    struct _WindowContext* parent;
    struct _WindowContext* children[10];
    uint8_t childrenCount;
    char* content;
    uint8_t font_size;
} WindowContext;

WindowContext* CreateWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, const char* title, COLORS theme,
                                    COLORS backgroud, COLORS font_color);
WindowContext* CreateTextWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, COLORS backgroud, COLORS font_color, uint8_t font_size);
void CloseWindow(WindowContext* w);
void DrawWindow(WindowContext* context);
void DrawTitleBar(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, const char* title, COLORS theme, COLORS font_color);
void DrawText(WindowContext* context, const char* str);