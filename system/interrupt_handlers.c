#include "common.h"
#include "menu.h"
#include "bsod.h"
#include "drawing.h"
#include "keyboard.h"
#include "pic.h"
#include "interrupt_handlers.h"

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