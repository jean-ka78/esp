#include <EasyTransfer.h>
EasyTransfer ETin, ETout; 

struct Resive_DATA{ 
  float Temp1;
  float Temp2;
  float Temp3;
  float Temp4;
  float Temp5;
  float Humid;
  float NH3;
  float t_in_min;
  float t_in_max;
  float t_out_min;
  float t_out_max;
  int32_t CO2;
  int32_t lux;
  int32_t Time_on;
  int32_t Temp_on;
  int32_t Temp_off;
  bool window;
  bool flag_z1;
  bool flag_z2;
  bool flag_z3;
  bool flag_z4;
  };

//Resive_DATA  Mega;

union uart_r
{
    Resive_DATA uart_rxdata;
    byte RESIVE_ARRAY[62];
}rxdata_u;

 

struct Send_DATA
{
    float Vent_tstart;
    float Vent_tstop; 
    float Temp_z_1;
    float Temp_z_2;
    float Temp_z_3;
    float Temp_z_4;
    int16_t Vent_time;
    int16_t hour;
    int16_t minute;
    int16_t second;
    bool but_esp;
    bool relley_poliv;
    bool relley_heat;
    bool lux_relley;
    
};
//Send_DATA Esp;

union uart_tr
{
    Send_DATA uart_txdata;
    byte SEND_ARRAY[56];
};
 
uart_tr txdata_u;
void DATA_Send()
{
    // flag_send = true;
//    Blynk.syncVirtual(V16,V17,V15,V50,V40,V41,V42,V43,V55,V51,V52);
    txdata_u.uart_txdata.Vent_time = VentTime;
    txdata_u.uart_txdata.Vent_tstart = VentTempStart;
    txdata_u.uart_txdata.Vent_tstop = VentTempStop;
    txdata_u.uart_txdata.but_esp = button;
    txdata_u.uart_txdata.relley_poliv = relay;
    txdata_u.uart_txdata.relley_heat = heat;
    txdata_u.uart_txdata.lux_relley = lux_relley;
    txdata_u.uart_txdata.Temp_z_1 = TempZ_1;
    txdata_u.uart_txdata.Temp_z_2 = TempZ_2;
    txdata_u.uart_txdata.Temp_z_3 = TempZ_3;
    txdata_u.uart_txdata.Temp_z_4 = TempZ_4;
    txdata_u.uart_txdata.hour = hour_t;
    txdata_u.uart_txdata.minute = minute_t;
    txdata_u.uart_txdata.second = sec_t;
    ETout.sendData();
//    Serial.write((uint8_t*)&txdata_u.SEND_ARRAY, sizeof(txdata_u.SEND_ARRAY)); 
    flag_send = false;
}

void DATA_Resive()
{
  
   
  
  
  
  
//    while (Serial.available()>0) 
//        {
//        uint8_t len = sizeof(rxdata_u.RESIVE_ARRAY);
//        Serial.readBytes((uint8_t*)&rxdata_u.RESIVE_ARRAY, len);

//       for(int i=0; i<5; i++){
    // //remember, you could use an if() here to check for new data, this time it's not needed.
    if (!flag_send)
    {
      /* code */
    if (ETin.receiveData()){  
        TempZ[0]    = rxdata_u.uart_rxdata.Temp1;    
        TempZ[1]    = rxdata_u.uart_rxdata.Temp2;
        TempZ[2]    = rxdata_u.uart_rxdata.Temp3;
        TempZ[3]    = rxdata_u.uart_rxdata.Temp4;
        temp_on    = rxdata_u.uart_rxdata.Temp_on;
        temp_off   = rxdata_u.uart_rxdata.Temp_off;
        time_on    = rxdata_u.uart_rxdata.Time_on;
        Temp_out  = rxdata_u.uart_rxdata.Temp5;
        Humid1    = rxdata_u.uart_rxdata.Humid;
        NH3       = rxdata_u.uart_rxdata.NH3;
        Tmax      = rxdata_u.uart_rxdata.t_out_max;
        Tmin      = rxdata_u.uart_rxdata.t_out_min;
        Tmax_i    = rxdata_u.uart_rxdata.t_in_max;
        Tmin_i    = rxdata_u.uart_rxdata.t_in_min;
        CO_2      = rxdata_u.uart_rxdata.CO2;
        lux       = rxdata_u.uart_rxdata.lux;
        flag_wind = rxdata_u.uart_rxdata.window;
        flagZ_1   = rxdata_u.uart_rxdata.flag_z1;
        flagZ_2   = rxdata_u.uart_rxdata.flag_z2;
        flagZ_3   = rxdata_u.uart_rxdata.flag_z3;
        flagZ_4   = rxdata_u.uart_rxdata.flag_z4;
        

      // terminal.println("Temp_on:"+String(temp_on));
      // terminal.flush(); 
     
  if (temp_on!=VentTempStart)
{
  VentTempStart = temp_on;
  Blynk.virtualWrite(V16, VentTempStart);
  // Blynk.syncVirtual(V16);
  EEPROM.write(29, VentTempStart);
  EEPROM.end();
}
if (temp_off!=VentTempStop)
{
  VentTempStop = temp_off;
  Blynk.virtualWrite(V17, VentTempStop);
  // Blynk.syncVirtual(V17);
  EEPROM.write(30, VentTempStop);
  EEPROM.end();
}
if (time_on!=VentTime)
{
  VentTime = time_on;
  Blynk.virtualWrite(V15, VentTime);
  // Blynk.syncVirtual(V15);
  EEPROM.write(31, VentTime);
  EEPROM.end();
}}}

}




void setup_uart()
{
//  ETin.begin(details(rxdata), &Serial2);
//   ETout.begin(details(txdata), &Serial2);
  
  ETin.begin(details(rxdata_u.RESIVE_ARRAY), &Serial);
  ETout.begin(details(txdata_u.SEND_ARRAY), &Serial);
}
