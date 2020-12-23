# 1 "C:\\Users\\E6E9F~1.KAP\\AppData\\Local\\Temp\\tmpb9ovfvwc"
#include <Arduino.h>
# 1 "C:/Users/e.kapitonov/Documents/PlatformIO/Projects/esp/src/esp.ino"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoOTA.h>
WidgetTerminal terminal(V8);
WidgetLED led1(V44), led2(V45), led3(V46), led4(V47);
#include "Settings.h"
#include "F_EEPROM.h"

#include "uart.h"

#include "obogrev.h"

#include "dosvetka.h"
#include "json.h"

#include "blynk.h"

char led;
void setup();
void loop();
#line 22 "C:/Users/e.kapitonov/Documents/PlatformIO/Projects/esp/src/esp.ino"
void setup()
{
  Serial.begin(115200);
  setup_uart();
  EEPROM_READ();
  setup_blynk();

  reconnectBlynk();
  terminal.clear();
  ArduinoOTA.setHostname("ESPTeplica");

  ArduinoOTA.begin();

 }

void loop()
{
  ArduinoOTA.handle();
  ms=millis();
  rssi = map(WiFi.RSSI(), -105, -35, 0, 100);
   loopBlynk();

    logic();
   S_led();







}