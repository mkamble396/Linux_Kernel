#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main(){

  const char *ip = "127.0.0.1";
  int port = 5566;

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  int n,len;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("Socket error");
    exit(1);
  }
  cout<<"TCP server socket created."<<endl;

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);
  
  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  cout<<"Connected to the server."<<endl;
  
  while(1)
  {
  bzero(buffer, 1024);
  cout<<"Enter the Message for server : "; 
  cin.getline(buffer,sizeof(buffer));
  len=strlen(buffer);
  cout<<"Client: "<<buffer<<" (Length = "<<len<<")"<< endl;
  send(sock, buffer, strlen(buffer), 0);
  //cout<<"send is working : ";

  bzero(buffer, 1024);
  recv(sock, buffer, sizeof(buffer), 0);
  //cout<<"recv is working : ";
  len=strlen(buffer);
  cout<<"Server : "<<buffer<<" (Length = "<<len<<")"<< endl;
  }
  return 0;
}



