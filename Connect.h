#define USE_LOCAL_SERVER

#ifdef USE_LOCAL_SERVER
        // #define SERVER                  IPAddress(192, 168, 1, 14) // Свой IP пишите
     #define SERVER                  "greenhouse.net.ua" // Имя своего хоста 
  //  #define SERVER                  IPAddress(31, 43, 61, 36) // Свой IP пишите

#endif

/*
   Wifi Credentials
*/

  // #define WIFI_SSID               "aonline"  //Имя точки доступа WIFI VVK   AndroidAP
#define WIFI_SSID               "UniNet"  //Имя точки доступа WIFI VVK   AndroidAP

  // #define WIFI_PASS               "1qaz2wsx3edc" //пароль точки доступа WIFI vtb24admin 1234567890
#define WIFI_PASS               "owen2014" //пароль точки доступа WIFI vtb24admin 1234567890
/*
     Blynk Auth Code
*/
// #define AUTH                      "5snN9aCY1vfL2w9Pf7Axf97CPceSGxNd"
  #define AUTH                      "fdJqyGGBEVnEm2Ge9TgtpPRXCaikPnhJ"  //test


//MQTT Server
const char *mqtt_server = "m16.cloudmqtt.com"; // Имя сервера MQTT
const int mqtt_port = 17031; // Порт для подключения к серверу MQTT
const char *mqtt_user = "lfrykgia"; // Логин от сервер
const char *mqtt_pass = "NUiR-ofMbYzC"; // Пароль от сервера


///////////////////////////////////////////////////////
//          Функции для подключения к Blynk          //

void ConnectBlynk()
{
  //*******************************************************
  // Запускаем WiFi
    if (WiFi.status() != WL_CONNECTED)// Если нет WiFi, то коннектимся
    {
      BLYNK_LOG(WIFI_SSID);
      // terminal.println();
      // terminal.println();
      // terminal.print("Connecting to ");
      // terminal.println(WIFI_SSID);
      // terminal.flush();
      WiFi.begin(WIFI_SSID, WIFI_PASS);

      int8_t count=0;
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        //Serial.print(".");
      //  terminal.print(WiFi.status());
        count++;
        if (count >= 5){break;
        //Serial.println("WiFi not connected");
        }
      }
    }
  /*  Дисконект - для справки 
    WiFi.disconnect(); // отключаемся от сети
    Serial.println("Disconnect WiFi.");
  */
  
  //*******************************************************
  // Запускаем Blynk

  if (WiFi.status() == WL_CONNECTED)// Если нет WiFi, то не коннектимся
    {
          // CONNECT TO BLYNK
          #ifdef USE_LOCAL_SERVER // Если используются локальный сервер
            Blynk.config(AUTH, SERVER, 8080);
            Blynk.connect();
          #else // Иначе конектимся постаринке к блинку
            Blynk.config(AUTH);
            Blynk.connect();
          #endif
    }
    
}//ConnectBlynk()


// Реконектимся если обрыв связи

void reconnectBlynk() {
  if (!Blynk.connected())
  {
    // terminal.println("Disconnected now");
    // terminal.flush();
    ConnectBlynk();
   if (Blynk.connected()) 
   {
     // terminal.println("Reconnected"); 
     // terminal.flush();     
   } 
   else 
   {
     // terminal.println("Not reconnected");      
     // terminal.flush();
   }
  }
}//reconnectBlynk()
