#include <iostream>
#include<stack>
using namespace std;
typedef struct BiTNode
{
   char date;
   struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void InitBiTree (BiTree &t)
{
   t=new BiTNode;
}
void CreatBiTree(BiTree &t)
{
   char e;
   cin>>e;
   if(e == '!')
   {
       t=NULL;
       return;
   }
   else
   {
      InitBiTree(t);
      t->date=e;
      CreatBiTree(t->lchild);
      CreatBiTree(t->rchild);
   }
}
void OutputBiTree (BiTree t)
{
   if(t!=NULL)
   {
     cout<<t->date;
     OutputBiTree(t->lchild);
     OutputBiTree(t->rchild);
   }
}
int DepthBiTree(BiTree t)
{
     if(t)
      {
        int dl=DepthBiTree(t->lchild);
        int dr=DepthBiTree(t->rchild);
        if(dl>dr)return dl+1;
        else   return dr+1;
      }
 return 0;
}
void InsertChild(BiTree &p,BiTree &c,int i)
{
     if(i==1)p->lchild=c;
     else if(i==0)p->rchild=c;
     else cout<<"ERROR"<<endl;
}
void OutputNo(BiTree t)
{
    stack <BiTree>S;
    BiTree p;
    p=t;
    while(!S.empty()||p)
    {
        if(p)
        {
            S.push(p);
            cout<<p->date;
            p=p->lchild;
        }
        else
        {
            p=S.top();
            S.pop();
            p=p->rchild;
        }
    }
}
int main()
{
    BiTree t,c;
    int i;
    char e;
    c=new BiTNode;
    c->date='f';
    CreatBiTree(t);
    //OutputBiTree(t);
    i=DepthBiTree(t);
    //cout<<"输入1表示插入左儿子，0表示插入右儿子："<<endl;
    //cin>>i;
    //InsertChild(t->lchild,c,i);
    OutputBiTree(t);
    cout<<endl;
    OutputNo(t);
    return 0;
}

