#pragma once

#include "common.h"
#include "windows.h"

#include <stdint.h>

typedef struct _systemAPI{
    //common
    SystemContext* (*GetSystemContext)(void);
    //math
    int32_t (*MathSqrt)(int32_t);
    //heap
    void* (*MallocHeap)(uint64_t);
    void (*FreeHeap)(void*);
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