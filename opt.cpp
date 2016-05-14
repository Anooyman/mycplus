#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int A[100];		    //内存物理块，0：未使用，非0：已使用
int max = 99;	    //记录内存的物理块数,值为A[100]最大下标
int count = 100;	//记录内存未使用物理块数
typedef struct LNode{
	int  f;         //进程号
	char name[8];	//进程名	
	int size;       //进程大小
	int n;		    //进程页数
	int ye[100];	//页表,下标表示页号，内容表示进程各页所在物理块
	struct LNode *next;
}LNode,*LinkList;
//内存初始化
void CreatA()
{
	int i = 0;	
	for(i = 0;i <= max; i++)
		A[i] = 0;
}

//建立新进程
void NewNode(LinkList &L)
{
	int i,j;
	int m,k;
	LinkList p;
 LinkList new_node;
	new_node= (LinkList)malloc(sizeof(LNode));	
	p = L;	
	printf("\n输入进程号:");
	scanf("%d",&new_node->f);
	j=0;
    while(p != NULL&&j<3) //查找进程号是否重复
    {
		
		if(p->f!=new_node->f)
			p = p->next;
		else
		{
			printf("\n该进程已存在,重新输入:");
			scanf("%d",&new_node->f); 
			p = L;//p重新指向头结点
			j++;
		}
    }
	if(j<3)
	{printf("\n输入进程名称:");
	scanf("%s",new_node->name);
	printf("\n输入进程的大小:");
	scanf("%d",&new_node->size);
	new_node->n=new_node->size/1024;
	k=new_node->size%1024;
	if(k!=0)
		new_node->n=new_node->n+1;
	printf("所需要的页数为:");
	printf("%d\n",new_node->n);
	if(new_node->n> count)
	{
		printf("\n内存物理块不足，新建进程失败!!!\n\n");
		
	}
	else
	{
		count -=new_node->n;
		m = 0;		
		for(i= 0; i<= max; i++)
			if(A[i] == 0 && m < new_node->n)
			{
			    A[i]=new_node->f;
				new_node->ye[m] = i;
				m++;
			}
			if(L == NULL)
				L = new_node;
			else
			{	
				p = L;
				//查找最后一个节点
				while(p->next != NULL)
				{
					p = p->next;
				}
				p->next = new_node;
			}
new_node->next = NULL;			
	}
	}
	else 
	{
		printf("\n错误次数过多,返回主菜单:");
	}
}
//回收进程，释放内存
void FreeNode(LinkList &L)
{
	LinkList p,q;
	int z;
	printf("请输入要删除的进程号:");
	scanf("%d",&z);	
	p = L;//查找进程；用p记录
	q = p;
	while(p != NULL)
	{
		if(p->f==z)
		{
			printf("该进程已删除");
			break;
		}
		else
		{
			q = p;
			p = p->next;	
		}
	}
	if(p == NULL)
	{
		printf("\n该进程不存在!!!\n");
	}
	else
	{		
		for(int i = 0; i < p->n; i++)	
			A[p->ye[i]] = 0;
		
		count += p->n;
		
		if(p->f== q->f)//要删除的是头结点
		{
			L = p->next;
		}
		else
		{
			q->next = p->next;
		}
	}
}

//显示所有进程占用的物理块

void Printf(LinkList L)
{
	int i = 0;
	
	printf("\n内存物理块分配情况:\n");
	
	LinkList p = L;
	printf("\n各进程信息:\n");
	printf("进程号\t\t进程名称\t进程页数\t所用物理块\n");
	
	while(p != NULL)
	{
		
		printf("%d\t\t",p->f);
		printf("%s\t\t",p->name);
		printf("%d\t\t",p->n);
		int i;
		for(i = 0;i < p->n; i++)
			printf("%d,",p->ye[i]);
		printf("\n");
		p = p->next;
	}
}
// 查看进程
void look(LinkList L)
{
	int z;
	printf("输入要查询的进程号");
	scanf("%d",&z);
	LinkList p = L;
	while (p!=NULL)
	{
		if(p->f ==z)
		{
			printf("进程号\t\t进程名称\t进程页数\t所用物理块\n");
			printf("%d\t\t",p->f);
		    printf("%s\t\t",p->name);
		    printf("%d\t\t",p->n);
		    int i;
		    for(i = 0;i < p->n; i++)
			    printf("%d,",p->ye[i]);
		    printf("\n");
			break;
		}
		else p=p->next; 
	}
	if(p==NULL)
		printf("要查询的进程不存在\n");
}
//显示内存块使用情况，不分进程
void showit()
{
	int i = 0;
	printf("\n****************************\n");
	printf("|    内存物理块分配情况    |\n");
	printf("****************************\n");
	for(i = 0; i <= max; i++)
	{		
		printf("%d\t",A[i]);
		if(i%10 == 9)
			printf("\n");
	}
}

int main()
{
	CreatA();
	printf("\n******* 基本分页算法 *******\n");
    LinkList L = NULL;
	int i = 0;
    do
    {		
		printf("\n***********菜单*************\n");
		printf(  "     1  进程装入\n");
		printf(  "     2  进程退出\n");
		printf(  "     3  内存使用情况\n");
		printf(  "     4  进程查看\n");		
		printf(  "     5  退出程序\n");
		printf(  "****************************\n");
		printf("请输入你的选择(select):");
		scanf("%d",&i);		
		switch(i){
		case 1:			
				NewNode(L);//建立新的进程				
			    Printf(L);//输出内存物理块分配情况和各进程概况
				break;			
		case 2:			
				FreeNode(L);	//删除某进程
			    Printf(L);	//输出内存物理块分配情况和各进程概况
				break;			
		case 3:			
				showit();//显示当前内存的使用情况
				break;
		case 4:
			look(L);
			break;
		case 5:
			printf("谢谢使用\n\n");
				exit(0);
			break;
		}
    }while(i != 0);
}
