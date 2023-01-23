#include"header.h"
struct msgbuf
{
    long mtype;
    char data[20];
};
int main(int argc , char * argv[])
{
    if(argc != 2)
    {   
        printf("usage:./rcv mtype\n" );
        printf("./rcv 2 \n");
        return 0;
    }
    struct msgbuf v;
    int id = msgget(2,IPC_CREAT|0664);
    if(id < 0)
    {
        perror("msgget");
        return 0;
    }
    printf("before msgrcv\n");
    msgrcv(id,&v,sizeof(v),atoi(argv[1]),0);
    printf("after msgrcv\n");
    printf("data is = %s\n",v.data);
    return 0;
    }

