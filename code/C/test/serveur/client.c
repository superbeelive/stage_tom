// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
	
#define PORT	 8888
#define MAXLINE 2048
	
// Driver code
int main() {
	srand(time(NULL));
	int sockfd,n,y,i,len;
	char buffer[MAXLINE];
        char charValues[80], tmp[20][4];
	struct sockaddr_in servaddr;
	double values[20];
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
		
	for(i=0;i<20;i++){
		double dec,cent;
		dec = rand()%10;
		cent = rand()%10;
		values[i]= rand()%10+(dec/10)+(cent/100);
		printf("%f",values[i]);	
		sprintf(tmp[i],"%1.2f",values[i]);
	}

	sendto(sockfd, (const char *)tmp[0], strlen(tmp[0]),MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
	printf("Values send.\n");
			
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,&len);
	buffer[n] = '\0';
	printf("Serveur : %s\n", buffer);
	
	close(sockfd);
	return 0;
}

