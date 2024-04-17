#include <WiFi.h>
#include <HTTPClient.h> // nos permite hacer peticiones http
#include <ArduinoJson.h>
#include <DHT.h>

#define DHTPIN 27
#define DHTTYPE  DHT22

DHT dht(DHTPIN, DHTTYPE, 22); 


// credenciales de la red a la cual nos conectaremos
const char* ssid = "red";
const char* password = "password";
//const char* ssid = "Tenda_3DE948";
//const char* password = "18264838";
//IPAddress ip(192,168,10,9);     
//IPAddress gateway(192,168,10,1);   
//IPAddress subnet(255,255,255,0);   
//Temperatura


void setup() {
    Serial.begin(115200);
     dht.begin(); 

    // conexión a la red
  //    WiFi.mode(WIFI_STA);
    //  WiFi.config(ip, gateway, subnet);
      WiFi.begin(ssid, password);
//    IPAddress ip(192,168,10,145);     
//    IPAddress gateway(192,168,10,1);   
//    IPAddress subnet(255,255,255,0);   
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print("Conectado a la red con la IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

}

void loop() {
if(WiFi.status() == WL_CONNECTED ){ 
 //se agregan valores al documento
DynamicJsonDocument doc(2048);

  doc["temp"] = dht.readTemperature();
  doc["hum"] = dht.readHumidity();
  doc["gas"] =  analogRead(35);
  doc["ruido"] =  analogRead(34)/100;
  doc["nombre"] =  "ITSRLL";
  //doc["fecha"] = rtc.getDate();

// documento serializado
String json;
serializeJson(doc, json);

WiFiClient client;  // or WiFiClientSecure for HTTPS
HTTPClient http;
// Send request
http.begin("https://colmena.onrender.com/insertar");
//cabeceras JSON
http.addHeader("Content-Type", "application/json");
int res = http.POST(json);

Serial.println(json);
// respuesta
Serial.println(http.getString());
Serial.println(res);
// desconecta
http.end();
delay(60000);
}
}