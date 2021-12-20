#include "common.h"
#include "menu.h"
#include "bsod.h"
#include "drawing.h"
#include "interrupt_handlers.h"

#include <stdint.h>

//https://wiki.osdev.org/Exceptions

void DefaultError_Handler(void *trapFrame)
{
    UNUSED(trapFrame);
    //BSOD("Unknow Error", trapFrame);
}

void DivideError_Handler(void *trapFrame)
{
    UNUSED(trapFrame);
    BSOD("Divid By Zero", trapFrame);
}

void KeyboardInt_Handler(void* trapFrame)
{
    UNUSED(trapFrame);
    //KB_Interrupt();
    //PIC_ClearInt();
}