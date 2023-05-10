#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
char buffer[2];
int main()
{
	int fd1,fd2;

	fd1=open("/sys/class/gpio/gpio60/direction",O_WRONLY); 
	write(fd1,"out", 3);
        close(fd1);
//	printf("Board connected %ld\n",sizeof("out"));

	fd2=open("/sys/class/gpio/gpio60/value",O_WRONLY);
	//while(1)
        //read(fd2,buffer,sizeof(buffer));
	for(int i=0;i<10;i++)
	{
				write(fd2,"1",1);  //turn on 
				sleep(1);

			
				//buffer[0]=0;
				write(fd2,"0",1); //turn off
				sleep(1);
			

	}
//close(fd1);
close(fd2);

return 0;
}
