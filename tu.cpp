#include<iostream>
#define Maxsize 20
using namespace std;
typedef struct
{
  char vexs[Maxsize];
  int AdjMatrix[Maxsize][Maxsize];
  int vexnum,arcnum;
  int length;
}Graph;
typedef struct QNode
{
  char data;
  struct QNode *next;
}QNode,*QueuePtr;
typedef struct
{
  QueuePtr Front;
  QueuePtr Rear;
}LinkQueue;
void InitQueue(LinkQueue &q)
{
  q.Rear=new QNode;
  q.Front=q.Rear;
  q.Front->next=NULL;
}
void EnQueue(LinkQueue &q,char e)
{
  QueuePtr p;
  p=new QNode;
  p->data=e;
  p->next=NULL;
  q.Rear->next=p;
  q.Rear=p;
}
char DeQueue(LinkQueue &q)
{
  char e;
  QueuePtr p;
  p=new QNode;
  p=q.Front->next;
  e=p->data;
  q.Front->next=p->next;
  return e;
}
void InitGraph(Graph &g, int n)
{
   g.vexnum=0;
   g.arcnum=0;
   g.length=n;
   for(int i=0;i<Maxsize;i++)
   {
     for(int j=0;j<Maxsize;j++)
     {
       g.AdjMatrix[i][j]=0;
     }
   }
   for(int i=0;i<Maxsize;i++)
   {
     g.vexs[i]='\0';
   }
}
void creatGraph(Graph &g , int n)
{
  InitGraph(g,n);
  cout<<"请输入图节点数："<<endl;
  for(int i=0;i<n;i++)
  {
    char e;
    cin>>e;
    g.vexs[i]=e;
  }
  cout<<"请输入有向边以“!!”结束："<<endl;
  while(1)
  {
    char e1,e2;
    cin>>e1>>e2;
    if(e1=='!'and e1=='!')break;
    for(int x=0;x<n;x++)
    {
      if(g.vexs[x]==e1)
      {
         for(int y=0;y<n;y++)
	 {
	   if(g.vexs[y]==e2)g.AdjMatrix[x][y]=1;
	 }
      }
    }
  }
  for(int i=0;i<n;i++)
  {
    if(g.vexs[i]!='\0')g.vexnum++;
  }
  for(int i=0;i<n;i++)
  {
     for(int j=0;j<n;j++)
	     if(g.AdjMatrix[i][j]!=0)g.arcnum++;
  }
}
int  getNumVertices(Graph g)
{
    return g.vexnum ;
}
int getNumEdges(Graph g)
{
   return g.arcnum ;
}
bool validVertex(Graph g,char v)
{
   for(int i=0;i<g.length;i++)
   {
     if(g.vexs[i]==v)return true;
   }
   return false;
}
int getPositon(Graph g,char e)
{
  int i=0;
  for(;i<g.length;i++)
  {
     if(g.vexs[i]==e)break;
  }
  return i;
}
bool hasEdge(Graph g,char u ,char v)
{
	int x,y;
	if(validVertex(g,u) and validVertex(g,v))
	{
	  x=getPositon(g,u);
          y=getPositon(g,v);
	  if(g.AdjMatrix[x][y]==1)return true;
	}
	return false;
}
void addVertex(Graph &g,char u)
{
 if(!validVertex(g,u))
 {
	 g.vexs[g.length]=u;
	 g.length++;
	 g.vexnum++;
	 g.arcnum++;
 }
}
void addEdge(Graph &g,char u,char v)
{
   int x,y;
   if(!hasEdge(g,u,v))
   {
      x=getPositon(g,u);
      y=getPositon(g,v);
      g.AdjMatrix[x][y]=1;
   }
}
void removeEdge(Graph &g,char u,char v)
{
  int x,y;
  if(!hasEdge(g,u,v))
  {
    x=getPositon(g,u);
    y=getPositon(g,v);
    g.AdjMatrix[x][y]=0;
  }
}
void outputGraph(Graph g)
{
  for(int i=0;i<g.length;i++)
  {
    for(int j=0;j<g.length;j++)
    {
      if(g.AdjMatrix[i][j]==1)cout<<"1"<<" ";
      else cout<<"0"<<" ";
    }
    cout<<endl;
  }
}
LinkQueue length1Path(Graph g ,LinkQueue q)
{
  LinkQueue p;
  InitQueue(p);
  do
  {
    char e;
    int a;
    e=DeQueue(q);
    a=getPositon(g,e);
    for(int i=0;i<g.length;i++)
    {
      if(g.AdjMatrix[i][a]==1)EnQueue(p,g.vexs[i]);
    }
  }while(q.Front->next!=NULL);
  return p;
}
Graph lengthPath(Graph g, char v,int n)
{
  Graph ng;
  InitGraph(ng,g.length);
  LinkQueue q,p;
  InitQueue(p);
  InitQueue(q);
  EnQueue(q,v);
  int c;
  c=getPositon(g,v);
  p=length1Path(g,q);
  while(n>1)
  {
    p=length1Path(g,p);
    n--;
  }
  int i=0;
  do
  {
    char e;
    e=DeQueue(p);
    ng.vexs[i]=e;
    i++;
  }while(p.Front->next!=NULL);
  for(int a=0;a<i;a++)
  {
     for(int b=0;b<g.length;b++)
     {
       if(ng.vexs[a]==g.vexs[b])
         {
           ng.AdjMatrix[b][c]=1;
         }
      }
  }
  return ng;
}
int main()
{
   Graph g,ng;
   int n;
   cout<<"请输入图中一共含有多少节点："<<endl;
   cin>>n;
   creatGraph(g,n);
   InitGraph(ng,g.length);
   int x,y;
   x=getNumVertices(g);
   y=getNumEdges(g);
   cout<<"顶点个数："<<x<<endl;
   cout<<"边的个数："<<y<<endl;
   outputGraph(g);
   cout<<endl;
   char e;
   cout<<"请输入选择的字符："<<endl;
   cin>>e;
   cout<<"请输入经过几跳到达："<<endl;
   cin>>n;
   ng=lengthPath(g,e,n);
   outputGraph(ng);
   return 0;
}

