/**cp1.c
 *  version 1 of cp - uses read and write with tunable buffer size
 *  usage : cp1 src dest
 */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(const char *, const char *);

int main(int ac, char* av[])
{
    int in_fd,out_fd,n_chars;
    char buf[BUFFERSIZE];


    if(ac!=3){                                                      /*检查参数*/
        fprintf(stderr, "usage: %s source destination\n", *av);
        exit(1);
    }
                                                                    /*打开文件*/
    if((in_fd=open(av[1],O_RDONLY))==-1){
        oops("Cannot open ", av[1]);
    }

    if((out_fd=creat(av[2], COPYMODE))==-1){
        oops("Cannot create ", av[2]);
    }
                                                                    /*read最大读取BUFFERSIZE个字节，在文件末尾可能读不够BUFFERSIZE个字节*/
    while((n_chars = read(in_fd, buf, BUFFERSIZE))>0){
        if(write(out_fd,buf,n_chars)!=n_chars)
            oops("Write error to ", av[2]);
    }
    if(n_chars == -1){
        oops("Read error from ", av[1]);
    }

    if(close(in_fd)==-1 || close(out_fd)==-1)
        oops("Error closing files", "");
}

void oops(const char * s1, const char *s2)
{
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(1);
}






