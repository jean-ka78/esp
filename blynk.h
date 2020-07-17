//#define BLYNK_PRINT Serial
//#include <UIPEthernet.h>
//#include <BlynkSimpleUIPEthernet.h>
#include "Connect.h"
#include <TimeLib.h>
#include <WidgetRTC.h>
BlynkTimer timer;
WidgetRTC rtc;
//_______________________________________________________


#include "RTC_DS3231.h" // Таймер реального времени RTC (DS3231)

#include "ventel.h"
#include "poliv.h"
#include "mqtt.h"


// При подключении нашей ESP к серверу Blynk 
// выполним настройку виджетов в приложении на Планшете
BLYNK_CONNECTED() {
  if (isFirstConnect) {
    Blynk.syncAll();
    Blynk.notify("TEST STARTING!!!!");
    isFirstConnect = false;
  }
   Blynk.syncVirtual(V16,V17,V15,V50,V40,V41,V42,V43,V55,V51,V52,V55);
    //  DATA_Send();
}

void logic(){
double absTemp_in = 0;
int count = 0;
   for (int i = 0; i < (sizeof(TempZ)/sizeof(TempZ[0]));i++) 
  {
     if (TempZ[i]>= -50 & TempZ[i] <= 70.00 & TempZ[i] !=0)
     {
       absTemp_in += TempZ[i];
        count ++;
         // absTemp_in += Temp[i];
        // count ++;
        //Serial.println(" Temp_in_s: "+String(absTemp_in));
     }
      
  }
     if (count > 0) {
    absTemp_in /= count;
} else {
    // все датчики неисправны
}
       
    // absTemp_in += Temp[i];      // складываем все температуры . . .
    //absTemp_in /= (sizeof(Temp)/sizeof(Temp[0]));        // . . . усредняем их с помощью деления
  Temp_s = absTemp_in;

}

// void printDigits(int digits)
// {
//     // utility function for digital clock display: prints preceding colon and leading 0
//     u8g.print(':');
//     if(digits < 10)
//         u8g.print('0');
//     u8g.print(digits);
    
// }
// void Digits(int digits)
// {
//     // utility function for digital clock display: prints preceding colon and leading 0
//     //u8g.print(':');
//     if(digits < 10)
//         u8g.print('0');
//     u8g.print(digits);
    
// }

String digits (int Sec)
{
  String Time; // Создаем переменную Строка Time
  // int Hour = Sec/3600; // Вычисляем количество часов
  // int Min = (Sec-Hour*3600)/60; // Вычисляем количество минут
  // String SHour; // Создаем переменную Строка SHour
  // String SMin;  // Создаем переменную Строка SMin
  String S_Sec;
  
  if (Sec<10){S_Sec = "0" + String(Sec);} else {S_Sec=String(Sec);} // Если часов меньше 10 то добовляем 0 в строку
  //if (Min<10){SMin = "0" + String(Min);} else {SMin=String(Min);} // Если минут меньше 10 то добовляем 0 в строку
  
  //Time = SHour + ":" + SMin; // Собераем строку в формате время
  return S_Sec; // Возвращаем результат
}

void clockDisplay()
{
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details

  String currentTime = digits(hour()) + ":" + digits(minute()) + ":" + digits(second());
  String currentDate = digits(day()) + "." + digits(month()) + "." + year();
   Blynk.virtualWrite(V10, currentTime);
  // Send date to the App
   Blynk.virtualWrite(V11, currentDate);
   hour_t = hour();
   minute_t = minute();
   sec_t = second();
}

void setup_blynk(){
  
 
  rtc.begin();
  setSyncInterval(5 * 60); // Sync interval in seconds (5 minutes)
  timer.setInterval(5000L, reconnectBlynk);
 // timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(50, temp_up);
  timer.setInterval(10000L, activetoday);
  timer.setInterval(1000L, resetRelay); 
  timer.setInterval(50L, logic);
// timer.setInterval(5, modbus_update);
  timer.setInterval(50, svet);
  // timer.setInterval(1000L, DATA_Send);
  // timer.setInterval(500L, DATA_Resive);
   timer.setInterval(1000L, clockDisplay);
}

void loopBlynk() {
  if (Blynk.connected()) {
    Blynk.run(); 
    //Blynk.syncAll();
  }
  timer.run();
  // DATA_Resive();
}
