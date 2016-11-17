#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include <time.h>
#define red  0
#define black 1
#define MAX   100


int number[MAX];
int number_in[MAX];
double start[9],finish[9],start_delete[3],finish_delete[3];
int prorder_flag[4],inorder_flag[4],postorder_flag[4];
int del_inorder_flag[4];
typedef struct RBNode
{
  int data;
  int color;
  int size;
  struct RBNode *parent,*left,*right;
}RBNode,*RBTree;
RBTree nil=NULL;

RBTree OS_SELECT(RBTree &T,int i);

//随机产生80个数据
void random_num(int d[])         
{
   int i,temp;
   int check[151];
   for(i=0;i<151;i++) check[i]=0;
   srand((unsigned)time(NULL));
   for(i=0;i<80;i++)
    {
       temp=1+rand()%150;
       if(check[temp]==0) 
        { 
          d[i]=temp;
          check[temp]=1;
        }
       else                i--;
    }  
  FILE *fp;
  fp=fopen("/home/talent/project2/ex/input/input.txt","wb+");
  for(i=0;i<80;i++) fprintf(fp,"%d\n",d[i]);
  fclose(fp);
}

//读取前k个数据
void read_data(int d[],int k)
{
  FILE *fp;
  fp=fopen("/home/talent/project2/ex/input/input.txt","rb");
  int i;
  for(i=0;i<k;i++) fscanf(fp,"%d",&d[i]);
  fclose(fp);
  printf("Read done!\n");
}


//输出构建好的红黑树的前序遍历序列
FILE *fp_pr;
void prorder_write_data(RBTree &T,int k)
{
  if(k==20&&prorder_flag[0]==0)   { fp_pr=fopen("/home/talent/project2/ex/output/size20/prorder.txt","wb+"); prorder_flag[0]=1;}
  else if(k==40&&prorder_flag[1]==0)  {  fp_pr=fopen("/home/talent/project2/ex/output/size40/prorder.txt","wb+"); prorder_flag[1]=1;}
  else if(k==60&&prorder_flag[2]==0)  {  fp_pr=fopen("/home/talent/project2/ex/output/size60/prorder.txt","wb+"); prorder_flag[2]=1;}
  else if(k==80&&prorder_flag[3]==0)  {  fp_pr=fopen("/home/talent/project2/ex/output/size80/prorder.txt","wb+"); prorder_flag[3]=1;}
  
  fseek(fp_pr,0,SEEK_END); 
  if(T!=nil)
   {
      if(T->color==0)fprintf(fp_pr,"%d  red  size: %d \n",T->data,T->size);
      else           fprintf(fp_pr,"%d  black  size: %d \n",T->data,T->size);
      prorder_write_data(T->left,k);
      prorder_write_data(T->right,k);
   }
}


//输出构建好的红黑树的中序遍历序列
FILE *fp_in;
void inorder_write_data(RBTree &T,int k)
{
  
  if(k==20&&inorder_flag[0]==0)  {  fp_in=fopen("/home/talent/project2/ex/output/size20/inorder.txt","wb+");  inorder_flag[0]=1;}
  else if(k==40&&inorder_flag[1]==0)  {  fp_in=fopen("/home/talent/project2/ex/output/size40/inorder.txt","wb+"); inorder_flag[1]=1;}
  else if(k==60&&inorder_flag[2]==0)  {  fp_in=fopen("/home/talent/project2/ex/output/size60/inorder.txt","wb+"); inorder_flag[2]=1;}
  else if(k==80&&inorder_flag[3]==0)  {  fp_in=fopen("/home/talent/project2/ex/output/size80/inorder.txt","wb+"); inorder_flag[3]=1;}
  
  fseek(fp_in,0,SEEK_END); 
  if(T!=nil)
    {
       inorder_write_data(T->left,k);
       if(T->color==0)fprintf(fp_in,"%d  red  size: %d \n",T->data,T->size);
       else           fprintf(fp_in,"%d  black  size: %d \n",T->data,T->size);
       inorder_write_data(T->right,k);
    }
}


