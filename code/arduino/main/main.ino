// Communication serie on utilise :
// minicom -b 9600 -o -D /dev/ttyUC0
//https://www.blognote.info/arduino-nano-ethernet-mqtt/
#include <SPI.h>
#include <EthernetUdp.h>
#include <PubSubClient.h>
#include <Ethernet.h>
#include <Adafruit_Si7021.h>
#define PORT_MQTT 1883
#define NBCHAR 5
#define NBECH 20
int piezo = 0;

IPAddress ip_device(172, 42, 20, 127) ;
byte mac [6] = {0x54, 0x34, 0x41, 0x42, 0x30, 0x35};

unsigned int localPort = 8888;

EthernetUDP Udp;

Adafruit_Si7021 sensor = Adafruit_Si7021();

String request ;
unsigned long refreshCounter  = 0;
IPAddress ipMqtt(194, 199, 227, 239) ;


void callback(char* topic, byte* payload, unsigned int length) {
	printf("Callbck function\n");
}


EthernetClient ethclient; 
PubSubClient client(ipMqtt,PORT_MQTT,callback,ethclient); 


void setup() {
   Serial.begin(9600);
   sensor.begin();
   Serial.println(F("Initialize System"));
   Ethernet.begin(mac, ip_device);
   Udp.begin(localPort);
   pinMode(piezo,INPUT);
   pinMode(2, OUTPUT);
   Serial.println(F("W5100 initialized"));
   Serial.print(F("IP Address: "));
   Serial.println(Ethernet.localIP());
   client.connect("arduino");
}

void loop() {
  double hum,temp;
  char Ctemp[3];
  char Chum[3];
  hum = sensor.readHumidity();
  temp = sensor.readTemperature();
  dtostrf(temp,3,3,Ctemp);
  dtostrf(hum,3,3,Chum);
  Serial.println(Ctemp);
  /*if(!client.publish("cadre2Temp",Ctemp)){
     Serial.println("error");
  }
  if(!client.publish("cadre2Hum",Chum)){
     Serial.println("error");
  }*/
	// ENVOIE MQTT PIEZO
	char tmp[NBECH][NBCHAR];
	char data2[NBECH*NBCHAR];
	double centsValeurs[NBECH];
	int i,y;
	for(i=0;i<NBECH;i++){
		centsValeurs[i]=analogRead(piezo);
		centsValeurs[i]=(centsValeurs[i]*5)/1023;
		delay(20);
	}
	delay(2000);
	for(i=0;i<NBECH;i++){
		dtostrf(centsValeurs[i],NBCHAR,NBCHAR,tmp[i]);
		for(y=0;y<NBCHAR;y++){
			data2[(NBCHAR*i)+y]=tmp[i][y];
			Serial.println(data2[(i*NBCHAR)+y]);	
		}	
	}

	Udp.beginPacket(ipMqtt,8888);
	Udp.write(data2);
	Udp.endPacket();

 delay(1000);
}
