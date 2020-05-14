
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int
main(){

int ret, i;
int size = 1024;
char *buf;
buf = (char*)malloc(50*sizeof(char));


ret = mkdir("a4part1", 0700);

if(getcwd(buf, size) == NULL)
{
printf("error3\n");
}


chdir("/home/012/j/jr/jrt160530/asn4/a4part1");

ret = mkdir("folder1", 0700);
chdir("/home/012/j/jr/jrt160530/asn4/a4part1/folder1");

creat("file1", S_IRWXU);

chdir("/home/012/j/jr/jrt160530/asn4/a4part1");

ret = mkdir("folder2", 0700);
chdir("/home/012/j/jr/jrt160530/asn4/a4part1/folder2");


creat("file2", S_IRWXU);
chdir("/home/012/j/jr/jrt160530/asn4/a4part1");

creat("file3", S_IRWXU);
symlink("/home/012/j/jr/jrt160530/asn4/a4part1/folder2/file2", "link4");



return(0);

}

