#include<iostream>
#include<string>
#include<fstream>
#define UINT_MAX 10000
using namespace std;
typedef struct BiTNode{
    char date;
    double  weight;
    int parent,lchild,rchild;
}BiTNode,*BiTree;
int Choosemin(BiTree t,int i)
{
    int j,n;
    double k=UINT_MAX;
    for(j=1;j<=i;j++)
	{
		if(t[j].weight<k&&t[j].parent==0)
			k=t[j].weight,n=j;
	}
    t[n].parent=-1;
    return n;
}
void select(BiTree t,int i,int &s1,int &s2)
{
	s1=Choosemin(t,i);
	s2=Choosemin(t,i);
}
void HuffmanCreate(BiTree &HT,double *w,int n)
{
    int m,i,s1,s2;
	BiTree p;
	if(n<=1)
		return;
	m=2*n-1;
	HT=new BiTNode[m+1];
	for(p=HT+1,i=1;i<=n;++i,++p,++w)
	{
		(*p).weight=*w;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
		(*p).date='\0';
	}
	for(;i<=m;++i,++p)
		(*p).parent=0;
	for(i=n+1;i<=m;++i)
	{
		select(HT,i-1,s1,s2);
		HT[s1].parent=HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
}
void HuffmanCode(BiTree &HT,char HC[][100],double *w,int n)
{
	int m,i,s1,s2,start;
    int c,f;
	char *cd;
    cd=new char[n];
	cd[n-1]='\0';
	for(i=1;i<=n;i++)
	{
		start=n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
				for(int j=0;j<n;j++)
				{
				   HC[i][j]=cd[start];
				   start++;
				}
	}
	delete cd;
}
int  main()
{
		BiTree HT;
		int n,i;
		double *w;
		cout<<"请输入参加编码的字符数："<<endl;
		cin>>n;
		w=new double[n];
		char HC[100][100];
		cout<<"请依次输入"<<n<<"个权值："<<endl;
		for(i=0;i<=n-1;i++)cin>>w[i];
		HuffmanCreate(HT,w,n);
		HuffmanCode(HT,HC,w,n);
		cout<<"请输入字符："<<endl;
		for(i=1;i<=n;i++)
		{
		   char e;
		   cin>>e;
		   HT[i].date=e;
		}
		for(i=1;i<=n;i++)cout<<HT[i].date<<"的哈夫曼编码为："<<HC[i]<<endl;
		ofstream outputfile;
		outputfile.open("a.txt",ios::out);
		for(i=1;i<=n;i++)
		{
		   outputfile<<HT[i].date<<"：";
		   int j=0;
		   while(1)
		   {
                outputfile<<HC[i][j];
                j++;
                if(HC[i][j]=='\0')break;
		   }
		   outputfile<<endl;
		}
		cout<<"请输入需要译码的字符串："<<endl;
		i=0;
		char a[100];
		while(1)
		{
		   char e;
		   cin>>e;
		   if(e=='!')break;
           a[i]=e;
		   i++;
		}
		char p[100];
		int m=1,j=0,q=0;
		while (1)
		{
		    for(m=1;m<=n;m++)
		     {
                 if(a[j]==HT[m].date)
                {
                   i=0;
                   while(1)
                   {
                      p[q]=HC[m][i];
                      i++;
                      q++;
                      if(HC[m][i]=='\0')break;
                    }
                }
		      }
		    j++;
		    if(a[j]=='\0')break;
		}
		for(i=0;i<q;i++)
		{
		   cout<<p[i];
		}
                cout<<endl;
		return 0;
}

