#include<stdlib.h>
#include<stdio.h>
#define n 64
#define m 4
int p[m];
int head=0;

struct
{
short int lnumber;
short int flag;
short int pnumber;
short int write;
short int dnumber;
short int times;
}page[n];

void computer()
{
    int i;
    for(i=0;i<n;i++)
 {
        page[i].lnumber = i;
        page[i].flag = 0;
        page[i].pnumber = 10000;
        page[i].write = 0;
        page[i].dnumber = i;
        page[i].times = 0;
 }

    for(i=0;i<m;i++)
 {
        page[i].pnumber = i;
 }

    for(i=0;i<m;i++)
 {
        p[i] = i;
        page[i].flag = 1;
 }
}
void showpagelist()
{
    int i;
    printf("\n页号\t是否在主存中\t块号\t是否被修改过\t磁盘块号\t访问次数\n");
    for(i=0;i<n;i++)
 {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",page[i].lnumber,page[i].flag,page[i].pnumber,page[i].write,page[i].dnumber,page[i].times);
 }
}
void showpage()
{
    int i;
    for(i=0;i<m;i++)
 {
        printf("\t%d\n",p[i]);
 }
}
void transformation() 
{
    unsigned logicAddress,logicNumber,innerAddress,physicsAddress,physicsNumber;
    int i, fail = 0;
    int method,temppage=0;
    short int times = 10000;
    printf("请输入一个逻辑地址（四位十六进制数）:");
    scanf("%x",&logicAddress);
    logicNumber = logicAddress >> 10;
    printf("页号为:%d\n",logicNumber);
    innerAddress = logicAddress & 0x03ff;
    printf("页内地址为:%d\n",innerAddress);
    for(i=0;i<n;i++)
 {
        if(logicNumber==(unsigned)page[i].lnumber)
  {
            if(page[i].flag == 1)
   {
                printf("请求的页面在主存中!\n");
                page[i].times++;
                physicsNumber = page[i].pnumber;
                printf("请求的主存块号为:%d\n",physicsNumber);
                physicsAddress = physicsNumber << 10 |innerAddress;
                printf("请求的物理地址为:%d",physicsAddress);
                break;
   }
            else
   {
               printf("请求的页面不在主存中！将进行缺页中断处理!\n请选择算法!\n");
               printf("1.先进先出\n2.最近最少用\n请选择置换算法:");
               scanf("%d",&method);
               if(method == 1) 
      {
                   printf("采用先进先出算法!\n");
                   fail = p[head];
                   printf("第%d页将被替换!\n",fail);
                   p[head] = logicNumber;
                   head = (head+1) % m;
                   if(page[fail].write == 1)
                       printf("第%d页曾被修改过!\n",fail);
                       page[fail].flag = 0;
                       page[logicNumber].flag = 1;
                       page[logicNumber].write = 0;
                       page[logicNumber].pnumber = page[fail].pnumber;
                       page[fail].pnumber = 10000;
                       page[logicNumber].times++;
                   break;
      }
    else if(method == 2) 
 {
        printf("采用最近最少用算法!\n");
        for(i=0;i<n;i++)
  {
            if(page[i].flag == 1)
   {
                if(page[i].times<times)
    {
                    times = page[i].times;
                    temppage = page[i].lnumber;
    }
   }
  }
        printf("第%d页将被替换!\n",temppage);
        for(i=0;i<m;i++)
  {
            if(p[i] == temppage)
   {
                p[i] = logicNumber;
   }
  }
        if(page[temppage].write == 1)
            printf("第%d页曾被修改过!\n",temppage);
            page[temppage].flag = 0;
            page[logicNumber].flag = 1;
            page[logicNumber].write = 0;
            page[logicNumber].pnumber = page[temppage].pnumber;
            page[temppage].pnumber = 10000;
            page[logicNumber].times++;
        break;
 }
    else
 {
  printf("你输入有误，即将退出!");
        exit(1);
 }
   }
  }
 }
}
int  main()
{
 char c,d,flag='y';
 printf("页表正在初始化中......，3秒后为你显示页和页表¡\n");
 computer();
 showpage();
 showpagelist();
 while(flag == 'y' || flag == 'Y')
 {
  transformation();
  printf("是否显示页和页表(Y/N)");
  c = getchar();
  c = getchar();
  if(c=='Y'||c=='y')
  {
   showpage();
   showpagelist();
  }
  else
  {
   while(c=='N'||c=='n')
   {
    printf("\n是否继续进行请求分页？（Y/N）");
    d = getchar();
    d = getchar();
    if(d=='Y'||d=='y')
    {
     transformation();
     printf("\n是否显示页和页表？（Y/N）");
     c = getchar();
     c = getchar();
     if(c=='Y'||c=='y')
     {
        showpage();
        showpagelist();
     }
    }
    else if (d=='N'||d=='n')
     exit(1);
    else
     printf("输入错误¡\n");
   }
  }
  printf("\n是否继续进行请求分页？（Y/N）");
  flag = getchar();
  flag = getchar();

 }
}
