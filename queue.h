/*************************************************************************
    > File Name: queue.h
    > Created Time: 2016年04月11日 星期一 14时25分17秒
 ************************************************************************/

#include<iostream>
using namespace std;

//任务的状态存储结构体
struct job
{
		int jobnum;        //任务号
		int arrivetime;    //到达时间
		int burst;		   //运行时间
		int retime;		   //响应时间
		int leavetime;	   //离开时间
		int roundtime;     //周转时间 
		int runtime;	   //已运行时间
};
typedef job ElemType;

//队列结构体
struct LNode
{
	ElemType data;
	LNode *next;
};

//队列指针结构体
struct LinkQueue
{
	LNode *front;   //对首指针
	LNode *rear;    //对尾指针
};

//初始化队列
void InitQueue(LinkQueue &HQ)
{
	HQ.front = HQ.rear=NULL;
}

//向队列中插入一个元素
void EnQueue(LinkQueue &HQ , ElemType item)
{
	LNode *newptr = new LNode;
	newptr->data = item;
	newptr->next = NULL;
	if (HQ.rear == NULL)
	{
		HQ.front=HQ.rear=newptr;
	}
	else
	{
		HQ.rear=HQ.rear->next=newptr;
	}
}

//从队列中删除一个元素
ElemType OutQueue(LinkQueue &HQ)
{
	if (HQ.front == NULL)
	{
		cout<<"Queue NULL"<<endl;
		exit(1);
	}
	ElemType temp = HQ.front->data;
	LNode *p = HQ.front;
	HQ.front = p->next;
	if (HQ.front==NULL)
	{
		HQ.rear=NULL;
	}
	delete p;
	return temp;
}

//读取队首元素
ElemType *PeekQueue(LinkQueue &HQ)
{
	if (HQ.front == NULL)
	{
		cout<<"队列为空无首元素。"<<endl;
	}
	return &HQ.front->data;
}

//检查队列是否为空
bool EmptyQueue(LinkQueue &HQ)
{
	return HQ.front == NULL;
}

//清除所有链队中的元素，变为空队列
void ClearQueue(LinkQueue &HQ)
{
	LNode *p = HQ.front;
	while (p != NULL)
	{
		HQ.front = HQ.front->next;
		delete p;
		p = HQ.front;
	}
	HQ.rear=NULL;
}

//实现4个队列的切换使用
void function(LinkQueue *x , int timing)
{
	int leatime[4];
	leatime[0]=0;
	leatime[1]=2;
	leatime[2]=6;
	leatime[3]=14;
	job *t = NULL;
	int i = 1;
	while(i<5)
	{
		if (EmptyQueue(x[i]) == false)
		{
			t = PeekQueue(x[i]);
			t->runtime++;
			if (t->runtime == 1 and timing>=t->arrivetime)
					t->retime = timing-t->arrivetime;
			if (t->runtime == t->burst)
			{
				t->leavetime = timing +1;
				t->roundtime = t->leavetime-t->arrivetime;
				cout<<"任务号："<<t->jobnum<<"响应时间："<<t->retime<<"";
				cout<<"离开时间："<<t->leavetime<<""<<"周转时间："<<t->roundtime;
				cout<<endl;
				OutQueue(x[i]);
			}
			else if (t->runtime == leatime[i] and (i<=3))
			{
				EnQueue(x[i+1],OutQueue(x[i]));
			}
			break;
		}
		i++;
	}
}

//将任务时间设置为0,再将任务进入第一个队列
void create(LinkQueue *x , job job)
{
	job.runtime=0;
	EnQueue(x[1],job);
}
