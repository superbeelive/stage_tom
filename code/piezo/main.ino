#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
//#include "piezo.h"
//#include "udp.h"
int piezo = 0;

IPAddress ip_device(10, 24, 4, 129) ;
byte mac [6] = {0x54, 0x34, 0x41, 0x30, 0x30, 0x31};

unsigned int localPort = 8888;

EthernetUDP Udp;

void setup() {
 	Ethernet.begin(mac, ip_device);
	Serial.begin(9600);
	pinMode(piezo,INPUT);
	Udp.begin(localPort);
}

void loop() {
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
	Serial.println(Ethernet.localIP());
}

