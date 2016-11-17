#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX   1594323

int data[MAX];
int num;
double start,finish;

int thr(int x)                 //返回3的x次方
{
  int i=1;
  for(;x>0;x--)i=i*3;
  return i;
}

char name_r[100];
void name(int k)                      //生成写入已排序数据的文件名
{
  char path[]="/home/talent/PB14011029-project1/ex2/output/bubble_sort/";
  char s1[]="result_";
  char s2[2];
  char s3[]=".txt";
  sprintf(s2,"%d",k);
  strcat(s1,s2);
  strcat(s1,s3);
  strcat(path,s1);
  strcpy(name_r,path);
}

void read_d()                         //读取将要排序的数据
{
  int i=0;
  FILE *fp;char read_name[]="/home/talent/PB14011029-project1/ex2/input/input_numbers.txt";
  fp=fopen(read_name,"rt");
  for(i=0;i<num;i++) fscanf(fp,"%d",&data[i]);
  printf("Read Done!\n");
}

void write_d(int d[])                      //将每次排序结果写入result_n.txt中去
{
  FILE *fp;
  int i;
  fp=fopen(name_r,"wt+");
  for(i=0;i<num;i++)
    {
      fprintf(fp,"%d\n",data[i]);
    }
  fflush(fp);
  fclose(fp);
  printf("Write_d Done!\n");
}

FILE *fp_t;int flag=0;
void write_t(int k)                           //将每次排序时间写入time.txt文件中去
{
  float ti;char time_name[]="/home/talent/PB14011029-project1/ex2/output/bubble_sort/time.txt";
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


void bubble_sort(int d[])                    //冒泡排序
{
  int i,j;
  for(i=0;i<num-1;i++)
   {
     for(j=0;j<num-1-i;j++)
       {
          if(d[j]>d[j+1])
           {
              int temp;
              temp=d[j];
              d[j]=d[j+1];
              d[j+1]=temp;
           }
       }
   }
}



int k;
int main()                         //主函数
{
  printf("3 的 x 次方\n");
  scanf("%d",&k);
  num=thr(k);
  name(k);
  read_d();
  start=clock();
  bubble_sort(data);
  finish=clock();
  write_d(data);
  write_t(k);
  printf("规模：3的%d次方   时间： %f seconds\n\n\n",k,(finish - start) / CLOCKS_PER_SEC);
  main();
}
