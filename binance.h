#ifndef BINANCE_OPERATIONS_H
#define BINANCE_OPERATIONS_H

#include <Arduino.h>

extern const char* symbols[];
extern const uint32_t totalSymbols;

bool fetchBinancePrices(const char* symbol, float prices[24]);

#endif