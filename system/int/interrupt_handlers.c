#include "../include/common.h"
#include "../include/menu.h"
#include "../include/bsod.h"
#include "../include/drawing.h"
#include "../include/keyboard.h"
#include "../include/pic.h"
#include "../include/interrupt_handlers.h"

#include <stdint.h>

//https://wiki.osdev.org/Exceptions

void DefaultError_Handler(void *trapFrame)
{
    UNUSED(trapFrame);
    //BSOD("Unknow Error", trapFrame);
    ClearIntPIC();
}

void DivideError_Handler(void *trapFrame)
{
    UNUSED(trapFrame);
    BSOD("Divide By Zero", trapFrame);
}

void KeyboardInt_Handler(void* trapFrame)
{
    UNUSED(trapFrame);
    KeyboardHandler();
    ClearIntPIC();
}