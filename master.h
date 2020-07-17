#include <SimpleModbusMaster_DUE.h>
//////////////////// Port information ///////////////////
     // interval at which to blink (milliseconds)
////////////////////modbus////////////
#define baud        115200
#define timeout     50
#define polling     200 // скорость опроса по модбус
#define retry_count 10
#define TxEnablePin 0   // Tx/Rx пин RS485
#define Slave_ID    10

//Общая сумма доступной памяти на ведущем устройстве, чтобы хранить данные
#define TOTAL_NO_OF_REGISTERS 255

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 250;      
//////////////////modbus////////////////
union fread_t{
 float f;
 uint16_t u[2];
}t;


enum
{
  PACKET1,
  PACKET2,
  PACKET3,
  PACKET4,
  PACKET5,
  PACKET6,
  PACKET7,
  TOTAL_NO_OF_PACKETS // leave this last entry
};

// Масив пакетов модбус
Packet packets[TOTAL_NO_OF_PACKETS];

// Массив хранения содержимого принятых и передающихся регистров
unsigned int regs[TOTAL_NO_OF_REGISTERS];
void setup_mega()
{
  // Настраиваем пакеты
  // Шестой параметр - это индекс ячейки в массиве, размещенном в памяти ведущего устройства, в которую будет 
  // помещен результат или из которой будут браться данные для передачи в подчиненное устройство. В нашем коде - это массив reg
  // Пакет,SLAVE адрес,функция модбус,адрес регистра,количесво запрашиваемых регистров,локальный адрес регистра.
   modbus_construct(&packets[PACKET1], Slave_ID, READ_HOLDING_REGISTERS,    0, 23, 0);
   modbus_construct(&packets[PACKET2], Slave_ID, READ_HOLDING_REGISTERS,    23, 23, 23);
   modbus_construct(&packets[PACKET3], Slave_ID, READ_HOLDING_REGISTERS,    47, 23, 47);
   modbus_construct(&packets[PACKET4], Slave_ID, READ_HOLDING_REGISTERS,    71, 23, 71);
   modbus_construct(&packets[PACKET5], Slave_ID, READ_HOLDING_REGISTERS,    95, 23, 95);
 
    // Пакет,SLAVE адрес,функция модбус,адрес регистра,данные,локальный адрес регистра.
   modbus_construct(&packets[PACKET6], Slave_ID, PRESET_MULTIPLE_REGISTERS, 95, 23, 95); 
 
  // инициализируем протокол модбус
  modbus_configure(&Serial, baud, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS, regs);
 
}

 void up_reg(){
  
      t.u[0]  = regs[0];
      t.u[1]  = regs[1];
      TempZ[0] = t.f;
      t.u[0]   = regs[2];
      t.u[1]   = regs[3];
      TempZ[1] = t.f;
      t.u[0]   = regs[4];
      t.u[1]   = regs[5];
      TempZ[2] = t.f;
      t.u[0]    = regs[6];
      t.u[1]    = regs[7];
      TempZ[3] = t.f;
      t.u[0]    = regs[8];
      t.u[1]    = regs[9];
      Temp_out = t.f;
      t.u[0]    = regs[10];
      t.u[1]    = regs[11];
      Temp_in = t.f;
      t.u[0]    = regs[12];
      t.u[1]    = regs[13];
      Humid1 = t.f;
      t.u[0]    = regs[14];
      t.u[1]    = regs[15];
      NH3 = t.f;
      t.u[0]    = regs[16];
      t.u[1]    = regs[17];
      Tmax = t.f;
      t.u[0]    = regs[18];
      t.u[1]    = regs[19];
      Tmin = t.f;
      t.u[0]    = regs[20];
      t.u[1]    = regs[21];
      Tmax_i = t.f;
      t.u[0]    = regs[22];
      t.u[1]    = regs[23];
      Tmin_i = t.f;
      flagZ_1 = regs[38];
      flagZ_2 = regs[39];
      flagZ_3 = regs[40];
      flagZ_4 = regs[41];
      // CO_2      = regs[8];
      // nh.u[1]   = regs[9];
      // nh.u[0]   = regs[10];
      // tmax.u[1] = regs[11];
      // tmax.u[0] = regs[12];
      // tmin.u[1] = regs[13];
      // tmin.u[0] = regs[14];
      // flag_wind = regs[15];
      // lux       = regs[16];
      // tmax_i.u[1] = regs[17];
      // tmax_i.u[0] = regs[18];
      // tmin_i.u[1] = regs[19];
      // tmin_i.u[0] = regs[20];
      // t_1.u[1]  = regs[21];
      // t_1.u[0]  = regs[22];
      // Temp_in   = t_0.f;    
      // Temp_out  = t_1.f;
      // Temp      = t1.f;
      // Temp1     = t2.f;
      // Humid1    = h.f;
      // NH3       = nh.f;
      // Tmax      = tmax.f;
      // Tmin      = tmin.f;
      // Tmax_i    = tmax_i.f;
      // Tmin_i    = tmin_i.f;
      //  terminal.println(regs[98]);
//      regs[93]= VentTempStart;
//      regs[94]= VentTempStop;
//      regs[95]= VentTime;
//      regs[96] = button;
//      regs[97]= relay;
if (!flag_send)
{
   heat = regs[98] ;
   Blynk.virtualWrite(V55, regs[98]);/* code */
}

else if  (heat!=regs[98])
  {
    regs[98]=heat;
    terminal.println(regs[98]);
  }
 
else
{  flag_send = false; 
  // Blynk.virtualWrite(V55, regs[98]);
  
}


      
      // 
 }
