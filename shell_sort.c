#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX   1594323

long thr(int x)             //返回3的x次方
{
  long i=1;
  for(;x>0;x--)i=i*3;
  return i;
}



long num;
int gaps[]={21,15,7,3,1};
double start,finish;
static char str[MAX][20];


char name_r[100];
void name(int k)              //生成写入已排序数据的文件名
{
  char path[]="/home/talent/PB14011029-project1/ex1/output/shell_sort/";
  char s1[]="result_";
  char s2[2];
  char s3[]=".txt";
  sprintf(s2,"%d",k);
  strcat(s1,s2);
  strcat(s1,s3);
  strcat(path,s1);
  strcpy(name_r,path);
}

void read_s(char str[][20])            //读取将要排序的数据
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

void write_s(char str[][20])           //将每次排序结果写入result_n.txt中去
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
void write_t(int k)             //将每次排序时间写入time.txt文件中去
{
  float ti;char time_name[]="/home/talent/PB14011029-project1/ex1/output/shell_sort/time.txt";
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



int compare(char *x,char *y)             //比较两个字符大小
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


long sub(int g,int i,int j)          //按增量分组后各个同组数据的下标
{
  return(i+g*j);
}

void shell(char s[][20],int g)         //分组插入排序
{
  int i,j,k;
  char key[20];
  if(g<num)
    {
      for(i=0;i<=g;i++)
       {
           for(j=1;sub(g,i,j)<num;j++)
             {
               strcpy(key,s[sub(g,i,j)]);
               k=j-1;
               while(sub(g,i,k)>=0&&compare(s[sub(g,i,k)],key)==0)
                 {
                    strcpy(s[sub(g,i,k+1)],s[sub(g,i,k)]);
                    k=k-1;
                 }
               strcpy(s[sub(g,i,k+1)],key);
             }
       }
    }
}

void shell_sort(char s[][20],int g[])       //希尔排序
{
   int i;
   for(i=0;i<5;i++) shell(s,g[i]);
}


int k;
int  main()                          //主函数
{
  printf("3 的 x 次方\n");
  scanf("%d",&k);
  num=thr(k);
  read_s(str);
  start=clock();
  shell_sort(str,gaps);
  finish=clock();
  name(k);
  write_s(str);
  write_t(k);
  printf("规模：3的%d次方   时间： %f seconds\n\n\n",k,(finish - start) / CLOCKS_PER_SEC);
  main();
  return 0;
}
