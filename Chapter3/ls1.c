/**
 * ls1.c 
 *    purpose list contents of directory or directories
 *    action if no args, use . else list files in args
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>

void do_ls(char[]);

int main(int ac, char * av[])
{
    if(ac==1)
        do_ls(".");
    else{
        while(--ac){
            printf("%s:\n", *++av);
            do_ls(*av);
        }
    }
}


void do_ls(char dirname[])
{
    DIR *dir_ptr;
    struct dirent *direntp;
    if((dir_ptr=opendir(dirname))==NULL){
        fprintf(stderr, "ls1: can not open %s\n",dirname);
    }else{
        while((direntp = readdir(dir_ptr))!=NULL){
            printf("%s\n",direntp->d_name);
        }
        closedir(dir_ptr);
    }
}











