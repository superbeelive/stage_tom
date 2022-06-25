#include <stdio.h>
#include <complex.h>
#include <fftw3.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//#include <arduinoUDP.h>

#define PORT	 8888
#define MAXLINE 2048

void traitementData(double * valeurs, char * charData, int taille, int nbChar);


int main (){

	printf("Début du programme. \n");
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	double data[20];
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("Erreur lors de la creation de la socket");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	int len, n;

	len = sizeof(cliaddr); //len is value/result
	for(;;){
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
		buffer[n] = '\0';
		printf("Client : %s\n", buffer);
		traitementData(data,buffer,20,4);
	}
	return 0;
}

void traitementData(double * valeurs, char * charData, int taille, int nbChar){
	int i,y;
	char tmp[4];
	printf("\n");
	for(i=0;i<taille;i++){
		for(y=0;y<nbChar;y++)
			tmp[y]=charData[(i*nbChar)+y];
		valeurs[i]=atof(tmp);
		printf("%f ",valeurs[i]);
	}
	printf("\n ");
}
