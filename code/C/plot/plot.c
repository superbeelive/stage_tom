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

#define PORT	 8888
#define MAXLINE 2048
#define NBCHAR 5
void traitementData(double * valeurs, char * charData, int taille, int nbChar);
void writeData(char * title, double * valeurs, int taille);
void fftSig(double * valeurs, double * fft, int N);


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
	double fft[20];
	len = sizeof(cliaddr); //len is value/result
	for(;;){
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
		buffer[n] = '\0';
		traitementData(data,buffer,20,4);
		writeData("sig.dat",data,20);
		fftSig(data,fft,20);
		writeData("fft.dat",fft,20);
		sendto(sockfd, "ACK", strlen("ACK"),MSG_CONFIRM, (const struct sockaddr *)&cliaddr,sizeof(cliaddr));
	
	}
	return 0;
}

void traitementData(double * valeurs, char * charData, int taille, int nbChar){
	int i,y;
	char tmp[nbChar];
	printf("\n");
	for(i=0;i<taille;i++){
		for(y=0;y<nbChar;y++)
			tmp[y]=charData[(i*nbChar)+y];	
		valeurs[i]=atof(tmp);
		printf("%f ",valeurs[i]);
	}
	printf("\n ");
}


void writeData(char * title, double * valeurs, int taille){
	int i;
	FILE * f;
	f=fopen(title,"w");	
	for(i=0;i<taille;i++){
		fprintf(f,"%f\t%d\n",valeurs[i],i*20);
	}	
	fclose(f);
}

void fftSig(double * valeurs, double * fft, int N){
	int i;
	double * values = NULL ;
	values = (double *)malloc(sizeof(double)*N);
	fftw_plan p;
	p = fftw_plan_r2r_1d(N,values,fft,FFTW_HC2R,FFTW_MEASURE);
	
	for(i=0;i<20;i++){
			values[i]=valeurs[i];
	}
	
	fftw_execute(p);
	for(i=0;i<20;i++){
			printf("%f ",fft[i]);
	}
	printf("\n");
	fftw_destroy_plan(p);
	free(values);	

}
