/*wo processes, client and server, communicate via two message queues "Up" and "Down".
Server
^ |
Up | v Down
Client
The client reads a message from the standard input and sends it to the server via the Up queue, then waits for the server's answer on the Down queue. The server is specialized in converting characters from lower case to upper case and vice versa. Therefore, if the client sends the message "lower case" via the Up message queue, the server will read the message, convert it, and send "LOWER CASE" via the Down queue. When the client receives the message from the server, it prints it out. You may assume the maximum size of any message is 256 bytes.
Multiple clients must be able to connect to the up and down queues. However, what happens if one client puts a letter to convert on the system and another client is waiting for it's response from the queue? There are different ways to handle this, but you should handle this using typed messages. Each client has a particular client number based on the last 4 digits of its process ID. Use this 4-digit number as the client identifier, and use typed messages on the queue so that each client can always be sure to receive the letter that it is waiting on to be converted.
*/


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
	  
    }

    close(client_fd);
    return 0;
}
