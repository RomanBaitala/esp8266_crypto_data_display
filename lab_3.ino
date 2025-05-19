#include "display.h"
#include "buttons.h"
#include "binance.h"
#include "wifiSetup.h"

const uint32_t errorPause = 10000;
uint32_t lastTimeError = 0;
const uint32_t getDataPause = 10000;
uint32_t lastGetDataPause = 0;

uint8_t currentPairIndex = 0;
float prices[24];

void setup() {
  Serial.begin(115200);
  conWifi();
  initDisplay();
  initButtons();
}

void loop() {
  checkButtons(currentPairIndex);
  if (wasNextPressed || wasPrevPressed){
    const char* symbol = symbols[currentPairIndex];
    if (!fetchBinancePrices(symbol, prices)) {
      Serial.println("Error fetching prices");
      return;
    }

    updateDisplay(symbol, prices);
  }
  uint32_t currentTime = millis();

  if (currentTime - lastGetDataPause > getDataPause) {
    const char* symbol = symbols[currentPairIndex];
    if (!fetchBinancePrices(symbol, prices)) {
      if (currentTime - errorPause > lastTimeError){
        Serial.println("Error fetching prices");
        lastTimeError = currentTime;
      }
      return;
    }

    updateDisplay(symbol, prices);
    lastGetDataPause = currentTime;
  }
}
