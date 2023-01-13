#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
  
int main(int argc, char const* argv[])
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;

    //creating client socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {

        printf("\n Socket creation error \n");
        return -1;
    }
    // printf("Hi \n");

  //creating connection to server
  //initializing the address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
  
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
    {
        printf("\nInvalid address\n");
        return -1;
    }
  // printf("Hi \n");

    
    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0) //The connect() system call establishes a connection with another socket.
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    char buffer[1024];
    int n;
    while(1){
	    bzero(buffer, 1024);
	    printf("enter message:");
	    n=0;
	    while((buffer[n++]=getchar())!= '\n');
	    write(sock,buffer,strlen(buffer));
	    bzero(buffer,1024);
	    read(sock,buffer,1024);
	    printf("From Server : %s",buffer);
	  //  break;
    }
	// printf("Hi \n");

  
    // closing the connected socket
    close(client_fd);
    return 0;
}