//输出构建好的红黑树的后序遍历序列
FILE *fp_po;
void postorder_write_data(RBTree &T,int k)
{
  
  if(k==20&&postorder_flag[0]==0)   { fp_po=fopen("/home/talent/project2/ex/output/size20/postorder.txt","wb+"); postorder_flag[0]=1;}
  else if(k==40&&postorder_flag[1]==0)  { fp_po=fopen("/home/talent/project2/ex/output/size40/postorder.txt","wb+"); postorder_flag[1]=1;}
  else if(k==60&&postorder_flag[2]==0)  { fp_po=fopen("/home/talent/project2/ex/output/size60/postorder.txt","wb+"); postorder_flag[2]=1;}
  else if(k==80&&postorder_flag[3]==0)  { fp_po=fopen("/home/talent/project2/ex/output/size80/postorder.txt","wb+"); postorder_flag[3]=1;}
  
  fseek(fp_po,0,SEEK_END); 
  if(T!=nil)
    {
       postorder_write_data(T->left,k);
       postorder_write_data(T->right,k);
       if(T->color==0)fprintf(fp_po,"%d  red  size: %d \n",T->data,T->size);
       else           fprintf(fp_po,"%d  black  size: %d \n",T->data,T->size);
    }
}



//输出插入运行时间效率的数据
void write_time1(double s[],double f[],int k)
{
  FILE *fp;int i;
  if(k==20) fp=fopen("/home/talent/project2/ex/output/size20/time1.txt","wb+"); 
  else if(k==40)   fp=fopen("/home/talent/project2/ex/output/size40/time1.txt","wb+"); 
  else if(k==60)   fp=fopen("/home/talent/project2/ex/output/size60/time1.txt","wb+"); 
  else if(k==80)   fp=fopen("/home/talent/project2/ex/output/size80/time1.txt","wb+");
  
  else printf("'k' error in postorder_write_data\n");
  fseek(fp,0,SEEK_END); 
  for(i=1;i<=(k/10);i++)
    {
      fprintf(fp,"%d : %f seconds\n",i*10,(finish[i]- start[i]) / CLOCKS_PER_SEC);
    }
  fprintf(fp,"Total: %f seconds\n",(finish[0]- start[0]) / CLOCKS_PER_SEC);
  fclose(fp);
}



//调用以上输出函数
void write_data(RBTree &T,int k)
{
  prorder_write_data(T,k);
  fclose(fp_pr);
  printf("prorder_write_data done!\n");

  inorder_write_data(T,k);
  fclose(fp_in);
  printf("Inorder_write_data done!\n");

  postorder_write_data(T,k);
  fclose(fp_po);
  printf("Postorder_write_data done!\n");

  write_time1(start,finish,k);
  printf("Write time1 done!\n");

  printf("Write all done!\n");
}


//输出删除的数据
void write_delete_data(RBTree &T,int k)
{
   FILE *fp; RBNode *x;
   if(k==20) fp=fopen("/home/talent/project2/ex/output/size20/delete_data.txt","wb+"); 
   else if(k==40)   fp=fopen("/home/talent/project2/ex/output/size40/delete_data.txt","wb+"); 
   else if(k==60)   fp=fopen("/home/talent/project2/ex/output/size60/delete_data.txt","wb+"); 
   else if(k==80)   fp=fopen("/home/talent/project2/ex/output/size80/delete_data.txt","wb+");
   
   x=OS_SELECT(T,k/4);
   if(x->color==red) fprintf(fp,"1: %d  red  size: %d\n",x->data,x->size);
   else              fprintf(fp,"1: %d  black  size: %d\n",x->data,x->size);
   x=OS_SELECT(T,(k-1)/2);
   if(x->color==red) fprintf(fp,"2: %d  red  size: %d\n",x->data,x->size);
   else              fprintf(fp,"2: %d  black  size: %d\n",x->data,x->size);
   fclose(fp);
}


