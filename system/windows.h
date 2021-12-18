#pragma once

#include <stdint.h>

void DrawWindow(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, const char* title, uint8_t theme, uint8_t font_color);
void DrawTitleBar(uint16_t sx, uint16_t sy, uint16_t width, const char* title, uint8_t theme);