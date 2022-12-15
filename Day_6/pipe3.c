//find size of pipe 



#include "header.h"
void main()
{
    int p[2];

    /*O_NONBLOCK  Set the O_NONBLOCK file status flag on the open file descriptions referred to by the new file descriptors.Using this flag saves extra calls to fcntl(2) to achieve
              the same result.*/
    pipe2(p,O_NONBLOCK);  //O_NONBLOCK it is available in #include <fcntl.h> header file

    int c=0;
    char ch='a';
    while(write(p[1],&ch,1) != -1)
    {
        c++;
        printf("%d\n",c);
    }
    printf("BYE....\n");
}
