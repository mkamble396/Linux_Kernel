//. Write a system programming your own version of wc command
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
int main(int c, char**v)
{
    char ch, prev= ' ';
    int fd, size, charac_count=0,word_count=0,line_count=0;
    fd= open(v[1],O_RDONLY);
    if(fd<0)
    {
        perror("Usage:./WC file name\n");
        return 0;
    }

    while((read(fd,&ch,1))>0) //reading 1 byte by byte data
        {
            charac_count++; //character count
            if((ch==' '|| ch=='\t' || ch=='\n'))
            {
                if(prev !=' '&& prev!='\t' && prev!='\n')
                {
                    word_count++; //word count
                }
            }
                if(ch=='\n')
                {
                    line_count++; //line count
                }
                prev=ch;
        }
    printf("Line Count-%d\t Word Count-%d\t Character count-%d\tFile name-%s\n",line_count,word_count,charac_count,v[1]);
}
