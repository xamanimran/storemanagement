/*working*/
#include<ESP8266WiFi.h>
#include<PubSubClient.h>
#include "DHT.h"
#define DHTPIN D3
#define wifi_ssid ""
#define wifi_password ""
#define mqtt_server "test.mosquitto.org" //its a cloud server just for you to temporarily run the code and understand, as implementing it locally takes some efforts.
#define tem "temperature"
#define DHTTYPE DHT22
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);    
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    dht.begin();
}
void setup_wifi() {
    delay(10);
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting MQTT Connection...");
    if (client.connect("nodeMcuDHT22")){
      Serial.println("connected");}
      else
      {Serial.print("failed,rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
      }
    }
  }

long lastMsg=0;
float temp=0.0;
float hum=0.0;
void loop()
{ if (!client.connected())
  {reconnect();
  }
  client.loop();
  long now=millis();
  if(now-millis()>30000)
  {lastMsg=now;

        float Temp = dht.readTemperature();
       
        Serial.print("Temp:"); //print
        Serial.println(String(Temp).c_str()); //print the value
        client.publish(tem, String(Temp).c_str(),true); //publish to mqtt
        delay(5000);
        }
    }
