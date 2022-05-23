//Libraries
// Communication serie on utilise :
// minicom -b 9600 -o -D /dev/ttyUC0
//https://www.blognote.info/arduino-nano-ethernet-mqtt/
#include <Ethernet.h>
#include <PubSubClient.h>
#define PORT_MQTT 1883

String request ;
unsigned long refreshCounter  = 0;
IPAddress ipMqtt(194, 199, 227, 239) ;
IPAddress ip(192, 168, 1, 179) ;
byte mac [6] = {0x54, 0x34, 0x41, 0x30, 0x30, 0x31};

EthernetClient ethclient; 
PubSubClient client;

void cb(){
}
void setup() {
 Serial.begin(9600);
 Serial.println(F("Initialize System"));
 Ethernet.begin(mac, ip);
 while (!Ethernet.begin(mac)) {
   Serial.println(F("failed. Retrying in 1 seconds."));
   delay(1000);
 }
 
 pinMode(2, OUTPUT);
 client = PubSubClient(ipMqtt,PORT_MQTT,cb,ethclient); 
 Serial.println(F("W5100 initialized"));
 Serial.print(F("IP Address: "));
 Serial.println(Ethernet.localIP());
 client.connect("arduino");
}
void loop() {
 client.publish("topic","coucou",6,false); 
 delay(1000);
}
