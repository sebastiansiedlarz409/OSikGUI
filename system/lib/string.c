#include "../include/string.h"

#include <stdint.h>
#include <stdarg.h>

void MemsetBuffer(char* buffer, uint8_t value, uint64_t size){
    for(uint64_t i =0;i<size;i++){
        buffer[i] = value;
    }
}

void FormatString(char* dst, char* str, ...){
    va_list args;
    va_start(args, str);

    const char* backup = str;

    uint32_t position = 0;

    while (*backup != '\0')
    {
        if(*backup != '%'){
            dst[position] = *backup;
            backup++;
            position++;
        }
        else{
            backup++;

            if(*backup == 'c'){
                dst[position] = va_arg(args, uint32_t);
                backup++;
                position++;
            }
            if(*backup == 's'){
                const char* temp = va_arg(args, const char*);
                //add each character
                while(*temp!='\0'){
                    dst[position]=*temp;
                    temp++;
                    position++;
                }
                backup++;
            }
            if(*backup == 'u'){
                size_t v = va_arg(args, size_t);

                if(v == 0){
                    dst[position] = '0';
                    position++;
                }
                else{
                    char buf[24] = {0};
                    char *temp = &buf[23];
                    while (v != 0) {
                        --temp;
                        *temp = (v % 10) + '0';
                        v /= 10;
                    }
                    //add each character
                    while(*temp!='\0'){
                        dst[position]=*temp;
                        temp++;
                        position++;
                    }
                }

                backup++;
            }
            if(*backup == 'd'){
                int64_t v = va_arg(args, int32_t);
                
                if (v == (-9223372036854775807LL - 1LL)) {
                    char* temp = "-9223372036854775808";

                    while(*temp!='\0'){
                        dst[position]=*temp;
                        temp++;
                        position++;
                    }

                    continue;
                }

                if (v < 0) {
                    dst[position] = '-';
                    position++;
                    v = -v;
                }

                if (v == 0) {
                    dst[position] = '0';
                    position++;
                    backup++;
                    continue;
                }

                char buf[24] = {0};
                char *temp = &buf[23];
                while (v != 0) {
                    --temp;
                    *temp = (v % 10) + '0';
                    v /= 10;
                }

                while(*temp!='\0'){
                    dst[position]=*temp;
                    temp++;
                    position++;
                }

                backup++;
            }
            if(*backup == 'x'){
                size_t v = va_arg(args, size_t);

                uint32_t width = 0;

                if (v == 0) {
                    dst[position] = '0';
                    position++;
                    backup++;
                    continue;
                }

                uint32_t sh = 0;
                while (width < 16 - sh && (v & 0xF000000000000000ULL) == 0) {
                    sh ++;
                    v <<= 4;
                }

                while (sh < 16) {
                    size_t idx = (v & 0xF000000000000000ULL) >> 60;
                    dst[position] = "0123456789ABCDEF"[idx];
                    position++;
                    sh ++;
                    v <<= 4;
                }

                backup++;
            }
            if(*backup == '%'){
                backup++;
            }
        }
    }
    
    va_end(args);
}

void MemcpyBuffers(char* dst, char* src, uint64_t size){
    if(size%8 == 0){
        uint64_t* dst8 = (uint64_t*)dst;
        uint64_t* src8 = (uint64_t*)src;

        for(uint64_t i = 0;i<size/8;i++){
        if(dst8[i] != src8[i])
            dst8[i] = src8[i];
        }
    }
    else if(size%4 == 0){
        uint32_t* dst4 = (uint32_t*)dst;
        uint32_t* src4 = (uint32_t*)src;

        for(uint64_t i = 0;i<size/4;i++){
        if(dst4[i] != src4[i])
            dst4[i] = src4[i];
        }
    }
    else if(size%2 == 0){
        uint16_t* dst2 = (uint16_t*)dst;
        uint16_t* src2 = (uint16_t*)src;

        for(uint64_t i = 0;i<size/2;i++){
        if(dst2[i] != src2[i])
            dst2[i] = src2[i];
        }
    }
    else{
        for(uint64_t i = 0;i<size;i++){
            if(dst[i] != src[i])
                dst[i] = src[i];
        }
    }
}

uint64_t StringLength(char* str){
    uint64_t size = 0;
    while(*str++){
        size++;
    }
    return size;
}