//输出删除结点所花费的时间
void write_time2(double s[],double f[],int k)
{
  FILE *fp;
  if(k==20) fp=fopen("/home/talent/project2/ex/output/size20/time2.txt","wb+"); 
  else if(k==40)   fp=fopen("/home/talent/project2/ex/output/size40/time2.txt","wb+"); 
  else if(k==60)   fp=fopen("/home/talent/project2/ex/output/size60/time2.txt","wb+"); 
  else if(k==80)   fp=fopen("/home/talent/project2/ex/output/size80/time2.txt","wb+");
  
  else printf("'k' error in postorder_write_data\n");
  fseek(fp,0,SEEK_END);
  fprintf(fp,"1: %f seconds\n",(finish_delete[1]-start_delete[1])/CLOCKS_PER_SEC);
  fprintf(fp,"2: %f seconds\n",(finish_delete[2]-start_delete[2])/CLOCKS_PER_SEC);
  fprintf(fp,"Total: %f seconds\n",(finish_delete[0]-start_delete[0])/CLOCKS_PER_SEC);
  fclose(fp);
}




//输出删除后的红黑树的中序遍历子序列
FILE *fp_del_in;
void delete_data_inorder(RBTree &T,int k)
{
  if(k==20&&del_inorder_flag[0]==0)  
     {  
fp_del_in=fopen("/home/talent/project2/ex/output/size20/delete_data_inorder.txt","wb+");               del_inorder_flag[0]=1;
     }

  else if(k==40&&del_inorder_flag[1]==0)  
     {  
fp_del_in=fopen("/home/talent/project2/ex/output/size40/delete_data_inorder.txt","wb+"); 
del_inorder_flag[1]=1;
     }

  else if(k==60&&del_inorder_flag[2]==0)  
     {  
fp_del_in=fopen("/home/talent/project2/ex/output/size60/delete_data_inorder.txt","wb+"); 
del_inorder_flag[2]=1;
     }

  else if(k==80&&del_inorder_flag[3]==0)  
     {  
fp_del_in=fopen("/home/talent/project2/ex/output/size80/delete_data_inorder.txt","wb+"); 
del_inorder_flag[3]=1;
     }

  fseek(fp_del_in,0,SEEK_END); 
  if(T!=nil)
    {
       delete_data_inorder(T->left,k);
       if(T->color==0)fprintf(fp_del_in,"%d  red  size: %d \n",T->data,T->size);
       else           fprintf(fp_del_in,"%d  black  size: %d \n",T->data,T->size);
       inorder_write_data(T->right,k);
    }
}



//输出红黑树T到屏幕
void pritree(RBTree &T)
{
  RBNode *x=T;
  if(x!=nil)
    {
      printf("%d  ",x->data);
      if(x->color==red) printf("red   ");
      else             printf("black   ");
      printf(" size: %d    ",x->size);
      if(x->left!=nil)
       {
         printf("left:%d %d   ",x->left->data,x->left->color);
       }
      else printf("No left    ");
      if(x->right!=nil)
       {
         printf("right:%d %d\n",x->right->data,x->right->color);
       }
      else printf("No right\n");
      pritree(x->left);
      pritree(x->right);
    }
}




//对结点x作左旋操作
void LeftRotate(RBTree &T,RBNode *x)
{ 
   RBNode *y=x->right;
   x->right=y->left;
   if(y->left!=nil)  y->left->parent=x;
   y->parent=x->parent;
   if(x->parent==nil) T=y;
   else if(x==x->parent->left) x->parent->left=y;
   else  x->parent->right=y;
   y->left=x;
   x->parent=y;
}

//对结点y作右旋操作
void RightRotate(RBTree &T,RBNode *y)
{
  RBNode *x=y->left;
  y->left=x->right;
  if(x->right!=nil) x->right->parent=y;
  x->parent=y->parent;
  if(y->parent==nil)  T=x;
  else if(y==y->parent->right) y->parent->right=x;
  else                       y->parent->left=x;
  x->right=y;
  y->parent=x;
}


