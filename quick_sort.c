#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX   1594323

long thr(int x)                    //返回3的x次方
{
  long i=1;
  for(;x>0;x--)i=i*3;
  return i;
}



long num;
double start,finish;
static char str[MAX][20];


char name_r[100];
void name(int k)                      //生成写入已排序数据的文件名
{
  char path[]="/home/talent/PB14011029-project1/ex1/output/quick_sort/";
  char s1[]="result_";
  char s2[2];
  char s3[]=".txt";
  sprintf(s2,"%d",k);
  strcat(s1,s2);
  strcat(s1,s3);
  strcat(path,s1);
  strcpy(name_r,path);
}


void read_s(char str[][20])                   //读取将要排序的数据
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


void write_s(char str[][20])                   //将每次排序结果写入result_n.txt中去
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
void write_t(int k)                         //将每次排序时间写入time.txt文件中去
{
  float ti;char time_name[]="/home/talent/PB14011029-project1/ex1/output/quick_sort/time.txt";
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


int compare(char *x,char *y)                 //比较两个字符大小
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


long partition(char s[][20],long p,long r)        //对数组A[p..r]的原址重排
{
  char x[20],t[20];
  long i=p-1,j=0;
  strcpy(x,s[r]);
  for(j=p;j<r;j++)
   {
      if(compare(x,s[j])==0)
        {
           i++;
           strcpy(t,s[i]);
           strcpy(s[i],s[j]);
           strcpy(s[j],t);
        }
   }
  strcpy(t,s[i+1]);
  strcpy(s[i+1],s[r]);
  strcpy(s[r],t);
  return(i+1);
}

void quick_sort(char s[][20],long p,long r)        //快速排序
{
  long q;
  if(p<r)
    {
      q=partition(s,p,r);
      quick_sort(s,p,q-1);
      quick_sort(s,q+1,r);
    }
}


int k;
int  main()                         //主函数
{
  printf("3 的 x 次方\n");
  scanf("%d",&k);
  num=thr(k);
  read_s(str);
  start=clock();
  quick_sort(str,0,num-1);
  finish=clock();
  name(k);
  write_s(str);
  write_t(k);
  printf("规模：3的%d次方   时间： %f seconds\n\n\n",k,(finish - start) / CLOCKS_PER_SEC);
  main();
  return 0;
}
