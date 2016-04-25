/*************************************************************************
    > File Name: main.cpp
    > Created Time: 2016年04月11日 星期一 14时55分36秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"cpu.h"
using namespace std;

int main()
{
	LinkQueue *x;
	int n,i;
	int timing = 0;
	job *jobing;
	x = (LinkQueue*)malloc(sizeof(LinkQueue)*5);
	for(i=1;i<=4;i++)
			InitQueue(x[i]);
	cout<<"请输入任务个数："<<endl;
	cin>>n;
	if (n==0)
	{
		cout<<"没有任务。请重新输入："<<endl;
		cin>>n;
	}
	jobing = new job[n];
	cout<<"请输入各个任务信息："<<endl;
	cout<<"任务号     到达时间    运行时间"<<endl;
	for(i=0; i<n;i++)
	{
		cin>>jobing[i].jobnum>>jobing[i].arrivetime>>jobing[i].burst;
	}
	i=0;
	while (i!=n or !(EmptyQueue(x[1]) and EmptyQueue(x[2]) and EmptyQueue(x[3]) and EmptyQueue(x[4])))
	{
		while (timing == jobing[i].arrivetime)
		{
			create(x,jobing[i]);
			i++;
		}
		function(x,timing);
		timing++;
	}
	for (i=1;i<=4;i++)
	{
		ClearQueue(x[i]);
	}
}