//插入结点后作调整
void RB_INSERT_FIXUP(RBTree &T,RBNode *z)
{
  while(z->parent->color==red)
   {
      RBNode *y;
      if(z->parent==z->parent->parent->left)
        {
          y=z->parent->parent->right;
          if(y->color==red)
           {
              z->parent->color=black;
              y->color=black;
              z->parent->parent->color=red;
              z=z->parent->parent;
              continue;
           }
          else if(z==z->parent->right)
            {
               z=z->parent;
               LeftRotate(T,z);
               continue;
            }
          z->parent->color=black;
          z->parent->parent->color=red;
          RightRotate(T,z->parent->parent);
        }
      else
        {
           y=z->parent->parent->left;
          if(y->color==red)
           {
              z->parent->color=black;
              y->color=black;
              z->parent->parent->color=red;
              z=z->parent->parent;
              continue;
           }
          else if(z==z->parent->left)
            {
               z=z->parent;
               RightRotate(T,z);
              continue;
            }
          z->parent->color=black;
          z->parent->parent->color=red;
          LeftRotate(T,z->parent->parent);
        }
   }
  T->color=black;
}


//插入结点z
void RB_INSERT(RBTree &T,RBNode *z)
{
  RBNode *y=nil;
  RBNode *x=T;
  while(x!=nil)
    {
      y=x;
      if(z->data<x->data) x=x->left;
      else              x=x->right;
    }
  z->parent=y;
  if(y==nil)  T=z;
  else if(z->data<y->data)  y->left=z;
  else        y->right=z;
  z->left=nil;
  z->right=nil;
  z->color=red;
  RB_INSERT_FIXUP(T,z);
}

//将数组d中的数据依次插入到红黑树T
void newtree(RBTree &T,int d[],int k)
{
  int i;
  nil=(RBNode*)malloc(sizeof(RBNode));
  nil->color=black;
  nil->data=0;
  nil->size=0;
  nil->parent=NULL;
  nil->left=NULL;
  nil->right=NULL;
  T=nil;
  for(i=0;i<k;i++)
   {  
      RBNode *z=(RBNode*)malloc(sizeof(RBNode));
      z->data=d[i];
      z->color=red;
      z->size=0;
      z->parent=NULL;
      z->left=NULL;
      z->right=NULL;
      if((i+10)%10==0) start[(i+10)/10]=clock();
      RB_INSERT(T,z);
      if((i+1)%10==0) finish[(i+1)/10]=clock();
   }
 for(i=1;i<=k/10;i++)
   {
      start[0]=start[0]+start[i];
      finish[0]=finish[0]+finish[i];
   }
 
}

//计算红黑树T中结点的属性size
int Size(RBTree &T)
{
  if(T!=nil) T->size=Size(T->left)+Size(T->right)+1;
  return (T->size);
}

//选择红黑树中第i小的结点
RBTree OS_SELECT(RBTree &T,int i)
{
  int r;
  r=T->left->size+1;
  if(i==r) return T;
  else if(i<r) return OS_SELECT(T->left,i);
  else     return OS_SELECT(T->right,i-r);
}

//返回最小结点
RBTree TREE_MINIMUM(RBTree &T)
{
  RBNode *x;
  x=T;
  while(x->left!=nil) x=x->left;
  return x;
}

//将结点v移接到u的位置
void RB_TRANSPLANT(RBTree &T,RBNode *u,RBNode *v)
{
  if(u->parent==nil) T=v;
  else if(u==u->parent->left) u->parent->left=v;
  else u->parent->right=v;
  v->parent=u->parent;
}


