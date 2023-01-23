//program to convert lower letter into upper letters
#include"header.h"
void main()
{
	int p[2],i,p1[2];
	if(pipe(p)<0 || pipe(p1)<0)
	{
		perror("pipe:");
		return;
	}
	if(fork()==0)
	{//child
		char s[20];
		printf("in child before read..\n");
		read(p[0],s,sizeof(s));
		for(i=0;s[i];i++)
			if(s[i]>='a' && s[i]<='z')
				s[i]=s[i]-32;
				write(p1[1],s,strlen(s));

	}
	else
	{//parent
		char a[20];
		printf("enter string:\n");
		gets(a);
		write(p[1],a,strlen(a)+1);
		//sleep(1);
		read(p1[0],a,sizeof(a));
		printf("data is:%s\n",a);
	}
}
