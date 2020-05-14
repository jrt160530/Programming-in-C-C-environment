#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sqlite3.h> 


/*
    CONCURRENT SERVER: THREAD EXAMPLE
    Must be linked with the "pthread" library also, e.g.:
       cc -o example example.c -lnsl -lsocket -lpthread 

    This program creates a connection socket, binds a name to it, then
    listens for connections to the sockect.  When a connection is made,
    it accepts messages from the socket until eof, and then waits for
    another connection...

    This is an example of a CONCURRENT server -- by creating threads several
    clients can be served at the same time...

    This program has to be killed to terminate, or alternately it will abort in
    120 seconds on an alarm...
*/

#define PORTNUMBER 10010
   char sqlG[2048];

struct serverParm {
        int connectionDesc;
		};
	
int sqlEx(char *sqlStr);


/*call back function for sql execution*/	
static int callback(void *data, int argc, char **argv, char **azColName){
  
   int i;
   char str[512];
   
     //fprintf(stderr, "%s: ", (const char*)data);
   
   for(i=0; i<argc; i++)
   {
    sprintf(str, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	strncat(sqlG, str, 512);
	
	}
 
   return 0;
}/******************************************/
	
	
/****************************************************************/
/* server thread uses the socket to listen to client            */
/* can have multiple server threads listening to clients        */
/* This thread will execute sql statements received from client */	
/****************************************************************/

void *serverThread(void *parmPtr) {

#define PARMPTR ((struct serverParm *) parmPtr)
    int recievedMsgLen;
    char messageBuf[1025];
	char buf[1025];
	FILE *fp;
	time_t mytime;
	mytime = time(NULL 	);
	
	fp = fopen("a5ServerLog.txt", "a+");
	fprintf(fp, ctime(&mytime));
	fprintf(fp, "Opened by Process ID: %d\n", getpid());
	fprintf(fp, "Opened by Thread ID: %u\n\n", (unsigned int)pthread_self());
	fclose(fp);
	
	printf("Processing client request..\n");
	printf("%s",ctime(&mytime));
	printf("Process ID: %d\n", getpid());
	printf("Thread ID: %u\n\n", (unsigned int)pthread_self());
	
    /* Server thread code to deal with message processing */
    printf("DEBUG: connection made, connectionDesc=%d\n",
            PARMPTR->connectionDesc);
    if (PARMPTR->connectionDesc < 0) {
        printf("Accept failed\n");
        return(0);    /* Exit thread */}
		
		
    
    /* Receive messages from sender... */
    while ((recievedMsgLen=
            read(PARMPTR->connectionDesc,messageBuf,sizeof(messageBuf)-1)) > 0) 
    {
        recievedMsgLen[messageBuf] = '\0';
        printf("Message: %s\n",messageBuf);
		
		
   /* Create SQL statement */
   sqlEx(messageBuf);
   

		if (write(PARMPTR->connectionDesc, sqlG,5056) < 0) {
               perror("Server: write error");
               return(0);
		}
		
		memset(sqlG, 0, sizeof(sqlG)+1);
		
    }
		   
						
   close(PARMPTR->connectionDesc);  /* Avoid descriptor leaks */
   free(PARMPTR);                   /* And memory leaks */
   return(0);                     /* Exit thread */
}/************************************************/




/********Main********/
int 
main(int argc, char **argv)  {  
    int listenDesc;
    struct sockaddr_in myAddr;
    struct serverParm *parmPtr;
    int connectionDesc;
	struct sockaddr_in servaddr;
    pthread_t threadID;
	FILE *fpLog;
	fpLog = fopen("a5ServerLog.txt", "a+");
	fclose(fpLog);

    /* For testing purposes, make sure process will terminate eventually */
    alarm(120);  /* Terminate in 120 seconds */
	
//basic check of the arguments
//additional checks can be inserted
	if (argc !=2) {
		perror("Usage: TCPCServer <Server Port>"); 
		exit(1);}

    /* Create socket from which to read */
    if ((listenDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("open error on socket");
        exit(1);
    }

    /* Create "name" of socket */
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = INADDR_ANY;
	myAddr.sin_port =  htons((int) strtol(argv[1], (char **)NULL, 10));
    //myAddr.sin_port = htons(PORTNUMBER);
    //servaddr.sin_port =  htons(argv[1]);  //this is depricated
	  
    if (bind(listenDesc, (struct sockaddr *) &myAddr, sizeof(myAddr)) < 0) {
        perror("bind error");
        exit(1);
    }

    /* Start accepting connections.... */
    /* Up to 5 requests for connections can be queued... */
    listen(listenDesc,5);

    while (1) /* Do forever */ 
	{
        /* Wait for a client connection */
        connectionDesc = accept(listenDesc, NULL, NULL);

        /* Create a thread to actually handle this client */
        parmPtr = (struct serverParm *)malloc(sizeof(struct serverParm));
        parmPtr->connectionDesc = connectionDesc;
		if (pthread_create(&threadID, NULL, serverThread, (void *)parmPtr) != 0) 
		{
            perror("Thread create error");
            close(connectionDesc);
            close(listenDesc);
            exit(1);
        }

        printf("Parent ready for another connection\n");
    }
 }
 
 
 
 
 
 /*****************************************/
 /* This function executes a sql command */
 /*	Accepts a char* sqlPtr which is 	*/
 /* the sql command to execute         */
 /*************************************/
 int sqlEx(char *sqlStr)
 {
	 char sqlPtr[strlen(sqlStr)];
	 sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char* data = "call back function called\n"; 
	strcpy(sqlPtr, sqlStr);
	
	 /* Open database */
   rc = sqlite3_open("employee.db", &db);
   if( rc )
    {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
	}
	else{fprintf(stderr, "Opened database successfully\n");}
	 
	 /* Execute SQL statement */
   rc = sqlite3_exec(db, sqlPtr, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else{fprintf(stdout, "Operation done successfully\n");}
	 
	 
 }