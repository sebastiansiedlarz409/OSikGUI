#include "include/windows.h"
#include "include/drawing.h"
#include "include/common.h"
#include "include/string.h"
#include "include/heap.h"
#include "include/menu.h"

#include <stdint.h>

#define TITLE_BAR_WIDTH 25

WindowContext* CreateWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, const char* title, COLORS theme,
                                    COLORS backgroud, COLORS font_color, void (*onInputStreamPushHandler)(WindowContext* context)){
    //prepare window context
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->id = parent->childrenCount+1;
    context->sx = sx;
    context->sy = sy;
    context->ex = ex;
    context->ey = ey;
    context->drawn = 0;
    context->theme = theme;
    context->background = backgroud;
    context->font_color = font_color;
    context->parent = parent;
    context->childrenCount = 0;
    context->content = NULL;
    context->font_size = 0;
    context->onInputStreamPushHandler = onInputStreamPushHandler;

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
    context->id = 0;
    context->sx = sx;
    context->sy = sy;
    context->drawn = 0;
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
    context->id = 0;
    context->sx = sx;
    context->sy = sy;
    context->ex = ex;
    context->ey = ey;
    context->drawn = 0;
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

WindowContext* CreateDescButtonWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                        COLORS border_color, COLORS fill_color, COLORS font_color, uint8_t font_size){
    //prepare window context
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->id = 0;
    context->sx = sx;
    context->sy = sy;
    context->ex = ex;
    context->ey = ey;
    context->drawn = 0;
    context->fill_color = fill_color;
    context->border_color = border_color;
    context->font_color = font_color;
    context->font_size = font_size;
    context->parent = parent;
    context->childrenCount = 0;

    if(parent != NULL){
        parent->children[parent->childrenCount] = context;
        parent->childrenCount++;
    }

    return context;
}

void DrawTextWindow(WindowContext* context, const char* str){
    if(context->parent != NULL && context->drawn == 0){
        context->sx+=(context->parent->sx);
        context->sy+=(context->parent->sy+TITLE_BAR_WIDTH);
    }

    if(context->content != NULL){
        FreeHeap(context->content);
    }

    context->drawn=1;

    //save data in context
    context->content = (char*)MallocHeap(StringLength((char*)str)+1);
    MemsetBuffer(context->content, 0, StringLength((char*)str)+1);
    MemcpyBuffers(context->content, (char*)str, StringLength((char*)str)+1);

    DrawString(context->sx, context->sy, str, context->font_size, context->font_color,
                context->background);
}

void DrawProgressBarWindow(WindowContext* context, uint8_t percent){
    if(context->parent != NULL && context->drawn == 0){
        context->ex+=context->parent->sx;
        context->ey+=(context->parent->sy+TITLE_BAR_WIDTH);
        if(context->ex > context->parent->ex-10){
            context->ex = context->parent->ex-10;
        }
        if(context->ey > context->parent->ey-10){
            context->ey = context->parent->ey-10;
        }
        context->sx+=(context->parent->sx);
        context->sy+=(context->parent->sy+TITLE_BAR_WIDTH);
    }

    context->drawn = 1;

    DrawProgressBar(context->sx, context->sy, context->ex, context->ey, percent, 
                    context->border_color, context->fill_color);
}

void DrawDescButtonWindow(WindowContext* context, const char* desc){
    if(context->parent != NULL && context->drawn == 0){
        context->ex+=context->parent->sx;
        context->ey+=(context->parent->sy+TITLE_BAR_WIDTH);
        if(context->ex > context->parent->ex-10){
            context->ex = context->parent->ex-10;
        }
        if(context->ey > context->parent->ey-10){
            context->ey = context->parent->ey-10;
        }
        context->sx+=(context->parent->sx);
        context->sy+=(context->parent->sy+TITLE_BAR_WIDTH);
    }

    context->drawn = 1;

    context->content = (char*)MallocHeap(StringLength((char*)desc)+1);
    MemcpyBuffers(context->content, (char*)desc, StringLength((char*)desc)+1);

    DrawRectangle(context->sx, context->sy, context->ex, context->ey, context->border_color, context->fill_color);

    //desc
    DrawString(context->sx+10, context->sy+30, desc, context->font_size, context->font_color, context->parent->background);
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
        if(context->ex > context->parent->ex-10){
            context->ex = context->parent->ex-10;
        }
        if(context->ey > context->parent->ey-10){
            context->ey = context->parent->ey-10;
        }
        if(context->sx<context->parent->sx+10){
            context->sx+=10;
        }
        if(context->sy<context->parent->sy+TITLE_BAR_WIDTH+10){
            context->sy=context->parent->sy+TITLE_BAR_WIDTH+10;
        }
    }

    //set last created window
    GetSystemContext()->currentWindow = context;
    GetSystemContext()->currentWidowId = context->id-1;

    //whole window border
    DrawRectangle(context->sx+1, context->sy+1, context->ex-1, context->ey, context->theme, context->background);

    //draw title bar
    DrawTitleBar(context->parent, context->sx+1, context->sy+1, context->ex-context->sx-2, context->title, context->theme, context->font_color);
}

void CloseWindow(WindowContext* w){
    if(w->parent != NULL){
        w->parent->childrenCount--;

        DrawRectangle(w->sx, w->sy, w->ex, w->ey, w->parent->background, w->parent->background);

        for(uint32_t i = 0;i<w->childrenCount;i++){
            FreeHeap(w->children[i]);
        }

        if(w->content != NULL){
            FreeHeap(w->content);
        }

        FreeHeap(w);
    }
}