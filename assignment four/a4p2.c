#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void fx1(char *);
static int readD(char *p);
static void getPath(char *p);
void infoX();


int main(int argc, char *argv[])
{
/*variables*/
int ret, pid;
char *apn;
DIR *dir;
struct dirent *entryD;

apn = "/home/012/j/jr/jrt160530/asn4/a4part1";
fx1(apn);
printf("\n----------------------------------------------------\n");
getPath(apn);


}//end of main


/***********************************/
/*This function gets the pathname */
/*path name is static            */
/********************************/

static char *pn;      
static size_t plen;
struct stat statbuf;

static void getPath(char *p)
{
pn = (char*)malloc(50*sizeof(char));

if (plen <= strlen(p)) 
	{
        plen = strlen(p) * 2;
        if ((pn = realloc(pn, plen)) == NULL)
            printf("allocation error\n");
	}
strcpy(pn, p);
readD(pn);

}//end of getPath


/************************************/
/*Reads each entry in a directory   */
/*if entry is directory 	    */
/*open directory and check contents */
/***********************************/
static int readD(char *p)
{
    struct dirent   *entryD;
    DIR             *dr;
    int             ret, n;
chdir(p);
if ((dr = opendir(p)) == NULL) 
	printf("error: can't open directory\n");

while((entryD = readdir(dr)) != NULL)
{	
	/* ignore dot and dot-dot */
	if (strcmp(entryD->d_name, ".") == 0  ||
          strcmp(entryD->d_name, "..") == 0)
                continue;   
	
	if (lstat(entryD->d_name, &statbuf) < 0) 
		{
            	printf("lstat error");
		}   
	printf("%s\n", entryD->d_name);
	infoX();
	
	
	if(S_ISDIR(statbuf.st_mode))
	{
	n=strlen(pn);
	pn[n++] = '/';
    	pn[n] = 0;
	strcpy(&pn[n], entryD->d_name);
	
	if(readD(pn) == 1)
		printf("success\n");
	}	
}	pn[n-1] = 0;
	if (closedir(dr) < 0)
        	printf("can't close directory %s", pn);
	
return(1);
}//end of readD



void infoX()
{

    int         i;
    char        *ptr;
	
        
        if (S_ISREG(statbuf.st_mode))
            ptr = " -regular";
        else if (S_ISDIR(statbuf.st_mode))
            ptr = " -directory";
        else if (S_ISCHR(statbuf.st_mode))
            ptr = " -character special";
        else if (S_ISBLK(statbuf.st_mode))
            ptr = " -block special";
        else if (S_ISFIFO(statbuf.st_mode))
           ptr = " -fifo";
        else if (S_ISLNK(statbuf.st_mode))
            ptr = " -symbolic link";
        else if (S_ISSOCK(statbuf.st_mode))
            ptr = " -socket";
        else
            ptr = "** unknown mode **";
        printf("%s\n", ptr);
	printf(" -i-node: %i\n", statbuf.st_ino);
    
}




/****************************************/
/*This function, fx1 uses fork and exec */			
/*to call:				*/
/*ls -R and				*/
/*pwd					*/
/****************************************/
void fx1(char *ptr)
{
char *p;
int ret, pid;

chdir(p);
pid = fork();
if(pid == 0)
{

pid = fork();
if(pid == 0)
{
if(ret = execl ("/bin/pwd", "pwd", (char *)0) < 0)
	printf("error: pwd");
exit(0);
}
else{wait(1);}


if(ret = execl ("/bin/ls", "ls", "-R", (char *)0) < 0)
	printf("error: ls -R");
exit(0);
}
else{wait(1);}


} //end of function







