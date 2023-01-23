// Try fork system as per codevault video

#include<stdio.h>
#include<unistd.h>

int main(int c,char*v[])
{
    int id=fork();
    fork();
//    printf("Hello from id=%d\n",id);
    if(id==0){
        printf("Hello from child\n");
    }
    else{
        printf("Hello from Parent\n");
    }
}
