#pragma once

#include "drawing.h"

#include <stdint.h>

#define MAX_CHILDREN 10

typedef struct _WindowContext{
    uint8_t drawn;
    uint8_t keys;
    void* entry;
    struct _position{        
        uint16_t sx;
        uint16_t sy;
        uint16_t ex;
        uint16_t ey;
    } position;
    struct _theme{
        uint8_t theme;
        uint8_t background;
        uint8_t border_color;
        uint8_t fill_color;
    } theme;
    struct _data{
        char title[30];
        char* content;
    } data;
    struct _font{
        uint8_t font_size;
        uint8_t font_color;
    } font;
    struct _events{    
        void (*onInputStreamPushHandler)(struct _WindowContext* context);
        void (*onFocusInHandler)(struct _WindowContext* context);
        void (*onFocusOutHandler)(struct _WindowContext* context);
    } events;
    struct _WindowContext* parent;
    struct _WindowContext* children[MAX_CHILDREN];
    uint8_t childrenCount;
} WindowContext;

WindowContext* CreateWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height,
                                     const char* title, COLORS theme, COLORS backgroud,
                                      COLORS font_color, void* entry, void (*onInputStreamPushHandler)(WindowContext* context),
                                    void (*onFocusInHandler)(WindowContext* context),
                                    void (*onFocusOutHandler)(WindowContext* context));
WindowContext* CreateTextWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, COLORS backgroud,
                                     COLORS font_color, uint8_t font_size);
WindowContext* CreateProgressBarWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                                     COLORS border_color, COLORS fill_color);
WindowContext* CreateDescButtonWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                         COLORS border_color, COLORS fill_color, COLORS font_color, uint8_t font_size);
void CloseWindow(WindowContext* w);
void DrawWindow(WindowContext* context);
void DrawProgressBarWindow(WindowContext* context, uint8_t percent);
void DrawTitleBar(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, const char* title, COLORS theme,
                 COLORS font_color);
void DrawTextWindow(WindowContext* context, const char* str);
void DrawDescButtonWindow(WindowContext* context, const char* desc);
void MarkWindow(WindowContext* context, uint8_t r);
void UnMarkWindow(WindowContext* context, uint8_t r);