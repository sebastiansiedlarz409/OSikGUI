#include "windows.h"
#include "drawing.h"
#include "common.h"
#include "string.h"
#include "heap.h"
#include "menu.h"

#include <stdint.h>

#define TITLE_BAR_WIDTH 25

WindowContext* CreateWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, const char* title, COLORS theme,
                                    COLORS backgroud, COLORS font_color){
    //prepare window context
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->id = ++GetSystemContext()->lastUsedWindowId;
    context->x = sx;
    context->y = sy;
    context->w = width;
    context->h = height;
    context->theme = theme;
    context->background = backgroud;
    context->font_color = font_color;
    context->parent = parent;
    context->childrenCount = 0;
    context->content = NULL;
    context->font_size = 0;

    MemcpyBuffers(context->title, (char*)title, StringLength((char*)title)+1);

    if(parent != NULL){
        parent->children[parent->childrenCount] = context;
        parent->childrenCount++;
    }

    return context;
}

WindowContext* CreateTextWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, COLORS backgroud, COLORS font_color, uint8_t font_size){
    //prepare window context
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->id = ++GetSystemContext()->lastUsedWindowId;
    context->x = sx;
    context->y = sy;
    context->background = backgroud;
    context->font_color = font_color;
    context->parent = parent;
    context->childrenCount = 0;
    context->content = NULL;
    context->font_size = font_size;

    if(parent != NULL){
        parent->children[parent->childrenCount] = context;
        parent->childrenCount++;
    }

    return context;
}

WindowContext* CreateProgressBarWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, COLORS border_color, COLORS fill_color){
    //prepare window context
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->id = ++GetSystemContext()->lastUsedWindowId;
    context->x = sx;
    context->y = sy;
    context->w = ex-sx;
    context->h = ey-sy;
    context->fill_color = fill_color;
    context->border_color = border_color;
    context->parent = parent;
    context->childrenCount = 0;

    if(parent != NULL){
        parent->children[parent->childrenCount] = context;
        parent->childrenCount++;
    }

    return context;
}

void DrawTextWindow(WindowContext* context, const char* str){
    if(context->parent != NULL){
        if(context->w > context->parent->w-context->x-10){
            context->w = context->parent->w-context->x-10;
        }
        if(context->h > context->parent->h-context->y-10){
            context->h = context->parent->h-context->y-10;
        }
        if(context->x<context->parent->x+10){
            context->x+=10;
        }
        if(context->y<context->parent->y+10){
            context->y=context->parent->y+10;
        }
    }

    //save data in context
    context->content = (char*)MallocHeap(StringLength((char*)str)+1);
    MemcpyBuffers(context->content, (char*)str, StringLength((char*)str)+1);

    DrawString(context->x, context->y+TITLE_BAR_WIDTH, str, context->font_size, context->theme,
                context->background);
}

void DrawProgressBarWindow(WindowContext* context, uint8_t percent){
    if(context->parent != NULL){
        if(context->w > context->parent->w-context->x-10){
            context->w = context->parent->w-context->x-10;
        }
        if(context->h > context->parent->h-context->y-10){
            context->h = context->parent->h-context->y-10;
        }
        if(context->x<context->parent->x+10){
            context->x+=10;
        }
        if(context->y<context->parent->y+10){
            context->y=context->parent->y+10;
        }
    }

    DrawProgressBar(context->x, context->y+TITLE_BAR_WIDTH*2, context->x+context->w, context->y+context->h+TITLE_BAR_WIDTH*2, percent, 
                    context->border_color, context->fill_color);
}

void DrawButtonWithDescWindow(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, const char* title,
                         const char* desc, COLORS border_color, COLORS fill_color){

    DrawRectangle(sx, sy, ex, ey, border_color, fill_color);

    //title
    DrawString(sx+10, sy+10, title, 4, RED, BLACK);

    //desc
    DrawString(sx+10, sy+30, desc, 1, RED, BLACK);
}

void DrawTitleBar(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t width, const char* title, 
                    COLORS theme, COLORS font_color){
    DrawRectangle(sx, sy, sx+width, sy+TITLE_BAR_WIDTH, theme, theme);
    
    //title
    DrawString(sx+8, sy+4, title, 2, font_color, theme);

    //icons
    DrawCircle(sx+width-15, sy+12, 6, theme == BRIGHTBLUE ? RED : BRIGHTBLUE, theme == RED ? BROWN : RED);

    //draw rounded window corners
    //dont draw it when drawing main window
    DrawRectangle(sx, sy, sx+7, sy+7, parent->background, parent->background);
    DrawRectangle(sx+width-7, sy, sx+width, sy+7, parent->background, parent->background);
    DrawQuarterCircle(sx+7,sy+7, 7, 2, theme, theme);
    DrawQuarterCircle(sx+width-8, sy+7, 7, 1, theme, theme);
}

void DrawWindow(WindowContext* context){
    //cut when too height or too wide
    //10px margin
    if(context->parent != NULL){
        if(context->w > context->parent->w-context->x-10){
            context->w = context->parent->w-context->x-10;
        }
        if(context->h > context->parent->h-context->y-10){
            context->h = context->parent->h-context->y-10;
        }
        if(context->x<context->parent->x+10){
            context->x+=10;
        }
        if(context->y<context->parent->y+TITLE_BAR_WIDTH+10){
            context->y=context->parent->y+TITLE_BAR_WIDTH+10;
        }
    }

    //set last created window
    GetSystemContext()->currentWindow = context;

    //whole window border
    DrawRectangle(context->x+1, context->y+1, context->x+context->w-1, context->y+context->h, context->theme, context->background);

    //draw title bar
    DrawTitleBar(context->parent, context->x+1, context->y+1, context->w-2, context->title, context->theme, context->font_color);
}

void CloseWindow(WindowContext* w){
    if(w->parent != NULL){
        w->parent->childrenCount--;

        DrawRectangle(w->x, w->y, w->x+w->w, w->y+w->h, w->parent->background, w->parent->background);

        for(uint32_t i = 0;i<w->childrenCount;i++){
            FreeHeap(w->children[i]);
        }

        if(w->content != NULL){
            FreeHeap(w->content);
        }

        FreeHeap(w);
    }
}