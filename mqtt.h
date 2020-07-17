#include <PubSubClient.h>
unsigned long oldmillis;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;  
                                                    // вызывается когда приходят данные от брокера
void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
 // Serial.print(topic);                              // отправляем в монитор порта название топика                     
 // Serial.print("] ");
  for (int i = 0; i < length; i++) {                // отправляем данные из топика
    //Serial.print((char)payload[i]);
  }
  //Serial.println();  
}
                                               // подключение к mqtt брокеру            
void reconnect() {                                                      
unsigned long ms=millis();
   if(ms - oldmillis > 1000) {
    oldmillis = ms;                                                       // подключаемся, в client.connect передаем ID, логин и пасс
    if (client.connect("arduinoClient", mqtt_user, mqtt_pass)) {
     // Serial.println("connected MQTT");                    // если подключились 
     // client.set_callback(callback);
     // client.subscribe("Температура внут");                   // подписываемся на топик, в который же пишем данные
    //  client.subscribe("Температура внеш");
      
    } else {                                          // иначе ругаемся в монитор порта  
      //Serial.print("failed, rc=");
     // Serial.print(client.state());
     // Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
    //  delay(1000);
    }
   }
}

void setupMqtt() {  
  
  client.setServer(mqtt_server, mqtt_port);           // указываем адрес брокера и порт
 // client.setCallback(callback); 
  // указываем функцию которая вызывается когда приходят данные от брокера
}
void loopMQtt() {
  
  char msg[6];                                            // забераем температуру и конвертируем её в char
  float tmpin = Temp_s;
  dtostrf(tmpin, 4, 2, msg);

  char msg1[6];                                            // забераем температуру и конвертируем её в char
  float tmp_out = Temp_out;
  dtostrf(tmp_out, 4, 2, msg1);

  char msg2[6];                                            // забераем температуру и конвертируем её в char
  float lux_in = lux;
  dtostrf(lux_in, 4, 2, msg2);
 
  


   
  if (!client.connected()) {                             // проверяем подключение к брокеру
    reconnect();                                            // еще бы проверить подкючение к wifi...
  }
  client.loop();

  long now = millis();                                   // каждые 10 секунд
  if (now - lastMsg > 5000) {
    lastMsg = now; 
    client.publish("Температура внут", msg);                     // пишем в топик 
    client.publish("Температура внеш", msg1);
    client.publish("Свет", msg2);
  }
}
