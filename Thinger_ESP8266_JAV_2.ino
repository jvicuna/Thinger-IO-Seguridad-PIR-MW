#define THINGER_SERIAL_DEBUG

#include <ThingerESP8266.h>
#include "arduino_secrets.h"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  // open serial for monitoring
  Serial.begin(115200);

  // set builtin led as output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  // add WiFi credentials
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  thing["MW"] >> outputValue(digitalRead(D0));
  thing["PIR"] >> outputValue(digitalRead(D1));

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
