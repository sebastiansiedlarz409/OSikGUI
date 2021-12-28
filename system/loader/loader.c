#include "../include/loader.h"
#include "../include/string.h"
#include "../include/common.h"

#include <stdint.h>

void* LoadApp(uint8_t id){
    uint8_t* appTable = (uint8_t*)GetSystemContext()->appsTableAddress;

    appTable-=(8*(id+1));

    uint64_t address = 0x10000 + *((uint64_t*)appTable);

    uint8_t* offset = (uint8_t*)address;

    uint8_t* PEHeader = offset+0x80;

    uint8_t sectionCount = *(uint16_t*)(PEHeader+0x6);

    uint32_t entryPoint = *(uint32_t*)(PEHeader+0x28);

    uint64_t imageBase = *(uint64_t*)(PEHeader+0x30);

    uint8_t* data = PEHeader+0x108;
    
    while(sectionCount){
        uint64_t sizeInMemory = *(uint32_t*)(data+0x8);
        uint64_t sizeInFile = *(uint32_t*)(data+0x10);
        uint64_t dstLocation = (*(uint32_t*)(data+0xC)+imageBase);
        uint64_t srcLocation = *(uint32_t*)(data+0x14) + (uint64_t)offset;

        MemsetBuffer((char*)dstLocation, 0, sizeInMemory);

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