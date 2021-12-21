#include "pic.h"
#include "hal.h"

#include <stdint.h>

//https://wiki.osdev.org/PIC

void InitPIC(uint8_t offset1, uint8_t offset2)
{
    //save mask
    uint8_t mask1 = 0;
    uint8_t mask2 = 0;
    PortInByte(PIC1_DATA, &mask1);
    WaitIO();
    PortInByte(PIC2_DATA, &mask2);
    WaitIO();

    //init
    PortOutByte(PIC1_COMMAND, PIC_INIT);
    WaitIO();
    PortOutByte(PIC2_COMMAND, PIC_INIT);
    WaitIO();

    //set offsets
    PortOutByte(PIC1_DATA, offset1);
    WaitIO();
    PortOutByte(PIC2_DATA, offset2);
    WaitIO();

    //tell master about slave at irq2
    PortOutByte(PIC1_DATA, 4);
    WaitIO();

    //tell slave about cascade mode
    PortOutByte(PIC2_DATA, 2);
    WaitIO();

    //send mode
    PortOutByte(PIC1_DATA, PIC_MODE_8086);
    WaitIO();
    PortOutByte(PIC2_DATA, PIC_MODE_8086);
    WaitIO();

    //restore mask
    PortOutByte(PIC1_DATA, mask1);
    PortOutByte(PIC2_DATA, mask2);
}

void ClearIntPIC(void)
{
    PortOutByte(PIC1_COMMAND, PIC_END);
    PortOutByte(PIC2_COMMAND, PIC_END);
}

void DisablePIC(void)
{
    //disable pic for apic
    PortOutByte(PIC1_DATA, PIC1_DISABLE);
    PortOutByte(PIC2_DATA, PIC2_DISABLE);
}

void SetMaskPIC(uint8_t irq, uint8_t value)
{
    //save mask
    uint8_t mask1 = 0;
    uint8_t mask2 = 0;
    PortInByte(PIC1_DATA, &mask1);
    PortInByte(PIC2_DATA, &mask2);

    if (irq < 8){
        PortOutByte(PIC1_DATA, mask1 | (value << irq));
    }
    else{
        irq-=8;
        PortOutByte(PIC1_DATA, mask1 | (value << irq));
    }
}