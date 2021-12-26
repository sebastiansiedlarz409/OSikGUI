#include "include/windows.h"
#include "include/drawing.h"
#include "include/common.h"
#include "include/string.h"
#include "include/heap.h"
#include "include/menu.h"

#include <stdint.h>

#define TITLE_BAR_WIDTH 25

WindowContext* CreateWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                                    const char* title, COLORS theme, COLORS backgroud, COLORS font_color,
                                    void (*onInputStreamPushHandler)(WindowContext* context)){
    //prepare window context
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->id = parent->childrenCount+1;
    context->drawn = 0;
    context->position.sx = sx;
    context->position.sy = sy;
    context->position.ex = ex;
    context->position.ey = ey;
    context->theme.theme = theme;
    context->theme.background = backgroud;
    context->font.font_color = font_color;
    context->parent = parent;
    context->childrenCount = 0;
    context->data.content = NULL;
    context->font.font_size = 0;
    context->events.onInputStreamPushHandler = onInputStreamPushHandler;

    MemcpyBuffers(context->data.title, (char*)title, StringLength((char*)title)+1);

    if(parent != NULL){
        parent->children[parent->childrenCount] = context;
        parent->childrenCount++;
    }

    return context;
}

WindowContext* CreateTextWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, COLORS backgroud,
                                     COLORS font_color, uint8_t font_size){
    //prepare window context
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->id = 0;
    context->drawn = 0;
    context->position.sx = sx;
    context->position.sy = sy;
    context->theme.background = backgroud;
    context->font.font_color = font_color;
    context->parent = parent;
    context->childrenCount = 0;
    context->data.content = NULL;
    context->font.font_size = font_size;

    if(parent != NULL){
        parent->children[parent->childrenCount] = context;
        parent->childrenCount++;
    }

    return context;
}

WindowContext* CreateProgressBarWindowContext(WindowContext* parent, uint16_t sx, uint16_t sy, uint16_t ex,
                                             uint16_t ey, COLORS border_color, COLORS fill_color){
    //prepare window context
    WindowContext* context = (WindowContext*)MallocHeap(sizeof(WindowContext));
    context->id = 0;
    context->drawn = 0;
    context->position.sx = sx;
    context->position.sy = sy;
    context->position.ex = ex;
    context->position.ey = ey;
    context->theme.fill_color = fill_color;
    context->theme.border_color = border_color;
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
    context->drawn = 0;
    context->position.sx = sx;
    context->position.sy = sy;
    context->position.ex = ex;
    context->position.ey = ey;
    context->theme.fill_color = fill_color;
    context->theme.border_color = border_color;
    context->font.font_color = font_color;
    context->font.font_size = font_size;
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
        context->position.sx+=(context->parent->position.sx);
        context->position.sy+=(context->parent->position.sy+TITLE_BAR_WIDTH);
    }

    if(context->data.content != NULL){
        FreeHeap(context->data.content);
    }

    context->drawn=1;

    //save data in context
    context->data.content = (char*)MallocHeap(StringLength((char*)str)+1);
    MemsetBuffer(context->data.content, 0, StringLength((char*)str)+1);
    MemcpyBuffers(context->data.content, (char*)str, StringLength((char*)str)+1);

    DrawString(context->position.sx, context->position.sy, str, context->font.font_size, context->font.font_color,
                context->theme.background);

    RefreshScreen();
}

void DrawProgressBarWindow(WindowContext* context, uint8_t percent){
    if(context->parent != NULL && context->drawn == 0){
        context->position.ex+=context->parent->position.sx;
        context->position.ey+=(context->parent->position.sy+TITLE_BAR_WIDTH);
        if(context->position.ex > context->parent->position.ex-10){
            context->position.ex = context->parent->position.ex-10;
        }
        if(context->position.ey > context->parent->position.ey-10){
            context->position.ey = context->parent->position.ey-10;
        }
        context->position.sx+=(context->parent->position.sx);
        context->position.sy+=(context->parent->position.sy+TITLE_BAR_WIDTH);
    }

    context->drawn = 1;

    DrawProgressBar(context->position.sx, context->position.sy, context->position.ex, context->position.ey, percent, 
                    context->theme.border_color, context->theme.fill_color);
    
    RefreshScreen();
}

void DrawDescButtonWindow(WindowContext* context, const char* desc){
    if(context->parent != NULL && context->drawn == 0){
        context->position.ex+=context->parent->position.sx;
        context->position.ey+=(context->parent->position.sy+TITLE_BAR_WIDTH);
        if(context->position.ex > context->parent->position.ex-10){
            context->position.ex = context->parent->position.ex-10;
        }
        if(context->position.ey > context->parent->position.ey-10){
            context->position.ey = context->parent->position.ey-10;
        }
        context->position.sx+=(context->parent->position.sx);
        context->position.sy+=(context->parent->position.sy+TITLE_BAR_WIDTH);
    }

    context->drawn = 1;

    context->data.content = (char*)MallocHeap(StringLength((char*)desc)+1);
    MemcpyBuffers(context->data.content, (char*)desc, StringLength((char*)desc)+1);

    DrawRectangle(context->position.sx, context->position.sy, context->position.ex, context->position.ey,
                context->theme.border_color, context->theme.fill_color);

    //desc
    DrawString(context->position.sx+10, context->position.sy+30, desc, context->font.font_size,
                context->font.font_color, context->parent->theme.background);
    
    RefreshScreen();
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
    DrawRectangle(sx, sy, sx+7, sy+7, parent->theme.background, parent->theme.background);
    DrawRectangle(sx+width-7, sy, sx+width, sy+7, parent->theme.background, parent->theme.background);
    DrawQuarterCircle(sx+7,sy+7, 7, 2, theme, theme);
    DrawQuarterCircle(sx+width-8, sy+7, 7, 1, theme, theme);
}

void DrawWindow(WindowContext* context){
    //cut when too height or too wide
    //10px margin
    if(context->parent != NULL){
        if(context->position.ex > context->parent->position.ex-10){
            context->position.ex = context->parent->position.ex-10;
        }
        if(context->position.ey > context->parent->position.ey-10){
            context->position.ey = context->parent->position.ey-10;
        }
        if(context->position.sx<context->parent->position.sx+10){
            context->position.sx+=10;
        }
        if(context->position.sy<context->parent->position.sy+TITLE_BAR_WIDTH+10){
            context->position.sy=context->parent->position.sy+TITLE_BAR_WIDTH+10;
        }
    }

    //set last created window
    GetSystemContext()->currentWindow = context;
    GetSystemContext()->currentWidowId = context->id-1;

    //whole window border
    DrawRectangle(context->position.sx+1, context->position.sy+1, context->position.ex-1, context->position.ey,
                context->theme.theme, context->theme.background);

    //draw title bar
    DrawTitleBar(context->parent, context->position.sx+1, context->position.sy+1,
                context->position.ex-context->position.sx-2, context->data.title, context->theme.theme,
                context->font.font_color);
    
    RefreshScreen();
}

void CloseWindow(WindowContext* w){
    if(w->parent != NULL){
        w->parent->childrenCount--;

        DrawRectangle(w->position.sx, w->position.sy, w->position.ex, w->position.ey, w->parent->theme.background,
                        w->parent->theme.background);

        for(uint32_t i = 0;i<w->childrenCount;i++){
            FreeHeap(w->children[i]);
        }

        if(w->data.content != NULL){
            FreeHeap(w->data.content);
        }

        FreeHeap(w);
        RefreshScreen();
    }
}