/*
* who1.c - a first version of who program
*          open, read and UTMP file and show results
*/

#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>

#define SHOWHOST

void show_info(struct utmp *);
int main()
{
    struct utmp current_record;     /*读入登录用户到这个结构*/
    int utmpfd;         /*文件描述符*/
    int reclen = sizeof(current_record);    // 结构体长度

    if((utmpfd = open(UTMP_FILE, O_RDONLY))==-1){
        perror(UTMP_FILE);
        exit(1);
    }

    while(read(utmpfd, &current_record, reclen)==reclen)    /*读入一个结构体的长度，并显示*/
        show_info(&current_record);
    close(utmpfd);
    return 0;
}

void show_info(struct utmp *utbufp)
{
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    printf("%10d",utbufp->ut_tv.tv_sec);
    printf(" ");
# ifdef SHOWHOST
    printf("(%s)",utbufp->ut_host);
# endif
    printf("\n");
}











