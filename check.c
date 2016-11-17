#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int number[MAX];
int number_in[MAX];

void read_data(int d[],int k)
{
  FILE *fp;
  fp=fopen("/home/talent/pr2/input/input.txt","rb");
  int i;
  for(i=0;i<k;i++) fscanf(fp,"%d",&d[i]);
  fclose(fp);
}

int RANDOM(int p,int r)
{
  int i=-1;
  srand((unsigned)time(NULL));
  while(i<p||i>r)i=p+rand()%r;
  return i;
}

int PARTITION(int a[],int p,int r)
{
  int x=a[r];
  int i=p-1;
  int j,temp;
  for(j=p;j<r;j++)
    {
      if(a[j]<x)
        {
          i++;
          temp=a[i];
          a[i]=a[j];
          a[j]=temp;
        }
    }
  temp=a[i+1];
  a[i+1]=a[r];
  a[r]=temp;
  return (i+1);
}

int RANDOMIZED_PARTITION(int a[],int p,int r)
{
  int i=RANDOM(p,r);
  int temp=a[r];
  a[r]=a[i];
  a[i]=temp;
  return PARTITION(a,p,r);
}

int SELECT(int a[],int p,int r,int i)
{
  if(p==r) return a[p];
  int q=RANDOMIZED_PARTITION(a,p,r);
  int k=q-p+1;
  if(i==k) return a[q];
  else if(i<k) return SELECT(a,p,q-1,i);
  else         return SELECT(a,q+1,r,i-k);
}

int main()
{
  int k,p,q,i;
  for(k=20;k<=100;k=k+20)
    { 
       for(i=0;i<k;i++)number[i]=0;
       read_data(number,k);
       p=SELECT(number,0,k-1,k/3);
       q=SELECT(number,0,k-1,2*(k-1)/3+1);
       printf("当n为 %d 时，第一个结点为： %d  第二个结点为： %d\n",k,p,q);
    }
  return 0;
}
