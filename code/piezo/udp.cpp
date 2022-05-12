#include <Arduino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "udp.h"
//https://www.geeksforgeeks.org/file-transfer-protocol-ftp-in-application-layer/?ref=lbp

void sendPacket(char * data, IPAddress ip_dest,EthernetUDP Udp){
	if(Udp.beginPacket(ip_dest,8888)==1)
	{
		Udp.write(data);
		Udp.endPacket();
	}
	else
	{
		Serial.println("No connexion");
	} 
} 
