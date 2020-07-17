

// void RegulatorT(int PIN, int Tin, int Tset, int Tdelta)
// {
//   //Если Текущая температура меньше Уставки-Дельта
//   if (Tin <= Tset - Tdelta)
//   {
//     PIN=HIGH; // Включить реле
//     flag_RELAY1 = true;
//     //Serial.print(" RelayT1 ON ");
//   }

//   // иначе если Текущая температура выше Устави+Дельта
//   else if (Tin >= Tset - Tdelta)
//   {
//     PIN=LOW; // Выключить реле
//     flag_RELAY1 = false;
//     //Serial.print(" RelayT1 OFF ");
//   }
// }//RegulatorT

// // Аварийный нагреватель
// void AlarmTemp(int PIN, int Tin, int TempStart, int TempStop)
// {
//   // Если текущая температура меньше или равно Температуры Включения
//   if (Tin >= TempStart)
//   {
//    PIN=HIGH; // Включить реле
//   // Mega.writeSingleRegister(32,HIGH);
//     flag_RELAY2_Alarm = true;
//     //Serial.print(" RelayT Alarm 2 ON ");
//   }

//   // Если текущая температура больше или равно Температура Выключения
//   if (Tin <= TempStop)
//   {
//     PIN=LOW; // Выключить реле
//     flag_RELAY2_Alarm = false;
// //    Mega.writeSingleRegister(32,LOW);
//     //Serial.print(" RelayT Alarm 2 OFF ");
//   }
// }

// // Логика работы устройства
// // Мы просто цыклично вызываем эту функцию
// void logic()
// {
//   if (flag_AutoManual == true) // Если включен автоматический режим
//   {
//     int i = 0;
//     // Проверяем какой сейчас таймер Активен и не равен ли он "нулю"
//     // и выбираем соответствующий номер уставки для регулятора температуры
//     // Условия вызываются последовательно и в случае верности изменят i
//     if (TimerRTC > 0 && TimerTuning[3] != 0) {
//       i = 3;
//     }
//     if (TimerRTC > TimerTuning[0] && TimerTuning[0] != 0) {
//       i = 0;
//     }
//     if (TimerRTC > TimerTuning[1] && TimerTuning[1] != 0) {
//       i = 1;
//     }
//     if (TimerRTC > TimerTuning[2] && TimerTuning[2] != 0) {
//       i = 2;
//     }
//     if (TimerRTC > TimerTuning[3] && TimerTuning[3] != 0) {
//       i = 3;
//     }

//     // Проверяем не равны ли все Таймеры 0
//     uint32_t check = 0;
//     for (int j = 0; j < 4; j++) {
//       check = check + TimerTuning[j];
//     }
//     if (check != 0)
//     { flag_A_logicRegulatorT = false;
//       // PIN - Пин выходного устройства // Tin - Температрура от датчика
//       // Tset - Какую темпратуру поддерживать // Tdelta - Дельта или Гистерезис
//       RegulatorT(RELAY1PIN, Temp_in, TempTuning[i], Delta);
//     }
//     else
//     {
//       RELAY1PIN=LOW;  // Выключить реле
//       flag_A_logicRegulatorT = true;
//     }
//   }
//   else
//   {
//     RELAY1PIN=LOW;  // Выключить реле
//     flag_RELAY1 = false;
//   }

//   // Аварийный нагреватель нельзя выключить,
//   // только если уравнять значения AlarmTempStart и AlarmTempStop
//   AlarmTemp(RELAY2PIN, Temp_in, AlarmTempStart, AlarmTempStop);
//   //VentTemp(RELAY3PIN, RELAY4PIN, TempDS18B20[0], VentTempStart, VentTempStop);
 
  
// }//logic

BLYNK_WRITE(V40){
  TempZ_1 = param.asFloat();
  EEPROM.write(40, TempZ_1);
  EEPROM.end();
   flag_send = true;
  DATA_Send();
}

BLYNK_WRITE(V41){
  TempZ_2 = param.asFloat();
  EEPROM.write(41, TempZ_2);
  EEPROM.end();
   flag_send = true;
  DATA_Send();
}

BLYNK_WRITE(V42){
  TempZ_3 = param.asFloat();
  EEPROM.write(42, TempZ_3);
  EEPROM.end();
   flag_send = true;
  DATA_Send();
}

BLYNK_WRITE(V43){
  TempZ_4 = param.asFloat();
  EEPROM.write(43, TempZ_4);
  EEPROM.end();
   flag_send = true;
  DATA_Send();
}

BLYNK_WRITE(V55){
  heat = param.asInt();
  flag_send = true;
//  DATA_Send();
}



void S_led() {
  if (flagZ_1)
  {
    led1.on();
    // terminal.println("led1.on:"+ String(flagZ_1));
    //   terminal.flush();
  }
  else
  {
    led1.off();
    //  terminal.println("led1.off:"+ String(flagZ_1));
    //   terminal.flush();
  }
  if (flagZ_2)
  {
    led2.on();
    //  terminal.println("led2.on:"+ String(flagZ_2));
    //   terminal.flush();
  }
  else
  {
    led2.off();
    //  terminal.println("led2.off:"+ String(flagZ_2));
    //   terminal.flush();
  }
if (flagZ_3)
  {
    led3.on();
    //  terminal.println("led3.on:"+ String(flagZ_3));
    //   terminal.flush();
  }
  else
  {
    led3.off();
    //  terminal.println("led3.off:"+ String(flagZ_3));
    //   terminal.flush();
  }
  if (flagZ_4)
  {
    led4.on();
    //  terminal.println("led4.on:"+ String(flagZ_4));
    //   terminal.flush();
  }
  else
  {
    led4.off();
    //  terminal.println("led4.off:"+ String(flagZ_4));
    //   terminal.flush();
  }
}
