/** 2.3.c
 *  copy from /dev/tty1 to file 2.3.1.c
 *  my TTY file is /dev/tty1
 * 
 *  Ctrl+D to end input
 * 
 */

#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define BUFFERSIZE 10
#define CREATEMODE 0644


void oops(const char *, const char *);

int main(int ac, char * av[])
{
    int     in_fd;
    int     out_fd;
    int     nchars;
    char    buf[BUFFERSIZE];

    if(ac!=3){
        fprintf(stderr, "usage: %s source destination", av[0]);
        exit(1);
    }

    if((in_fd=open(av[1], O_RDONLY))==-1){
        oops("Open source ", av[1]);
    }

    if((out_fd=creat(av[2], CREATEMODE))==-1){
        oops("Open Destination ",av[2]);
    }

    while((nchars = read(in_fd, buf, BUFFERSIZE))!=-1){
        if(write(out_fd, buf, nchars)==-1){
            perror("Write to error");
            exit(1);
        }
    }
}

void oops(const char * s1, const char *s2)
{
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(1);
}



