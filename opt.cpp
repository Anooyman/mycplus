/*************************************************************************
    > File Name: opt.cpp
    > Created Time: 2016年04月25日 星期一 15时28分20秒
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
using namespace std;

int Block[10][10];
int EachBlock[100][100];
int AvailCount = 0;
typedef struct Page
{
	int IDnum;
	int BlockSum;
	struct Page *next;
}Page;
Page *page=NULL;

void init()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			Block[i][j]=(int)rand()%2;
			if(Block[i][j] == 0)
							AvailCount++;
		}
	}
	for(i=0;i<100;i++)
					for(j=0;j<100;j++)
									EachBlock[i][j] = 0;
}

void Create()
{
	int num,blockcount;
	Page *p,*q;
	p=page;
	cout<<"输入进程号："<<endl;
	cin>>num;
	while(p != NULL)
	{
		if(p->IDnum != num)	
						p=p->next;
		else
		{
			cout<<"该进程已存在并分配了物理块，重新输入："<<endl;	
			cin>>num;
			p=page;
		}
	}
	cout<<"输入该进程所需要的物理块的数目："<<endl;
	cin>>blockcount;
	if(blockcount>AvailCount)
					cout<<"内存物理快不足，不能完成分配！"<<endl;
	else 
	{
		q=new Page;
		q->IDnum = num;
		q->BlockSum=blockcount;
		q->next=NULL;
	}
}











