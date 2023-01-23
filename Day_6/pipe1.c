#include"header.h"
void main()
{
	int p[2];
	pipe(p);
	perror("pipe:");
	printf("p[0]=read file=%d\n",p[0]);
	printf("p[1]=write file=%d\n",p[1]);
	if(fork())
	{//parent
		char s[20];
		printf("in parent... enter a data\n");
		scanf("%s",s);
		write(p[1],s,strlen(s)+1);//if pipe is full write will block
		perror("parent write");
	}
	else
	{//child
		char s1[20];
		printf("child before read\n");
		read(p[0],s1,sizeof(s1));//if pipe is empty read will block
		printf("in child after read s1=%s\n",s1);
	}

}
