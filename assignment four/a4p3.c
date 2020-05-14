#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int callFx(char c[]);

int main()
{
char com[50];
char ch;
int i;

printf("enter commands\n");
while(ch != '\n')    // terminates if user hit enter
    {
        ch = getchar();
        com[i] = ch;
        i++;
    }
    	com[i] = '\0';       // inserting null character at end
if(callFx(com) != 1)
	printf("error\n");

}//end of main



int callFx(char c[])
{
int i = 0;
char *buf[10];
char *t;

c = strtok (c," ");

while(c != NULL)
{
buf[i++] = c;
printf("%s\n",c);
c = strtok (NULL," ");
}
i=0;
while(buf[i] != 0)
{
printf("%s ", buf[i++]);
}

return(1);

}//callFx