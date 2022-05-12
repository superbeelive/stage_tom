#include <Arduino.h>
#include "piezo.h"

//https://www.geeksforgeeks.org/file-transfer-protocol-ftp-in-application-layer/?ref=lbp

void getMultipelValues(double * values, int nb, int Te, int pin){
	int i;
	for(i=0;i<nb;i++){
		values[i]=analogRead(pin);
		values[i]=(values[i]*5)/1023;
		delay(Te);
	}

}
void printTab(double * tab,int nb){
	int i;
	Serial.println("Débuts Plage de valeurs");
	for(i=0;i<nb;i++){
		Serial.print(tab[i]);
		Serial.print(", ");
	}
	Serial.println("");
	Serial.println("Fin Plage de valeurs");
}
void dataToStr(double * data, char * data2){
	char tmp[100][4];
	int i,y;
	for(i=0;i<100;i++){
		dtostrf(data[i],4,2,tmp[i]);
		for(y=0;y<4;y++){
			if(i==0){
				data2[(4*i)+y]=tmp[i][y];
			}
		}	
	}
}
