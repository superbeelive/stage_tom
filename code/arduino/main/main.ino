//Libraries
// Communication serie on utilise :
// minicom -b 9600 -o -D /dev/ttyUC0


#include <SPI.h>
#include <PubSubClient.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Adafruit_Si7021.h>
#define PORT_MQTT 1883
#define PORT_UDP 8888


void udpSendChar(char * data);
void gatherVibration(char * fdata,char * topic, int nbEchantillon, int nbVirgule, double periodeEchantillonageMs);
void mqttSendHumTmp(int nbVirgule,char * topich , char * topict,Adafruit_Si7021 sensor);
void callback(char* topic, byte* payload, unsigned int length);
int beginEthSen();

int piezo = 0;
Adafruit_Si7021 sensor = Adafruit_Si7021();
String request ;
unsigned long refreshCounter  = 0;
byte mac [6] = {0x54, 0x34, 0x41, 0x30, 0x30, 0x31};

// Pour changer les addresse du serveur il faut changer les IP si dessous.
IPAddress ipMqtt(194, 199, 227, 239) ;
IPAddress ipUdp(194, 199, 227, 239) ;

EthernetUDP Udp;
EthernetClient ethclient; 
PubSubClient client(ipMqtt,PORT_MQTT,callback,ethclient); 

void setup() 
{
	Serial.begin(9600);
	if(!beginEthSen()){
		Serial.println("Erreur");
	}
	client.connect("arduino");
}
void loop() 
{
	char data[320];
	mqttSendHumTmp(2,"cadre3/humidite","cadre3/temperature",sensor);
  	delay(500);
	gatherVibration(data,"cadre3/vibration",50,2,10);
  	delay(500);
}


// Lance tout les fonction. Ehternet, UDP, MQTT et le capteur. 
int beginEthSen()
{
	int error = 0;
	if (!sensor.begin()) 
	{
		Serial.println("Did not find Si7021 sensor!");
		error=1;
	}

	Serial.println(F("Initialize System"));
	Ethernet.begin(mac);

	while (!Ethernet.begin(mac)) 
	{
		Serial.println(F("failed. Retrying in 1 secondsi."));
		error=1;
	}

	pinMode(2, OUTPUT);
	pinMode(0, INPUT);
	Serial.print(F("IP Address: "));
	Serial.println(Ethernet.localIP());
	Udp.begin(PORT_UDP);
	if(error=1)
		return -1;

	return 0;
}


// Cette fonction recolte et envoie l'humiditer et la température en MQTT. nbVirgule permet de spécifier le nombre de valeur apres la virgule.
void mqttSendHumTmp(int nbVirgule,char * topich, char * topict,Adafruit_Si7021 sensor)
{

	double hum,temp;
	char Ctemp[2+nbVirgule];
	char Chum[2+nbVirgule];
	hum = sensor.readHumidity();
	temp = sensor.readTemperature();
	dtostrf(temp,2,nbVirgule,Ctemp);
	dtostrf(hum,2,nbVirgule,Chum);
  
  Serial.println("HUMIDITER ET TEMPERATURE");
	Serial.println(Chum);
	Serial.println(Ctemp);
	if(!client.publish(topict,Ctemp))
	{
		Serial.println("error");
	}
	if(!client.publish(topich,Chum))
	{
		Serial.println("error");
	}

}

void gatherVibration(char * fdata, char * topic, int nbEchantillon, int nbVirgule, double periodeEchantillonageMs)
{
	// Afin d'avoire le nombre de caractere je fait le nombre de chiffre apres la virgule plus deux
	// qui represente mon premier digits et ma virgule.
	int nbChar = nbVirgule+2;
	char tmp[nbEchantillon][nbChar];
	char data2[nbEchantillon*nbChar];
	double centsValeurs[nbEchantillon];
	int i,y;
	for(i=0;i<nbEchantillon;i++){
		centsValeurs[i]=analogRead(piezo);
		centsValeurs[i]=(centsValeurs[i]*5)/1023;
		delay(periodeEchantillonageMs);
	}
	for(i=0;i<nbEchantillon;i++){
		dtostrf(centsValeurs[i],nbChar,nbVirgule,tmp[i]);
		for(y=0;y<nbChar;y++){
			data2[(nbChar*i)+y]=tmp[i][y];
			
		}	
	}
	Serial.println(data2);
	Udp.beginPacket(ipUdp,PORT_UDP);
	Udp.write(data2);
	Udp.endPacket();
}

void callback(char* topic, byte* payload, unsigned int length){

}
