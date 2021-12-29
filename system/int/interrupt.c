#include "../include/interrupt.h"
#include "../include/pic.h"

#include <stdint.h>

IDTE table[256];

extern void DefaultError_Wrapper(void);
extern void DivideError_Wrapper(void);
extern void KeyboardInt_Wrapper(void);

uint16_t SetEntryFlag(uint8_t ist, uint8_t type, uint8_t dpl, uint8_t p){
    return (uint16_t)(ist | (type << 8) | (dpl << 13) | (p << 15));
}

void InsertEntry(IDTE* idte, uint64_t address, uint8_t ist, uint8_t type, uint8_t dpl, uint8_t p){
    idte->offset_63_32 = (address >> 32);
    idte->offset_31_16 = ((address & 0xFFFF0000) >> 16);
    idte->offset_15_0 = (address & 0xFFFF);
    idte->flags = SetEntryFlag(ist, type, dpl, p);
    idte->seg_selector = 0x8;
}

void InitInterrupt(void){
    for(int i = 0; i<256;i++){
        InsertEntry(&table[i], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1);
    }
    
    InsertEntry(&table[0], (uint64_t)DivideError_Wrapper, 0, 0xE, 0, 1);
    InsertEntry(&table[8], (uint64_t)DefaultError_Wrapper, 0, 0xE, 0, 1); //pit
    InsertEntry(&table[9], (uint64_t)KeyboardInt_Wrapper, 0, 0xE, 0, 1); //keyboard

    //INTEL 3A, page 200
    IDTP idtp = {
        256*16-1,
        (uint64_t)&table
    };

    InitPIC(0x8, 0x70); //default values

    __asm("lidt %0" : : "m"(idtp));
    __asm("sti");
}