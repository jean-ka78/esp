#include <ESP8266HTTPClient.h>
// #include <Arduino_JSON.h> 
#include <ArduinoJson.h> 
//#define serverName  "http://bfcloud.space/api/v1/modbus-device/"
const char* serverName = "http://bfcloud.space/api/v1/modbus-device/";
// 
String httpPostRequest(const char* serverName, String httpRequestData) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);

  // String httpRequestData;
http.addHeader("Content-Type",  "application/json");
  // Send HTTP POST request
  int httpResponseCode = http.POST(httpRequestData);
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
//    Serial.print("HTTP Response code_Post: ");
//    Serial.println(httpResponseCode);
    payload = http.getString();
    // Serial.println(payload);
  }
  else {
//    Serial.print("Error code: ");
//    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void send_json(){
  
const size_t capacity_post = JSON_ARRAY_SIZE(7) + JSON_OBJECT_SIZE(1) + 7*JSON_OBJECT_SIZE(2);
DynamicJsonDocument doc_post(capacity_post);

JsonArray tags = doc_post.createNestedArray("tags");
JsonObject tags_0 = tags.createNestedObject();
tags_0["id"] = 1;
tags_0["value"] = TempZ[0];

JsonObject tags_1 = tags.createNestedObject();
tags_1["id"] = 2;
tags_1["value"] = TempZ[1];

JsonObject tags_2 = tags.createNestedObject();
tags_2["id"] = 3;
tags_2["value"] = TempZ[2];

JsonObject tags_3 = tags.createNestedObject();
tags_3["id"] = 4;
tags_3["value"] = TempZ[3];

JsonObject tags_4 = tags.createNestedObject();
tags_4["id"] = 5;
tags_4["value"] = Temp_in;

JsonObject tags_5 = tags.createNestedObject();
tags_5["id"] = 6;
tags_5["value"] = Humid1;

JsonObject tags_6 = tags.createNestedObject();
tags_6["id"] = 7;
tags_6["value"] = NH3;
String output;
serializeJson(doc_post, output);
//  Serial.println(output);
httpPostRequest(serverName ,output);

 }
