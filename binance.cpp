#include "binance.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* symbols[] = {
  "BTCUSDT", "ETHUSDT", "BNBUSDT", "XRPUSDT", "SOLUSDT",
  "ADAUSDT", "DOGEUSDT", "DOTUSDT", "TRXUSDT", "AVAXUSDT",
  "MATICUSDT", "LINKUSDT", "LTCUSDT", "BCHUSDT", "XLMUSDT",
  "ATOMUSDT", "FILUSDT", "ETCUSDT", "HBARUSDT", "APTUSDT"
};

const uint32_t totalSymbols = sizeof(symbols) / sizeof(symbols[0]);

bool fetchBinancePrices(const char* symbol, float prices[24]) {
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  String url = "https://api.binance.com/api/v3/klines?symbol=" + String(symbol) + "&interval=1h&limit=24";
  http.begin(client, url);
  http.addHeader("User-Agent", "ESP8266");

  int httpCode = http.GET();
  if (httpCode != 200) {
    Serial.println("Failed to get data: " + String(httpCode));
    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  const size_t capacity = 24 * JSON_ARRAY_SIZE(12) + 2048;
  DynamicJsonDocument doc(capacity);
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print("deserializeJson failed: ");
    Serial.println(error.c_str());
    return false;
  }

  for (int i = 0; i < 24; i++) {
    prices[i] = doc[i][4].as<float>();
  }

  return true;
}
