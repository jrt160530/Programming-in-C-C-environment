#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/times.h>
//This program will accept an input stream
//It passes the command to the built-in system("command") 
//It's suppose to handle the chdir() and getcwd().
//exit,dont, quit, by to terminate program.
int main()
{
	char str[30];		//holds char[] for input stream
	char scpy[30];
	char *t;		//Pointer to hold token
	char c;			//holds char to insert into char[]
	int i = 0;		//i for an iterator

    printf("Enter Command \n");
    while(c != '\n')   		// will character is not newline(pressing enter)
    {
        c = getchar();		//gets char and assigns it to c
        str[i] = c;		//outs c into str[i]. i=iterator
        i++;			//iterates i
    }
    str[i] = '\0';       //insert null character. used to find EOL

strcpy(scpy, str);

if(strcmp("exit\n",scpy) == 0){return(0);}
if(strcmp("quit\n",scpy) == 0){return(0);}
if(strcmp("bye\n",scpy) == 0){return(0);}
if(strcmp("done\n",scpy) == 0){return(0);}
//if(strcmp("cd\n",scpy) == 0){printf("hi world");
//		chdir();}
t = strtok (scpy," ");	
if(strcmp("cd",t) == 0){chdir(t=strtok(NULL,t));}


system(str);
 

//if chdir is called with system(str) 
//it will return value of 32512
//if(system(str) == 32512)


 
main();


}

