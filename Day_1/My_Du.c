#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>


int main(int argc, char const *argv[])
{
	int fd1 ; 
	float fd2 , ret ;
	struct stat statbuf;

	//fd1 = open(argv[1],O_RDONLY);
	ret = stat(argv[1],&statbuf);

	fd2 = (statbuf.st_blksize);//4096;

//	printf("File Size :- %ld\n",statbuf.st_blksize);
	printf("block Size :- %ld\n",statbuf.st_blocks/2);
//	printf("total Size :- %ld\n",statbuf.st_size);

	return 0;
}
