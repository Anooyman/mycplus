#include <iostream>
using namespace std;
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
char DeQueue(LinkQueue q)
{
  char e;
  QueuePtr p;
  p=new QNode;
  p=q.Front->next;
  e=p->data;
  q.Front->next=p->next;
  return e;
}
void InputQueue(LinkQueue &q)
{
  char e,c ;
  while(1)
  {
   cout<<"请输入队列元素："<<endl;
   cin>>e;
   if(e=='!')break;
   EnQueue(q,e);
  }
}
void outputQueue(LinkQueue q)
{
  do
  {
    char e;
    e=q.Front->next->data;
    q.Front=q.Front->next;
    cout<<e<<" ";
  }while(q.Front->next!=NULL);
}
int main()
{
    LinkQueue p;
    InitQueue(p);
    InputQueue(p);
    outputQueue(p);S
    return 0;
}
