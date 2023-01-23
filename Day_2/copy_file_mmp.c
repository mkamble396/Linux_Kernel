
//Write an Linux System Programming copy one file content to another file using mmap() system call



#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h> // for using mmap
#include<sys/mman.h> //for mmap operation
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
     
                       // condition to check whether the required argument are passed or not
     if(argc<3)
     {
     printf("Usages:./a.out Sourcefile Destinationfile\n");
     return 0;
     }
      int source_file, desti_file;   // file discripter 
    char *sou, *dest;
  
    
    struct stat s;  //stat is used for finding out the sizeof the file
 
    source_file = open(argv[1], O_RDONLY);
  
    fstat(source_file, &s);



   sou = mmap(NULL, 1, PROT_READ, MAP_PRIVATE, source_file, 0);// mmap creates a new mapping in virtual address space of calling process.




    desti_file = open(argv[2], O_RDWR | O_CREAT ,0777);




    dest = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_SHARED, desti_file, 0);

    /* COPY */

    /* from source to destination , number of bytes*/
    for(int i = 0; i<s.st_size; i++)
    {
        write(desti_file,&sou[i], 1);
    }
    close(source_file);
    close(desti_file);
         return 0;
}
