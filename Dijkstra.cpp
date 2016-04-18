/*************************************************************************
    > File Name: Dijkstra.cpp
    > Created Time: 2016年04月18日 星期一 14时06分12秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define MAXPROCESS 50
#define MAXRESOURCE 100
int AVAILABLE[MAXRESOURCE];
int MAX[MAXPROCESS][MAXRESOURCE];
int ALLOCATION[MAXPROCESS][MAXRESOURCE];
int NEED[MAXPROCESS][MAXRESOURCE];
int REQUEST[MAXPROCESS][MAXRESOURCE];
bool FINISH[MAXPROCESS];
int p[MAXPROCESS];
int m,n;

void Init()
{
	int i,j;
	cout<<"请输入进程的数目：";
	cin>>m;
	cout<<"请输入资源的种类：";
	cin>>n;
	cout<<"请输入每个进程最多所需的各资源数，按照"<<m<<"x"<<n<<"矩阵输入"<<endl;
	for (i=0;i<m;i++)
		for (j=0;j<n;j++)
			cin>>MAX[i][j];
	cout<<"请输入每个进程已分配的各资源数，也按照"<<m<<"x"<<n<<"矩阵输入"<<endl;
	for (i=0;i<m;i++)
	{
		for (j=0;j<n;j++)
		{
			cin>>ALLOCATION[i][j];
			NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
			if (NEED[i][j] < 0)
			{
				cout<<"您输入的第"<<i+1<<"个进程所拥有的第"<<j+1<<"个资源数错误，请重新输入："<<endl;
				j--;
				continue;
			}
		}
	}
	cout<<"请输入各个资源现有的数目："<<endl;
	for(i=0;i<n;i++)
		cin >> AVAILABLE[i];
}

void showdata(int n , int m)
{
	int i,j;
	cout<<endl;
	cout<<"-------------------"<<endl;
	cout<<"系统可用的资源数为：";
	for (j=0;j<n;j++)
		cout<<" "<<AVAILABLE[j];
	cout<<endl;
	cout<<"各个进程还需要的资源量"<<endl;
	for(i=0;i<m;i++)
	{
		cout<<" 进程"<<i<<":";
		for (j=0;j<n;j++)
		{
			cout<<"  "<<NEED[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"各个进程已经得到的资源量：  "<<endl<<endl;
	for(i=0;i<m;i++)
	{
		cout<<" 进程"<<i<<":";
		for(j=0;j<n;j++)
			cout<<"   "<<ALLOCATION[i][j];
		cout<<endl;
	}
}

bool Safe()
{
	int i,j,k,l=0;
	int Work[MAXRESOURCE];
	for(i=0;i<n;i++)
			Work[i]=AVAILABLE[i];
	for(i=0;i<m;i++)
			FINISH[i] = false;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(NEED[i][j] > Work[j])
					break;
		}
		if(j==n)
		{
			FINISH[i]=true;
			for(k=0;k<n;k++)
				Work[k]+=ALLOCATION[i][k];
			p[l++]=i;
		}
		else
		{
			continue;
		}
		if(l==m)
		{
			cout<<"系统是安全的"<<endl;
			cout<<"安全序列："<<endl;
			for(i=0;i<l;i++)
			{
				cout<<p[i];
				if(i!=(l-1))
					cout<<"-->";
			}
			cout<<""<<endl;
			return true;
		}
	}
	cout<<"系统是不安全的"<<endl;
	return false;
}

void Bank()
{
	int i,cusneed,flag=0;
	char again;
	while(1)
	{
		showdata(n,m);
		cout<<endl;
input:
		cout<<"请输入申请资源的进程号（注：第1个进程号为0,依次类推）"<<endl;
		cin>>cusneed;
		if(cusneed > m)
		{
			cout<<"没有该进程，请重新输入"<<endl;
			goto input;
		}
		cout<<"请输入进程所请求的各资源的数量"<<endl;
		for(i=0;i<n;i++)
				cin>>REQUEST[cusneed][i];
		for(i=0;i<n;i++)
		{
			if(REQUEST[cusneed][i] > NEED[cusneed][i])
			{
				cout<<"您输入的请求数超过进程需求量！请重新输入！"<<endl;	
				goto input;
			}
			if(REQUEST[cusneed][i] > AVAILABLE[i])
			{
				cout<<"您输入的请求数量超过系统有的资源数！请重新输入！"<<endl;
				goto input;
			}
		}
		for(i=0;i<n;i++)
		{
			AVAILABLE[i]-=REQUEST[cusneed][i];
			ALLOCATION[cusneed][i]+=REQUEST[cusneed][i];
			NEED[cusneed][i]-=REQUEST[cusneed][i];
		}
		if(Safe())
			cout<<"同意分配请求！"<<endl;
		else
		{
			cout<<"您的请求被拒绝！"<<endl;
			for(i=0;i<n;i++)
			{
				AVAILABLE[i]+=REQUEST[cusneed][i];
				ALLOCATION[cusneed][i]-=REQUEST[cusneed][i];
				NEED[cusneed][i]+=REQUEST[cusneed][i];
			}
		}
		for(i=0;i<n;i++)
		{
			if(NEED[cusneed][i] <= 0)
					flag++;
		}
		if(flag == n)
		{
			for(i=0;i<n;i++)
			{
				AVAILABLE[i]+=ALLOCATION[cusneed][i];
				ALLOCATION[cusneed][i] = 0;
				NEED[cusneed][i] = 0;
			}
			cout<<"线程"<<cusneed<<"占有的资源被释放！"<<endl;
			flag =0;
		}
		for(i=0;i<m;i++)
			FINISH[i]=false;
		cout<<"您还想再次请求分配吗？是请按y/Y，否请按其它键"<<endl;
		cin>>again;
		if(again == 'Y' or again == 'y')
				continue;
		break;
	}
}

int main()
{
	Init();
	Safe();
	Bank();
}
