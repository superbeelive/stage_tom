#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "piezo.h"
//#include "udp.h"
int piezo = 0;

IPAddress ip_device(10, 24, 4, 128) ;
IPAddress ip_dest(10, 24, 4, 127) ;
byte mac [6] = {0x54, 0x34, 0x41, 0x30, 0x30, 0x31};

EthernetClient ethclient; 
unsigned int localPort = 8888;

char bufferRcv[UDP_TX_PACKET_MAX_SIZE];
EthernetUDP Udp;

void setup() {
	Ethernet.init(10);
 	Ethernet.begin(mac, ip_device);
	Serial.begin(9600);
	pinMode(piezo,INPUT);
	Udp.begin(localPort);
}

void loop() {
	char data2[400];
	double centsValeurs[100];
	getMultipelValues(centsValeurs,100,20,piezo);
	printTab(centsValeurs,100);
	delay(2000);
	dataToStr(centsValeurs,data2);	
	Udp.beginPacket(ip_dest,8888);
	Udp.write(data2);
	Udp.endPacket();
	Serial.println(Ethernet.localIP());
}

