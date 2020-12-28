/*
* who2.c - read /var/run/utmp and list info therein
*        - suppresses empty records
*        - formats time nicely
*/

#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define SHOWHOST

void show_info(struct utmp *);
void show_time(int32_t timeval);
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
    if(utbufp->ut_type!=USER_PROCESS)
        return;

    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    show_time(utbufp->ut_tv.tv_sec);
    printf(" ");
# ifdef SHOWHOST
    printf("(%s)",utbufp->ut_host);
# endif
    printf("\n");
}

void show_time(int32_t timeval)
/*
* displays time in formate fit for human consumption
* uses ctime to build a string then picks parts out of it
* Note: %12.12s prints a string 12 chars wide and LIMITS
* it to 12chars.
*/
{
    char *cp;
    cp = ctime(timeval);
    printf("%12.12s",cp+4);
}





