#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoOTA.h> // Библиотека для OTA-прошивки
WidgetTerminal terminal(V8);
WidgetLED led1(V44), led2(V45), led3(V46), led4(V47);
#include "Settings.h"
#include "F_EEPROM.h"
#include "master.h"
#include "uart.h"

#include "obogrev.h"

#include "dosvetka.h"
#include "blynk.h"
char led;

void setup() 
{
  Serial.begin(115200);
  setup_mega();
    // Следующие три строки для прошивки по воздуху
  ArduinoOTA.setHostname("ESPTeplica007"); // Задаем имя сетевого порта
  //ArduinoOTA.setPassword((const char *)"0000"); // Задаем пароль доступа для удаленной прошивки
  ArduinoOTA.begin(); // Инициализируем OTA
  
  setup_uart();
  EEPROM_READ();
  setup_blynk();
  // setupMqtt();
  reconnectBlynk(); 
  terminal.clear();
 }

void loop()
{
  ArduinoOTA.handle(); // Всегда готовы к прошивке
  ms=millis();
  rssi =  map(WiFi.RSSI(), -105, -35, 0, 100);
   loopBlynk();
  //  temp_up();
  //  logic();
   S_led(); 
  //  svet();
//   clockDisplay();
  //  loopMQtt(); 
  //  DATA_Resive();
  //  DATA_Send();
    modbus_update(); 
up_reg();
}

   
