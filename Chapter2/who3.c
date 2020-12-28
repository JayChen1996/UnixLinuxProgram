#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>

#define SHOWHOST

void show_info(struct utmp *);
void show_time(time_t* timeval);

int          utmp_open(char *);
struct utmp* utmp_next();
void         utmp_close();

int main()
{
    struct utmp *current_record;     /*读入登录用户到这个结构*/

    if(utmp_open(UTMP_FILE)==-1){
        perror(UTMP_FILE);
        exit(1);
    }

    while((current_record = utmp_next())!=((struct utmp *)NULL))    /*读入一个结构体的长度，并显示*/
        show_info(current_record);
    utmp_close();
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
    show_time((time_t *)&(utbufp->ut_tv.tv_sec));
    printf(" ");
# ifdef SHOWHOST
    printf("(%s)",utbufp->ut_host);
# endif
    printf("\n");
}

void show_time(time_t* timeval)
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