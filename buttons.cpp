#include "buttons.h"

const uint8_t buttonNext = 12;
const uint8_t buttonPrev = 14;

const uint32_t totalSymbols = 20;

bool wasNextPressed = false;
bool wasPrevPressed = false;

void initButtons() {
  pinMode(buttonNext, INPUT);
  pinMode(buttonPrev, INPUT);
}

void checkButtons(uint8_t &currentPairIndex) {
  if (digitalRead(buttonNext) == LOW && !wasNextPressed) {
    currentPairIndex = (currentPairIndex + 1) % totalSymbols;
    wasNextPressed = true;
  } else if (digitalRead(buttonNext) == HIGH) {
    wasNextPressed = false;
  }

  if (digitalRead(buttonPrev) == LOW && !wasPrevPressed) {
    currentPairIndex = (currentPairIndex == 0) ? totalSymbols - 1 : currentPairIndex - 1;
    wasPrevPressed = true;
  } else if (digitalRead(buttonPrev) == HIGH) {
    wasPrevPressed = false;
  }
}
