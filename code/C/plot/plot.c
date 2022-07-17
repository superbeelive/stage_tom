#include <stdio.h>
#include <complex.h>
#include <fftw3.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8888
#define MAXLINE 2048
#define NBCHAR 5
void traitementData(double * valeurs, char * charData, int taille, int nbChar);
void writeData(char * title, double * valeurs, int taille);
void fftSig(double * valeurs, double * fft, int N);

struct stat st = {0};
int main (){
	printf("Début du programme. \n");
	int sockfd, len, n, echantillon, nbchar;
	nbchar = 4;
	echantillon = 80;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	double data[echantillon];
	fftw_complex *fft;
	fft = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*echantillon);
	if(stat("graph",&st)== -1){
		mkdir("graph", 0700);
	}
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

	len = sizeof(cliaddr); //len is value/result
	for(;;){
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
		buffer[n] = '\0';
		traitementData(data,buffer,echantillon,4);
		writeData("graph/sig.dat",data,echantillon);
		fftSig(data,fft,echantillon);
		writeData("graph/fft.dat",fft,echantillon);
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

void fftSig(double * valeurs, fftw_complex * fft, int N){
	int i;
	double * values = NULL ;
	values = (double *)malloc(sizeof(double)*N);
	fftw_plan p;
	p = fftw_plan_dft_r2c(N,values,fft,FFTW_HC2R,FFTW_MEASURE);
	
	for(i=0;i<20;i++){
			values[i]=valeurs[i];
	}
	
	fftw_execute(p);
	for(i=0;i<20;i++){
			printf("reel : %f complexe : i %f ",fft[i][0], fft[i][1]);
	}
	printf("\n");
	fftw_clean_plan(p);
	fftw_destroy_plan(p);
	free(values);	

}
