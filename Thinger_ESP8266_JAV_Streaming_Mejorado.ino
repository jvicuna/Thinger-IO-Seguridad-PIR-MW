#include <ThingerESP8266.h>
#include "arduino_secrets.h"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int previousMW = -1;
int previousPIR = -1;
unsigned long previousMillisValue = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["led"] << digitalPin(LED_BUILTIN);

  thing["MW"] >> outputValue(digitalRead(D0));
  thing["PIR"] >> outputValue(digitalRead(D1));

  thing["millis"] >> outputValue(millis());
}

void loop() {
  thing.handle();

  int currentMW = digitalRead(D0);
  int currentPIR = digitalRead(D1);
  unsigned long currentMillisValue = millis();

  // Transmitir solo si hay un cambio en el estado de MW
  if (currentMW != previousMW) {
    previousMW = currentMW;
    thing.stream(thing["MW"]);
  }

  // Transmitir solo si hay un cambio en el estado de PIR
  if (currentPIR != previousPIR) {
    previousPIR = currentPIR;
    thing.stream(thing["PIR"]);
  }

  // Transmitir solo si hay un cambio en el valor de millis (opcional, ya que millis siempre cambia)
  //if (currentMillisValue != previousMillisValue) {
   // previousMillisValue = currentMillisValue;
  //  thing.stream(thing["millis"]);
  }
//}
