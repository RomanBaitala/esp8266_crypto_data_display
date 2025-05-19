#ifndef BUTTONS_OPERATIONS_H
#define BUTTONS_OPERATIONS_H

#include <stdint.h>
#include <Arduino.h>

extern bool wasNextPressed;
extern bool wasPrevPressed;

void initButtons();
void checkButtons(uint8_t &currentPairIndex);

#endif