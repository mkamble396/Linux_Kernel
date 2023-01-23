#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) //Socket creation 
  {
        printf("\n socket failed \n");
        return -1;
    }
	//printf("Hello world \n");
     //for binding
     //for initialising the address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

//The bind() system call binds a socket to an address. Usually, a server employs this call to bind its socket to a well-known address so that clients can locate the socket.
    if (bind(server_fd, (struct sockaddr*)&address sizeof(address)) < 0) {
        printf("\n bind failed \n");
        return -1;
    }
   // printf("Hi \n");
    
    //for listening from client The listen() system call allows a stream socket to accept incoming connections from other sockets.
    if (listen(server_fd, 3) < 0) {
        printf("\n listen \n");
        return -1;
    }

    
    // printf("Hi \n");

    //for accepting by creating a new socket to communicate with client  The accept() system call accepts a connection from a peer application on a listening stream socket, and optionally returns the address of the peer socket.

    new_socket= accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen);
    if (new_socket<0){
	    printf("Failed\n");
	    return -1;
    }
    char buffer[1024];
    int n;
    while(1){
	    bzero(buffer,1024);
	    read(new_socket,buffer,1024);
	    printf("From client: %sTo client : ", buffer);
	    bzero(buffer,1024);
	    n=0;
	    while((buffer[n++]=getchar()) != '\n');
	    write(new_socket,buffer,1024);
	    
    }
	
    // printf("Hi \n");

  // closing the connected socket
    close(new_socket);
  // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
