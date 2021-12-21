#pragma once

#include <stdint.h>

void MemsetBuffer(char* buffer, uint8_t value, uint64_t size);
void FormatString(char* dst, char* str, ...);