//Libraries
// Communication serie on utilise :
// minicom -b 9600 -o -D /dev/ttyUC0
//https://www.blognote.info/arduino-nano-ethernet-mqtt/
#include <PubSubClient.h>
#include <Ethernet.h>
#include "Adafruit_Si7021.h"
#define PORT_MQTT 1883

Adafruit_Si7021 sensor = Adafruit_Si7021();

String request ;
unsigned long refreshCounter  = 0;
IPAddress ipMqtt(172, 42, 20, 126) ;
IPAddress ip(192, 168, 1, 179) ;
byte mac [6] = {0x54, 0x34, 0x41, 0x30, 0x30, 0x31};


void callback(char* topic, byte* payload, unsigned int length) {
}


EthernetClient ethclient; 
PubSubClient client(ipMqtt,PORT_MQTT,callback,ethclient); 


void setup() {
  
 if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }
 Serial.begin(9600);
 Serial.println(F("Initialize System"));
 Ethernet.begin(mac, ip);
 while (!Ethernet.begin(mac)) {
   Serial.println(F("failed. Retrying in 1 seconds."));
   delay(1000);
 }
 
 pinMode(2, OUTPUT);
 Serial.println(F("W5100 initialized"));
 Serial.print(F("IP Address: "));
 Serial.println(Ethernet.localIP());
 client.connect("arduino");
}
void loop() {
  double hum,temp;
  char Ctemp[4];
  char Chum[4];
  hum = sensor.readHumidity();
  temp = sensor.readTemperature();
  dtostrf(temp,2,2,Ctemp);
  Serial.println(Ctemp);
  if(!client.publish("topic","test")){
     Serial.println("error");
  }
  client.publish("topic","coucou"); 

 delay(1000);
}
