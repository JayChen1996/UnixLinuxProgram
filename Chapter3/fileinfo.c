/**
 * fileinfo.c - use stat() to obtain and print file properties
 *            - some members are just numbers
 */

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>

int show_stat_info(char *, struct stat *);

int main(int ac, char* av[])
{
    struct stat info;

    if(ac>1){
        if(stat(av[1], &info)!=-1){
            show_stat_info(av[1], &info);
            return 0;
        }else{
            perror(av[1]);
        }
    }
    return 1;
}

int show_stat_info(char *fname, struct stat *buf)
/*
* display some info from stat in a name = value format
*/
{
    printf("   mode: %o\n",  buf->st_mode);
    printf("  links: %ld\n", buf->st_nlink);
    printf("   user: %d\n",  buf->st_uid);
    printf("  group: %d\n",  buf->st_gid);
    printf("   size: %ld\n", buf->st_size);
    printf("modtime: %s\n", ctime(buf->st_mtime));
    printf("   name: %s\n",  fname);
}





