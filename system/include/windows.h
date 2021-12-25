#pragma once

#include "drawing.h"

#include <stdint.h>

typedef struct _WindowContext{
    uint32_t id;
    uint16_t sx;
    uint16_t sy;
    uint16_t ex;
    uint16_t ey;
    uint8_t theme;
    uint8_t background;
    uint8_t font_color;
    char title[30];
    struct _WindowContext* parent;
    struct _WindowContext* children[10];
    uint8_t childrenCount;
    char* content;
    uint8_t font_size;
    uint8_t border_color;
    uint8_t fill_color;
    void (*onInputStreamPushHandler)(struct _WindowContext* context);
} WindowContext;

WindowContext* CreateWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, const char* title, COLORS theme,
                                    COLORS backgroud, COLORS font_color, void (*onInputStreamPushHandler)(WindowContext* context));
WindowContext* CreateTextWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, COLORS backgroud, COLORS font_color, uint8_t font_size);
WindowContext* CreateProgressBarWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                                     COLORS border_color, COLORS fill_color);
WindowContext* CreateDescButtonWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                         COLORS border_color, COLORS fill_color, COLORS font_color, uint8_t font_size);
void CloseWindow(WindowContext* w);
void DrawWindow(WindowContext* context);
void DrawProgressBarWindow(WindowContext* context, uint8_t percent);
void DrawTitleBar(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, const char* title, COLORS theme, COLORS font_color);
void DrawTextWindow(WindowContext* context, const char* str);
void DrawDescButtonWindow(WindowContext* context, const char* desc);