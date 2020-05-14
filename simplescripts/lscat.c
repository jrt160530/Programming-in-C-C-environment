/*
 * This program will search the current directory
 * and print the contents of files
 * with the .c extension.
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int
main(int argc, char **argv) {

	DIR *dp;
	struct dirent *dirp;
	char filename[80];
	int  name_length;
	char c[10] = ".c\0";
	char *ret;
	int ch;
	FILE *fp;

	//invalid amount of args
	if (argc != 2) {
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	//opens directory if not a null file
	if ((dp = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "can't open '%s'\n", argv[1]);
		exit(1);
	}

	//reads each line in directory until NULL
	while ((dirp = readdir(dp)) != NULL )
	{
			//memset(filename, '\0', sizeof(filename));
			//printf(" ** %s ", filename);
			//name_length = strlen(filename);
			//printf(" name_length=%d \n", name_length);

		strcpy(filename, dirp->d_name);
		ret = strstr(filename,c);	//finds a string within a string
									//matching string stored in c

		//if there is a value in ret
		if(ret)
		{	//checks for cases in which the .c is not at the end of file
			if((strcmp(ret,c) == 0))
			{
				//opens up a FILE *filepointer
				//r sets read only
				//name of file from dirp->d_name
				fp = fopen(dirp->d_name,"r");

				//checks if FILE fp is null
				if( fp == NULL )
				   {
				      perror("Error while opening the file.\n");
				   }

				//prints out each character until End Of File
				while( ( ch = fgetc(fp) ) != EOF )
				      printf("%c",ch);

				//closes FILE fp
				fclose(fp);
			}

			}
		}
		
	closedir(dp);
	return(0);
}


