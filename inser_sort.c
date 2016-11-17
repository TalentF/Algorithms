#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX   1594323

long thr(int x)                //返回3的x次方
{
  long i=1;
  for(;x>0;x--)i=i*3;
  return i;
}

char name_r[100];
void name(int k)               //生成写入已排序数据的文件名
{
  char path[]="/home/talent/PB14011029-project1/ex1/output/inser_sort/";
  char s1[]="result_";
  char s2[2];
  char s3[]=".txt";
  sprintf(s2,"%d",k);
  strcat(s1,s2);
  strcat(s1,s3);
  strcat(path,s1);
  strcpy(name_r,path);
}

long num;
double start,finish;
static char str[MAX][20];


void read_s(char str[][20])                 //读取将要排序的数据
{
  FILE *fp;
  int  i=0; 
  char read_name[]="/home/talent/PB14011029-project1/ex1/input/input_strings.txt";
  fp = fopen(read_name,"rt");
  while(i<num)
   {
      fgets(str[i],18,fp);
      str[i][strlen(str[i])-1]='\n';
      i++;
   }
 fclose(fp);
 printf("Read  Done!\n");
}

void write_s(char str[][20])              //将每次排序结果写入result_n.txt中去
{
  FILE *fp;
  int i;
  fp=fopen(name_r,"wt+");
  for(i=0;i<num;i++)
   {
     fputs(str[i],fp);
   }
 fclose(fp);
 printf("Write_s Done!\n");
}

FILE *fp_t;int flag=0;
void write_t(int k)                            //将每次排序时间写入time.txt文件中去
{
  float ti;char time_name[]="/home/talent/PB14011029-project1/ex1/output/inser_sort/time.txt";
  ti=(finish - start) / CLOCKS_PER_SEC;
  if(flag==0)
   {
     remove(time_name);
     fp_t=fopen(time_name,"wt+");
     flag=1;
   }
  fseek(fp_t,0,SEEK_END);
  fprintf(fp_t,"%d %c %f %s\n",k,':',ti,"seconds");
  fflush(fp_t);
  printf("Write_t Done!\n");
}

int compare(char *x,char *y)               //比较两个字符串大小
{
  int i,j;
  i=strlen(x);
  j=strlen(y);
  
  if(i>j) return 0;
  else if(i<j) return 1;
  else if(i==j)
   {
      int i;
      for(i=0;i<=strlen(x);i++)
       {
         if(x[i]>y[i])
           {
             return 0;
             break;
           }
        else if(x[i]<y[i])
           {
             return 1;
             break;
           }
       }
    return 0;
   }
}


void inser_sort(char s[][20])                 //插入排序
{
  long  i,j;
  char ch[17];
  for(j=1;j<num;j++)
   {
     strcpy(ch,str[j]);
     i=j-1;
     while(i>=0&&compare(s[i],ch)==0)
       {
          strcpy(s[i+1],s[i]);
          i=i-1;
       }
     strcpy(s[i+1],ch);
   }
}

int k;
void main()                           //主函数
{
  printf("3 的 x 次方\n");
  scanf("%d",&k);
  num=thr(k);
  name(k);
  read_s(str);
  start=clock();
  inser_sort(str);
  finish=clock();
  write_s(str);
  write_t(k);
  printf("规模：3的%d次方   时间： %f seconds\n\n\n",k,(finish - start) / CLOCKS_PER_SEC);
  main();
}
