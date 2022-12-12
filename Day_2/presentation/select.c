#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<linux/input.h>
int main(int argc, char *argv[])
{
    fd_set rfds;
    struct timeval tv;
    int retval;
	/*Watch stdin (fd 0) to see when it has input*/
	FD_ZERO(&rfds);
	FD_SET(0,&rfds);
/* Wait up to five seconds. */
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don’t rely on the value of tv now!*/
	if(retval == 0) {
                printf("select timeout:\n");
        }
        else if(retval == -1){
                printf("fail to select\n");
        }
        else{
    		printf("data is avaliable\n");
        }
	return 0;
}
