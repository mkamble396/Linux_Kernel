    #include"header.h"
struct msgbuf
{
    long mtype;
    char data[20];
};
int main(int argc , char * argv[])
{
    if(argc != 3)
    {   
        printf("usage:./snd mtype msg\n" );
        printf("./snd 2 hello\n");
        return 0;
    }
    struct msgbuf v;
    int id = msgget(2,IPC_CREAT|0664);
    if(id < 0)
    {
        perror("msgget");
        return 0;
    }
    printf("id = %d\n",id);
    v.mtype = atoi(argv[1]);
    strcpy(v.data,argv[2]);
    msgsnd(id,&v,strlen(v.data)+1,0);
    perror("msgsnd");
    return 0;
    }

