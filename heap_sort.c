#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX   1594323

long thr(int x)                  //返回3的x次方
{
  long i=1;
  for(;x>0;x--)i=i*3;
  return i;
}

char name_r[100];
void name(int k)                 //生成写入已排序数据的文件名
{
  char path[]="/home/talent/PB14011029-project1/ex1/output/heap_sort/";
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


void read_s(char str[][20])               //读取将要排序的数据
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


void write_s(char str[][20])       //将每次排序结果写入result_n.txt中去
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
void write_t(int k)                  //将每次排序时间写入time.txt文件中去
{
  float ti;
  char time_name[]="/home/talent/PB14011029-project1/ex1/output/heap_sort/time.txt";
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

int compare(char *x,char *y)              //比较两个字符大小
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

long heap_num;

long left(long i)           //返回左子树下标
{
    return(2*i+1);
}

long right(long i)          //返回右子树下标
{
   return(2*i+2);
} 

void max_heapify(char s[][20],long i)             //维持最大堆的性质
{
  long l,r,largest;
  char ch[20];
  l=left(i); r=right(i);
 
  if(l<heap_num&&compare(s[l],s[i])==0) largest=l;
  else largest=i;
  if(r<heap_num&&compare(s[r],s[largest])==0) largest=r;
  if(largest!=i)
    {
      strcpy(ch,s[largest]);
      strcpy(s[largest],s[i]);
      strcpy(s[i],ch);
      max_heapify(s,largest);
    }
}

void build_max_heap(char s[][20])         //建堆
{
  long i;
  for(i=floor((heap_num-1)/2);i>=0;i--)
   {
     max_heapify(s,i);
   }
}

void heap_sort(char s[][20])          //堆排序
{
  build_max_heap(s);
  long i;
  char ch[20];
  for(i=heap_num-1;i>=1;i--)
    {
      
       strcpy(ch,s[i]);
       strcpy(s[i],s[0]);
       strcpy(s[0],ch);
       heap_num--;
       max_heapify(s,0);
    }
}

int k;
void main()                       //主函数
{
  printf("3 的 x 次方\n");
  scanf("%d",&k);
  num=thr(k);
  name(k);
  heap_num=num;
  read_s(str);
  start=clock();
  heap_sort(str);
  finish=clock();
  write_s(str);
  write_t(k);
  printf("规模：3的%d次方   时间： %f seconds\n\n\n",k,(finish - start) / CLOCKS_PER_SEC);
  main();
}
