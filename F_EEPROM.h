#include <EEPROM.h>         
// #include "EEPROMAnything.h" // http://playground.arduino.cc/Code/EEPROMWriteAnything

// Функция чтения данных из Энергонезовисимой памяти EEPROM
void EEPROM_READ()
{
 terminal.println("EEPROM_READ_Start");
  
  int addr=0; // Номер байта EEPROM
  EEPROM.begin(512);
// Флаги адреса с 0 по 19
  flag_AutoManual = EEPROM.read(addr);   // Адрес 0
//  flag_TableStop = EEPROM.read(addr+1);  // Адрес 1

// Уставки констант с 20 по 39
  addr = 20;
  Delta = EEPROM.read(addr);             // Адрес 20
  AlarmTempStart = EEPROM.read(addr+4);  // Адрес 24 
  AlarmTempStop = EEPROM.read(addr+8);   // Адрес 28
  VentTempStart = EEPROM.read(addr+9);  //  Адрес 29
  VentTempStop = EEPROM.read(addr+10);  //  30
  VentTime = EEPROM.read(31); // 31 
  //Tmax = EEPROM.read(32);//32
  // Tmin = EEPROM.read(33);//33
  //DELAY_Backlight = EEPROM.read(34);//34
  TempZ_1 = EEPROM.read(40);
  TempZ_2 = EEPROM.read(41);
  TempZ_3 = EEPROM.read(42);
  TempZ_4 = EEPROM.read(43);

  EEPROM.write(31, VentTime);
//EEPROM.write(32, Tmax);
// EEPROM.write(33, Tmin);

EEPROM.write(40, TempZ_1);
EEPROM.write(41, TempZ_2);
EEPROM.write(42, TempZ_3);
EEPROM.write(43, TempZ_4);
// Уставки температуры c 100 по 199
//   addr = 100;
//   for (int i=0; i < 4; i++)
//   {EEPROM_readAnything(addr+i*10, TempTuning[i]);}  
// /*  
//   TempTuning[0] // Адрес 100
//   TempTuning[1] // Адрес 110
//   TempTuning[2] // Адрес 120
//   TempTuning[3] // Адрес 130
// */    
// // Уставки времени c 200 по 399
//   addr = 200;
//   for (int i=0; i < 4; i++)
//   {EEPROM_readAnything(addr+i*10, TimerTuning[i]);} 
// /*  
//   TimerTuning[0] // Адрес 200
//   TimerTuning[1] // Адрес 210
//   TimerTuning[2] // Адрес 220
//   TimerTuning[3] // Адрес 230
// */     
  EEPROM.end(); 

  terminal.println("EEPROM_READ_Stop");
}