//删除结点后作调整
void RB_DELETE_FIXUP(RBTree &T,RBNode *x)
{
  RBNode *w;
  while(x!=T&&x->color==black)
    {
       if(x==x->parent->left)
         {
            w=x->parent->right;
            if(w->color==red)
              {
                 w->color=black;
                 x->parent->color=red;
                 LeftRotate(T,x->parent);
                 w=x->parent->right;
              }
            if(w->left->color==black&&w->right->color==black)
              {
                 w->color=red;
                 x=x->parent;
              }
            else if(w->right->color==black)
              {
                 w->left->color=black;
                 w->color=red;
                 RightRotate(T,w);
                 w=x->parent->right;
              }
            else
              {
                 w->color=x->parent->color;
                 x->parent->color=black;
                 w->right->color=black;
                 LeftRotate(T,x->parent);
                 x=T;
              }
         }
       else
         {
           w=x->parent->left;
           if(w->color==red)
             {
                w->color=black;
                x->parent->color=red;
                RightRotate(T,x->parent);
                w=x->parent->left;
             }
           if(w->left->color==black&&w->right->color==black)
             {
                w->color=red;
                x=x->parent;
             }
           else if(w->left->color==black)
             {
                w->right->color=black;
                w->color=red;
                LeftRotate(T,w);
                w=x->parent->right;
             }
           else 
             {
                w->color=x->parent->color;
                x->parent->color=black;
                w->left->color=black;
                RightRotate(T,x->parent);
                x=T;
             }
         }
    }
  x->color=black;
}


//删除红黑树T中的结点z
void RB_DELETE(RBTree &T,RBNode *z)
{
  RBNode *y,*x;
  y=z;printf("Deleted %d\n",z->data);
  int y_original_color=y->color;
  if(z->left==nil)
   {
     x=z->right;
     RB_TRANSPLANT(T,z,z->right);
   }
  else if(z->right==nil)
   {
     x=z->left;
     RB_TRANSPLANT(T,z,z->left);
   }
  else 
   {
     y=TREE_MINIMUM(z->right);
     y_original_color=y->color;
     x=y->right;
     if(y->parent==z)  x->parent=y; 
     else 
       {
         RB_TRANSPLANT(T,y,y->right);
         y->right=z->right;
         y->right->parent=y;
       }
     RB_TRANSPLANT(T,z,y);
     y->left=z->left;
     y->left->parent=y;
     y->color=z->color;
     if(y_original_color==black)
        RB_DELETE_FIXUP(T,x);
   }
}

int random_flag=0;
int main()
{
  int k,i,n;
  for(i=0;i<5;i++)
   {
     prorder_flag[i]=0;
     inorder_flag[i]=0;
     postorder_flag[i]=0;
   }
  RBTree RBT=NULL;
  
  //产生数据
  if(random_flag==0) { random_num(number); random_flag=1; }

  //输入k决定数据量
  printf("请输入整数k\n");
  scanf("%d",&k);

  memset(start,0,sizeof(double)*(k+1));
  memset(finish,0,sizeof(double)*(k+1));

  //读取前k个数据
  read_data(number_in,k);

  //插入数据
  newtree(RBT,number_in,k);
  Size(RBT);

  //输出红黑树到相应文件
  write_data(RBT,k);
  printf("k为：%d  时间为：%f\n",k,(finish[0] - start[0]) / CLOCKS_PER_SEC);
  pritree(RBT);printf("\n\n\n");

  //输出将要删除的数据到相应文件
  write_delete_data(RBT,k);

  //删除数据并记录时间
  double start_size,finish_size;
  n=k/4;
     start_delete[0]=clock();
     start_delete[1]=clock();     
   RB_DELETE(RBT,OS_SELECT(RBT,n));
     finish_delete[1]=clock();
  
  start_size=clock();
  Size(RBT);
  finish_size=clock();

  n=(k-1)/2;
     start_delete[2]=clock();
   RB_DELETE(RBT,OS_SELECT(RBT,n));
     finish_delete[2]=clock();
     finish_delete[0]=clock();

  //为计算删除两个结点的总时间去除Size函数的影响
  start_delete[0]=start_delete[0]+finish_size;
  finish_delete[0]=finish_delete[0]+start_size;

  //输出删除结点的时间到相应文件
  write_time2(start_delete,finish_delete,k);

  //计算新树的size，输出删除后的红黑树的中序遍历子序列到相应文件
  Size(RBT);
  delete_data_inorder(RBT,k);
  pritree(RBT);

  main();
}
