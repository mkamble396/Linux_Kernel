#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int c,char *v[])
{
	if(c != 2)
	{
		printf("./a.out filename");
		return 0;
	}
	int in,nread,out,line=0,count=0;
	char buff[20];
	in=open(v[1],O_RDONLY);
	while((nread=read(in,buff,1))>0)
	{
		if (*buff=='\n')
			line++;					//Counting total number of lines
	}

	lseek(in,0,SEEK_SET);						//setting the cursor from starting
	line=line-10;							
	if (line>0)							//condition checking only 10 lines code if file contain more than 3 lines
	{
		while((nread=read(in,buff,1))>0)
		{
			if(count>=line)				//condition to print last 10 lines
				write(1,buff,nread);
			if(*buff == '\n')
				count++; 
		}
	}
	else								//prints the all lines of code beacuse it has below 3 lines
	{
		while((nread=read(in,buff,1))>0)
			write(1,buff,nread);
	}
	close(in);
}
