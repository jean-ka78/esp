BLYNK_WRITE(V16){
  flag_send = true;
  VentTempStart = param.asInt();
  EEPROM.write(29, VentTempStart);
  EEPROM.end();
  
  DATA_Send();
}
BLYNK_WRITE(V17){
   flag_send = true;
   VentTempStop = param.asInt();
  //Serial.println(VentTempStop);
 // Mega.writeSingleRegister(27,VentTempStop);
  EEPROM.write(30, VentTempStop);
  EEPROM.end();
 
  DATA_Send();
}
BLYNK_WRITE(V15){
  flag_send = true;
  VentTime = param.asInt();
  //Serial.println(VentTime);
 // Mega.writeSingleRegister(28,VentTime);
    EEPROM.write(31,  VentTime);
    EEPROM.end();
    
    DATA_Send();
}


void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V5, millis() / 1000);
}

// Every time we connect to the cloud...
/*
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  }
*/
// When App button is pushed - switch the state

BLYNK_WRITE(V50) {
  switch (param.asInt())
  {
    case 1: // Item 1
      terminal.println("Item 1 selected");
      terminal.flush();
      button = 1;

      break;
    case 2: // Item 2
      terminal.println("Item 2 selected");
      terminal.flush();
      button = 0;
      break;
  }
  // DATA_Send();
}

void temp_up(){
for (int i = 0; i < (sizeof(TempZ)/sizeof(TempZ[0])); i++)
{
  if (TempZ[i]>= -50 && TempZ[i] <= 70.00 && TempZ[i] != 0)
{
   Blynk.virtualWrite(V[i], TempZ[i]);
}
else
{
   Blynk.virtualWrite(V[i], "Нет датчика");
}

}
if (Temp_out >= -50 && Temp_out <= 70.00 && Temp_out != 0)
{
   Blynk.virtualWrite(V4, Temp_out);
}
else
{
   Blynk.virtualWrite(V4, "Нет датчика");
}


  
  // Blynk.virtualWrite(V1,  TempZ[1]);
  // Blynk.virtualWrite(V2,  TempZ[2]);
  // Blynk.virtualWrite(V3,  TempZ[3]);
  //Blynk.virtualWrite(V4,  Temp_out);
  Blynk.virtualWrite(V5,  Temp_in);
  Blynk.virtualWrite(V6,  Humid1);
  Blynk.virtualWrite(V22, Tmax);
  Blynk.virtualWrite(V23, Tmin);
  Blynk.virtualWrite(V33, Tmax_i);
  Blynk.virtualWrite(V34, Tmin_i);
  Blynk.virtualWrite(V7,  lux);
  Blynk.virtualWrite(V20, rssi);
  Blynk.virtualWrite(V9, NH3);
  if (flag_wind){
    Blynk.virtualWrite(V19, "Открыты");
  }
  else if (!flag_wind){
    Blynk.virtualWrite(V19, "Закрыты");
  }


}
