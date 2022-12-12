#include<stdio.h>
#include<fcntl.h>
#include <linux/input.h>
int main(int argc, char *argv[])
{
	int fd1, retfd;
	char buf[4096];
	int val;
	char name[256];

	//argv[1] has in format /dev/input/event0

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 3) {
		printf("Open Fails");
		return -1;
	}
	//function call to get device name
	ioctl(fd1, EVIOCGNAME(sizeof(name)), name);
	printf("Input device name: \"%s\"\n", name);

	return 0;
}
