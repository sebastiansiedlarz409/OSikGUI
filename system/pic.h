#pragma once

#include <stdint.h>

//https://wiki.osdev.org/PIC

enum PIC_PORTS{
    PIC1_COMMAND = 0x20,
    PIC1_DATA = 0x21,
    PIC2_COMMAND = 0xA0,
    PIC2_DATA = 0xA1
};

enum PIC_COMMANDS{
    PIC_END = 0x20,
    PIC_INIT = 0x11,
    PIC_MODE_8086 = 0x01,
    PIC1_DISABLE = 0xFD,
    PIC2_DISABLE = 0xFF
};

void InitPIC(uint8_t offset1, uint8_t offset2);
void ClearIntPIC(void);
void DisablePIC(void);
void SetMaskPIC(uint8_t irq, uint8_t value);
