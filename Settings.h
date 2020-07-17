

// Переменные для Меню
  unsigned long Watch_dog = 0;
  unsigned long ms;
  int Item=0;     // Тут храним индекс получаемый от Виджета Menu
  int Index=0;    // Дополнительный индекс нужен для навигации по вкладкам
  int MenuIndex=0;  // Индекс для перехода по меню при помощи switch case
// Переменные что бы действие выполнялось один раз
  int MenuIndexLast=0; // Тут Храним последнее значение Индекса
  boolean one = false; // Переменная что бы выполнить условие один раз
int16_t TempTuning[4];
uint32_t TimerTuning[4]; //= {36000, 43200, 54000, 82800};
int16_t data_send[20];
int16_t new_data_send[20];
bool relay_poliv;
int8_t new_rellay_poliv = 0;
int8_t Delta; //=2;
// Переменные для настройки параметров
long TimerInput;  // Тут хранятся данные от TimerInput (Ввод времени)
int StepControl; // Тут хранятся данные от StepControl (Шаговые кнопки)
boolean Button; // Тут храниться данные от Нажата ли кнопка
//timezone Временная зона
//full list of supported timezones could be found here
//Полный список поддерживаемых часовых поясов можно найти здесь
//https://www.mkyong.com/java/java-display-list-of-timezone-with-gmt/
char TimeZone[] = "Europe/Kiev";
int Tuning; // служит для настройки всех уставок через StepControl (Шаговые кнопки)
long TunTime; // служит для настройки всех уставок через TimerInput (Ввод времени)
int timerTable_ID; // Номер таймера Таблица
int timerTimeString_ID; // Номер таймера TimeString
int ID_timer_RTS; // Номер Таймера для установки времени
uint32_t TimerRTC; // Текущее время в секундах от DS3231
int8_t T_hourRTC; // Текущее время сколько часов
int8_t T_minRTC; // Текущее время сколько минут
#define VPIN_TABLE V10 // Задаем виртуальный пин виджета Value Display
#define VPIN_MENU V11 // Задаем виртуальный пин виджета Value Display
#define VPIN_TIME_INPUT V12 // Задаем виртуальный пин виджета Time Input
#define VPIN_STEP_CONTROL V13 // Задаем виртуальный пин виджета Step Control
#define VPIN_BUTTON V14 // Задаем виртуальный пин виджета Button
String currentTimeRTC;
String currentTimeBlynk;
String currentTime;
uint8_t hour_t;
uint8_t minute_t;
uint8_t sec_t;
String WindowsValue;
uint8_t flag_AutoManual;
uint8_t flag_TableStop = true;
bool isFirstConnect  = true;
bool flag_send = false;
// Настройки Аварийного нагревателя
int8_t AlarmTempStart = 20; //Температура Включения
int8_t AlarmTempStop = 22;  //Температура Выключения
int8_t VentTempStart = 2500; //Температура открытия окон
int8_t temp_on;
int8_t VentTempStop = 2000; //Температура закрытия окон
int8_t temp_off;
int8_t VentTime = 5000;    //Время открытия
int8_t time_on;
float TempZ_1;
float TempZ_2;
float TempZ_3;
float TempZ_4;
float TempZ[4];
char V[4] = {V0,V1,V2,V3};

bool flagZ_1;
bool flagZ_2;
bool flagZ_3;
bool flagZ_4;
bool relayZ_1;
bool relayZ_2;
bool relayZ_3;
bool relayZ_4;
bool manual_z;
bool heat;
bool send_heat;


// Данные от датчиков
float Temp;
float Temp_in;
float Temp_out;
float Temp1;
//int8_t Temp1;  // Температура от датчика 1
float Humid1;
//int8_t Humid1; // Влажность от датчика 1
float NH3;
int16_t CO_2;
int lux;
int lux_in;
int lux_on;
bool lux_relley;
//#define TEMP_SUM 2 // Количество датчиков
//int8_t TempDS18B20[TEMP_SUM];
//float Temp_in;
//float Temp_out;
float TempDS;
// 0 Датчик в помещении
// 1 Датчик в полу
float Temp_s;
float Tmin = 50.00;
float Tmax = -50.00;
float Tmax_i = -50.00;
float Tmin_i =  50.00;
float Tout;
float Tin;
float  temp_ust_esp;
int  button_esp;
uint32_t DELAY_Backlight = 10000UL; // время отключения подсветки экрана при бездействии (Factory Settings)
// Флаги выходных устройств
boolean flag_RELAY1 = false;
boolean flag_A_logicRegulatorT = false;
boolean flag_RELAY2_Alarm = false;
boolean flag_RELAY3_Vent = false;
boolean flag_RELAY4_Vent = false;
boolean flag_wind = false;
boolean flag = 0;
boolean i = 0;
bool button;
bool relay;  // Реле подключаем 
long rssi;
unsigned long new_time = 0;
uint16_t modbus_read[55];
uint16_t modbus_write[55];
uint16_t au16data[35]; // data array for modbus network sharing

boolean RELAY1PIN;   // PIN реле 1 Теплый пол
boolean RELAY2PIN;  // PIN реле 2 Аварийный нанреватель
boolean RELAY3PIN;  // PIN реле 3 Открытия Окон проветривания
boolean RELAY4PIN;  // Пин реле 4 Закрытия Окон Проветривания
