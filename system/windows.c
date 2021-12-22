#include "windows.h"
#include "drawing.h"
#include "string.h"
#include "heap.h"

#include <stdint.h>

#define TITLE_BAR_WIDTH 20
#define MIN_WIDTH 80
#define MIN_HEIGHT (TITLE_BAR_WIDTH+20)

void DrawText(WindowContext* context, uint16_t x, uint16_t y, const char* str, uint8_t font_size, uint8_t color, uint8_t background){
    if(x+context->x > context->x+context->w || y+context->y+TITLE_BAR_WIDTH>context->y+context->h){
        return;
    }

    DrawString(x+context->x, y+context->y+TITLE_BAR_WIDTH, str, font_size, color,
                background);
}

void DrawButtonWithDesc(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, const char* title, const char* desc, uint8_t border_color, uint8_t fill_color){
    DrawRectangle(sx, sy, ex, ey, border_color, fill_color);

    //title
    DrawString(sx+10, sy+10, title, 4, RED, BLACK);

    //desc
    DrawString(sx+10, sy+30, desc, 1, RED, BLACK);
}

void DrawTitleBar(uint16_t sx, uint16_t sy, uint16_t width, const char* title, uint8_t theme, uint8_t font_color){
    DrawRectangle(sx, sy, sx+width, sy+TITLE_BAR_WIDTH, theme, theme);
    
    //title
    DrawString(sx+5, sy+2, title, 2, font_color, theme);

    //icons
    DrawCircle(sx+width-10, sy+10, 6, theme == RED ? BRONZE : RED, theme == RED ? BRONZE : RED);
}

WindowContext* DrawWindow(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, const char* title, uint8_t theme, uint8_t backgroud, uint8_t font_color){
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->x = sx;
    context->y = sy;
    context->w = width;
    context->h = height-260;
    context->theme = theme;
    context->background = backgroud;
    context->font_color = font_color;
    context->parent = parent;
    context->childrenCount = 0;

    if(parent != NULL){
        parent->children[parent->childrenCount] = context;
        parent->childrenCount++;
    }

    //whole window border
    DrawRectangle(sx+1, sy+1, sx+width-1, sy+height-260, theme, backgroud);

    DrawTitleBar(sx+1, sy+1, width-2, title, theme, font_color);

    return context;
}

void CloseWindow(WindowContext* w){
    if(w->childrenCount > 0){
        //WindowContext* lastChild = w->children[w->childrenCount-1];

        /*DrawRectangle(200, 200, 100, 100, 
            RED, RED);*/
        
        /*w->childrenCount--;
        char buffer[100];
        MemsetBuffer(buffer, 0, 100);
        FormatString(buffer, "ASD %u %u %u %u %u", lastChild->x, lastChild->y, lastChild->w, lastChild->h, w->childrenCount);

        DrawString(300, 300, buffer, 4, RED, GREY);*/

        return;
    }

    if(w->parent != NULL){
        DrawRectangle(w->x, w->y, w->x+w->w, w->y+w->h, w->parent->background, w->parent->background);
        return;
    }
}