/* more01.c - version 0.1 of more
* read and pring 24 lines then pause for a few special commands 
*/

#include<stdio.h>
#include<stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();

int main(int ac, char*av[])
{
    FILE *fp;
    if(ac==1)           // 如果没有参数选项，从标准输P入读入
        do_more(stdin);
    else
    {
        while(--ac){    // 依次读入参数
            if((fp=fopen(*++av, "r"))!=NULL){   // 打开文件
                do_more(fp);
                fclose(fp);
            }else{
                exit(1);    // 文件打开失败
            }
            return 0;
        }
    }
}


void do_more(FILE *fp)
/*
* read PAGELEN lines, then call see_more() for further instructions
*/
{
    char line[LINELEN];
    int num_of_lines = 0;
    int see_more(), reply;
    while(fgets(line, LINELEN, fp)) // fgets成功返回line，从fp文件中读取LINELEN个字符
    {
        if(num_of_lines==PAGELEN){  // 如果显示满了一页，等待用户输入
            reply = see_more();
            if(reply==0)
                break;
            num_of_lines -= reply;
        }
        if(fputs(line, stdout)==EOF)    // 如果输出失败，退出
            exit(1);
        num_of_lines++;
    }

}

int see_more()
/*
*  print message, wait for response, return # of lines to advance
*  q means no, space means yes, CR means one line
*/
{
    int c;
    printf("\033[7m more? \033[m");
    while((c=getchar())!=EOF){
        if(c=='q')
            return 0;
        if(c==' ')
            return PAGELEN;
        if(c=='\n')
            return 1;
    }
    return 0;
}







