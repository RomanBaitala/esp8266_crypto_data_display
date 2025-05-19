#ifndef DISPLAY_OPERATIONS_H
#define DISPLAY_OPERATIONS_H

#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

void initDisplay();
void updateDisplay(const char* symbol, float prices[24]);

#endif