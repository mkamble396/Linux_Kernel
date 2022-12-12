// Write a system programming your own version of du & touch command


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[])
 {
        short int i;

  
 open(argv[1], O_CREAT |  O_WRONLY | O_TRUNC, 0700);  // first we open f1 file in read mode only and f2 file either created in write mode 0700 used for giving permission for read wite exexute that file.
 }
