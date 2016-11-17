#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX   1594323

static char data[MAX][10],data_2[MAX][10],data_3[MAX][10];
int num;
double start,finish;

int thr(int x)             //返回3的x次方
{
  int i=1;
  for(;x>0;x--)i=i*3;
  return i;
}

char name_r[100];
void name(int k)             //生成写入已排序数据的文件名
{
  char path[]="/home/talent/PB14011029-project1/ex2/output/radix_sort/";
  char s1[]="result_";
  char s2[2];
  char s3[]=".txt";
  sprintf(s2,"%d",k);
  strcat(s1,s2);
  strcat(s1,s3);
  strcat(path,s1);
  strcpy(name_r,path);
}

int zero_num(char d[])          //返回每个数据补了多少个0
{
  int i,flag=0,k=0;
  for(i=0;i<5;i++)
    {
      if(d[i]=='0'&&flag==0)k++;
      if(d[i]!='0')flag=1;
    }
  return k;
}

void read_d()                       //读取将要排序的数据
{
  int i=0,j;
  FILE *fp;char read_name[]="/home/talent/PB14011029-project1/ex2/input/input_numbers.txt";
  fp=fopen(read_name,"rt");
  for(i=0;i<num;i++) 
   {
     fseek(fp,0,SEEK_CUR);
     fgets(data[i],8,fp);
   }
  fclose(fp);
  for(i=0;i<num;i++)
   {
     if((j=strlen(data[i]))<6) 
      { 
        int k=0;
        for(;j<6;j++)  
         {
            data_2[i][k]='0';
            k++;
         }
        strcat(data_2[i],data[i]);
      }
     else strcpy(data_2[i],data[i]);
   }
  printf("Read Done!\n");
}

void write_d(char d[][10])                //将每次排序结果写入result_n.txt中去
{
  FILE *fp;
  int i,ze,j;
  fp=fopen(name_r,"wt+");
  for(i=0;i<num;i++)
   {
     ze=zero_num(d[i]);
     if(ze==0)
      {
        strcpy(data_3[i],data_2[i]);
        data_3[i][strlen(data_3[i])-1]='\n';
      }
     else
      {
        for(j=0;j<5-ze;j++) data_3[i][j]=d[i][j+ze];
        data_3[i][strlen(data_3[i])]='\n';
      }
   }
  for(i=0;i<num;i++)
    {
      fprintf(fp,"%s",data_3[i]);
    }
  fflush(fp);
  fclose(fp);
  printf("Write_d Done!\n");
}

FILE *fp_t;int flag=0;
void write_t(int k)                       //将每次排序时间写入time.txt文件中去
{
  float ti;char time_name[]="/home/talent/PB14011029-project1/ex2/output/radix_sort/time.txt";
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


void counting_sort(char d[][10],int w)          //计数排序
{
   int c[10];
   int i,j;
   static char b[MAX][10];
   for(i=0;i<=9;i++)c[i]=0;
   for(j=0;j<num;j++)c[d[j][w]-'0']=c[d[j][w]-'0']+1;
   for(i=1;i<=9;i++)c[i]=c[i]+c[i-1];
   for(j=num-1;j>=0;j--)
    {
       strcpy(b[c[d[j][w]-'0']-1],d[j]);
       c[d[j][w]-'0']=c[d[j][w]-'0']-1;
    }
   for(j=0;j<num;j++)strcpy(d[j],b[j]);
}

void radix_sort(char d[][10],int di)           //基数排序
{
  int i;
  for(i=di-1;i>=0;i--) counting_sort(d,i);
}

int k,i_main;
int main()                                  //主函数
{
  i_main=0;
  printf("3 的 x 次方\n");
  scanf("%d",&k);
  num=thr(k);
  name(k);
  for(i_main=0;i_main<num;i_main++)
    {
       memset(data[i_main],0,sizeof(data[i_main]));
       memset(data_2[i_main],0,sizeof(data_2[i_main]));
       memset(data_3[i_main],0,sizeof(data_3[i_main]));
    }
  read_d();
  start=clock();
  radix_sort(data_2,5);
  finish=clock();
  write_d(data_2);
  write_t(k);
  printf("规模：3的%d次方   时间： %f seconds\n\n\n",k,(finish - start) / CLOCKS_PER_SEC);
  main();
}
