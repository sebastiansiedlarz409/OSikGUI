#pragma once

#include "common.h"
#include "windows.h"

#include <stdint.h>

typedef struct _systemAPI{
    //common
    SystemContext* (*GetSystemContext)(void);
    void (*WaitSeconds)(uint64_t seconds);
    //math
    int32_t (*MathSqrt)(int32_t);
    //heap
    void* (*MallocHeap)(uint64_t);
    void (*FreeHeap)(void*);
    //stream
    void (*PushInStream)(uint8_t value);
    uint8_t (*PopInStream)(void);
    uint16_t (*GetInStreamSize)(void);
    void (*FlushInStream)(void);
    //string
    uint64_t (*StringLength)(char*);
    void (*MemcpyBuffers)(char*, char*, uint64_t);
    void (*MemsetBuffer)(char*, uint8_t, uint64_t);
    void (*FormatString)(char*, char*, ...);
    //drawing
    void (*RefreshScreen)(void);
    void (*RefreshPartOfScreen)(uint16_t, uint16_t, uint16_t, uint16_t);
    void (*DrawPixel)(uint16_t, uint16_t, COLORS);
    void (*DrawHorizontalLine)(uint16_t, uint16_t, uint16_t, COLORS);
    void (*DrawVerticalLine)(uint16_t, uint16_t, uint16_t, COLORS);
    void (*DrawLine)(uint16_t, uint16_t,uint16_t, uint16_t, COLORS);
    void (*DrawWLine)(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, COLORS);
    void (*DrawRectangle)(uint16_t, uint16_t,uint16_t, uint16_t, COLORS, COLORS);
    void (*DrawQuarterCircle)(uint16_t, uint16_t, uint16_t, uint8_t, COLORS, COLORS);
    void (*DrawCircle)(uint16_t, uint16_t, uint16_t, COLORS, COLORS);
    void (*DrawWCircle)(uint16_t, uint16_t, uint16_t, uint16_t, COLORS, COLORS);
    void (*DrawChar)(uint16_t, uint16_t, char, uint8_t, COLORS, COLORS );
    void (*DrawString)(int, int, const char*, uint8_t, COLORS, COLORS );
    void (*ClearFullScreen)(void);
    void (*ClearPartScreen)(uint16_t, uint16_t, uint16_t, uint16_t);
    void (*FillScreen)(COLORS);
    void (*DrawProgressBar)(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, COLORS, COLORS);
    //windows
    WindowContext* (*CreateWindowContext)(WindowContext*, uint16_t, uint16_t, uint16_t, uint16_t,
                                     const char*, COLORS, COLORS,
                                      COLORS, void (*onInputStreamPushHandler)(WindowContext*));
    WindowContext* (*CreateTextWindowContext)(WindowContext*, uint16_t, uint16_t, COLORS,
                                        COLORS, uint8_t);
    WindowContext* (*CreateProgressBarWindowContext)(WindowContext*, uint16_t, uint16_t, uint16_t, uint16_t,
                                        COLORS, COLORS);
    WindowContext* (*CreateDescButtonWindowContext)(WindowContext*, uint16_t, uint16_t, uint16_t, uint16_t,
                            COLORS, COLORS, COLORS, uint8_t);
    void (*CloseWindow)(WindowContext*);
    void (*DrawWindow)(WindowContext*);
    void (*DrawProgressBarWindow)(WindowContext*, uint8_t);
    void (*DrawTextWindow)(WindowContext*, const char*);
    void (*DrawDescButtonWindow)(WindowContext*, const char*);
} SystemAPI;

void InitAPI(void);