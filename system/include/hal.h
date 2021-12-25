#pragma once
#include <stdint.h>

void PortOutByte(uint32_t port, uint8_t v);
void PortOutWord(uint32_t port, uint16_t v);
void PortOutDword(uint32_t port, uint32_t v);
void PortInByte(uint32_t port, uint8_t* v);
void PortInWord(uint32_t port, uint16_t* v);
void PortInDword(uint32_t port, uint32_t* v);
void WaitIO(void);