#pragma once

#include <stdint.h>

void MemsetBuffer(uint8_t* buffer, uint8_t value, uint64_t size);
void FormatString(char* dst, char* str, ...);