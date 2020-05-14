#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

/* Note. 
/*inet_aton: converts the C character string pointed to by strptr into its 32-bit binary network byte ordered value, 
/*	which is stored through the pointer addrptr

/*inet_addr: does the same conversion, returning the 32-bit binary network byte ordered      
/*	value as the return value. It is deprecated and any new code should use inet_aton instead

/*inet_ntoa: converts a 32-bit binary network byte ordered IPv4 address into its corresponding dotted-decimal string.

/*servaddr.sin_addr.s_addr = inet_addr(argv[1]);
/*servaddr.sin_port =  htons((int) strtol(argv[2], (char **)NULL, 10)); */



#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 10010 /*port*/
#define PORTNUMBER 10010


int

main(int argc, char **argv) 
{
 int sockfd, i;
 struct sockaddr_in servaddr;
 char sendline[MAXLINE], recvline[MAXLINE];
 time_t mytime;
 mytime = time(NULL);
 
FILE *fpLog;
fpLog = fopen("a5Client1Log.txt", "a+");

fprintf(fpLog, "\nFile opened: ");
fprintf(fpLog, ctime(&mytime));
fputs("\n", fpLog);
fclose(fpLog);

 alarm(300);  // to terminate after 300 seconds
	
 //basic check of the arguments
 //additional checks can be inserted
 if (argc !=3) {
  perror("Usage: TCPClient <Server IP> <Server Port>"); 
  exit(1);
 }
	
 //Create a socket for the client
 //If sockfd<0 there was an error in the creation of the socket
 if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("Problem in creating the socket");
  exit(2);
 }
	
 //Creation of the socket
 memset(&servaddr, 0, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 //servaddr.sin_port =  htons(argv[2]); //this is depricated
 servaddr.sin_port =  htons((int) strtol(argv[2], (char **)NULL, 10));
//servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
	
 //Connection of the client to the socket 
 if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
  perror("Problem in connecting to the server");
  exit(3);
 }
 
	printf("%s",ctime(&mytime));
	printf("Process ID: %d\n", getpid());
	
	sprintf(sendline, "SELECT * from EMPLOYEE");
	
 //while (fgets(sendline, MAXLINE, stdin) != NULL)	 
while(1)
 {
	send(sockfd, sendline, strlen("SELECT * from EMPLOYEE"), 0);
	
	memset(recvline, 0, sizeof(recvline)+1);	
  if (recv(sockfd, recvline, MAXLINE,0) == 0){
   //error: server terminated prematurely
   perror("The server terminated prematurely"); 
   exit(4);
  }
  printf("\n%s", "String received from the server: \n\n");
  char *rPtr = recvline;
  
  fpLog = fopen("a5Client1Log.txt", "a");
  fprintf(fpLog, "%s\n", recvline);
  fprintf(fpLog, "End of entry from Process ID: %d\n", getpid());
  fclose(fpLog);
	
	printf("%s\n", recvline);
	printf("%s",ctime(&mytime));
	printf("Process ID: %d\n", getpid());
  
  sleep(3);
 }
 
 
 exit(0);
}



