#pragma once

#include <stdint.h>

uint64_t StringLength(char* str);
void MemcpyBuffers(char* dst, char* src, uint64_t size);
void MemsetBuffer(char* buffer, uint8_t value, uint64_t size);
void FormatString(char* dst, char* str, ...);