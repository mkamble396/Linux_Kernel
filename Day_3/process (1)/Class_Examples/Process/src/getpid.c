#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	//fork();
	//fork();
	//fork();

	printf ("My pid=%d ppid=%d \n", getpid( ),getppid());

	getchar();

	return (0);
}
