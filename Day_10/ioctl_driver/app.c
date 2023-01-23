#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int8_t write_buf[1024];
int8_t read_buf[1024];

int main()
{
	int fd;
	char option;

	printf("WELCOME\n");

	fd = open("/dev/my_device",O_RDWR);
	if(fd<0)
	{
		printf("Cannot open device file..\n");
		return 0;
	}

	while(1)
	{
		printf("***Please enter your option\n");
		printf("1.write\n");
		printf("2.read\n");
		printf("3.Exit\n");
		scanf(" %c",&option);
		printf("Your option %c\n",option);
		
		switch(option)
		{
			case '1':
				printf("Enter the string to write into the driver\n");
				scanf("%s",write_buf);
				printf("Data written\n");
				write(fd,write_buf,strlen(write_buf)+1);
				printf("Done\n");
				break;

			case '2':
				printf("Data is reading\n");
				read(fd,read_buf,1024);
				printf("Done\n");
				printf("Data read %s\n",read_buf);
				break;

			case '3':
				close(fd);
				exit(1);
				break;

//			default:
//				printf("Enter valid option\n");
//				break;
		}
	}
	close(fd);
}
