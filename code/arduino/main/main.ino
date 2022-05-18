// Communication serie on utilise :
// minicom -b 9600 -o -D /dev/ttyUC0
//https://www.blognote.info/arduino-nano-ethernet-mqtt/
#include <SPI.h>
#include <EthernetUdp.h>
#include <PubSubClient.h>
#include <Ethernet.h>
#include <Adafruit_Si7021.h>
#define PORT_MQTT 1883

int piezo = 0;

IPAddress ip_device(10, 24, 4, 129) ;
byte mac [6] = {0x54, 0x34, 0x41, 0x30, 0x30, 0x31};

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
 if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }
 Serial.println(F("Initialize System"));
 Ethernet.begin(mac, ip_device);
 while (!Ethernet.begin(mac)) {
   Serial.println(F("failed. Retrying in 1 seconds."));
   delay(1000);
 }
 
 pinMode(piezo,INPUT);
 Udp.begin(localPort);
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
  dtostrf(hum,2,2,Chum);
  Serial.println(Ctemp);
  if(!client.publish("topic",Ctemp)){
     Serial.println("error");
  }
  if(!client.publish("topic",Chum)){
     Serial.println("error");
  }
	// ENVOIE MQTT PIEZO
	char tmp[20][4];
	char data2[80];
	double centsValeurs[20];
	int i,y;
	for(i=0;i<20;i++){
		centsValeurs[i]=analogRead(piezo);
		centsValeurs[i]=(centsValeurs[i]*5)/1023;
		delay(20);
	}
	delay(2000);
	for(i=0;i<20;i++){
		dtostrf(centsValeurs[i],4,2,tmp[i]);
		for(y=0;y<4;y++){
			data2[(4*i)+y]=tmp[i][y];
			Serial.println(data2[(i*4)+y]);	
		}	
	}

	Udp.beginPacket("10.24.4.127",8888);
	Udp.write(data2);
	Udp.endPacket();

 delay(1000);
}
