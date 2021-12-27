#include "../include/loader.h"
#include "../include/string.h"

#include <stdint.h>

void* LoadApp(void* address){
    uint8_t* offset = (uint8_t*)address;

    //clear apps space
    MemsetBuffer((char*)0xA00000, 0, 0x200000);

    uint8_t* PEHeader = offset+0x80;

    uint8_t sectionCount = *(uint16_t*)(PEHeader+0x6);

    uint32_t entryPoint = *(uint32_t*)(PEHeader+0x28);

    uint64_t imageBase = *(uint64_t*)(PEHeader+0x30);

    uint8_t* data = PEHeader+0x108;
    
    while(sectionCount){
        uint64_t sizeInFile = *(uint32_t*)(data+0x10);
        uint64_t dstLocation = (*(uint32_t*)(data+0xC)+imageBase);
        uint64_t srcLocation = *(uint32_t*)(data+0x14) + (uint64_t)offset;

        //copy section
        for(uint32_t i = 0;i<sizeInFile;i++){
            *((uint8_t*)dstLocation+i) = *((uint8_t*)srcLocation+i);
        }
        sectionCount--;
        data+=0x28;
    }

    return (void*)(imageBase+entryPoint);
}

void RunApp(void* entry){
    void(*app)(void) = entry;
    app();
}