//SBT
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define inf 1234567890
struct SBT
{
    int left,right,s,key;
    void init()
    {
        left=right=0;
        s=1;
    }
} a[100010];
int tol=0;
int root=0;
void left_rotate(int &t)//左旋
{
    int k=a[t].right;
    a[t].right=a[k].left;
    a[k].left=t;
    a[k].s=a[t].s;
    a[t].s=a[a[t].left].s+a[a[t].right].s+1;
    t=k;
}
void right_rotate(int &t)//右旋
{
    int k=a[t].left;
    a[t].left=a[k].right;
    a[k].right=t;
    a[k].s=a[t].s;
    a[t].s=a[a[t].left].s+a[a[t].right].s+1;
    t=k;
}
void maintain(int &t,bool flag)//保持
{
    if(flag==0)
    {
        if(a[a[a[t].left].left].s>a[a[t].right].s)
            right_rotate(t);
        else if(a[a[a[t].left].right].s>a[a[t].right].s)
        {
            left_rotate(a[t].left);
            right_rotate(t);
        }
        else return ;
    }
    else
    {
        if(a[a[a[t].right].right].s>a[a[t].left].s)
            left_rotate(t);
        else if(a[a[a[t].right].left].s>a[a[t].left].s)
        {
            right_rotate(a[t].right);
            left_rotate(t);
        }
        else return ;
    }
    maintain(a[t].left,0);
    maintain(a[t].right,1);
    maintain(t,0);
    maintain(t,1);
}
void insert(int &t,int v)//插入
{
    if(t==0)
    {
        t=++tol;
        a[t].init();
        a[t].key=v;
    }
    else
    {
        a[t].s++;
        if(v<a[t].key)
            insert(a[t].left,v);
        else insert(a[t].right,v);
        maintain(t,v>=a[t].key);
    }
}
int del(int &t,int v)//删除
{
    if(!t)
        return 0;
    a[t].s--;
    if(v==a[t].key || v<a[t].key&& !a[t].left || v>a[t].key&&!a[t].right)//懂了
    {
        if(a[t].left&&a[t].right)
        {
            int p=del(a[t].left,v+1);
            a[t].key=a[p].key;
            return p;
        }
        else
        {
            int p=t;
            t=a[t].left+a[t].right;
            return p;
        }
    }
    else return del(v<a[t].key?a[t].left:a[t].right,v);
}
int find(int t,int k)//寻找第k小的数
{
    if(k<=a[a[t].left].s)
        return find(a[t].left,k);
    if(k>a[a[t].left].s+1)
        return find(a[t].right,k-a[a[t].left].s-1);
    return a[t].key;
}
int maxless(int t,int k)
{
    if(t==0) return -inf;
    if(a[t].key>=k) return maxless(a[t].left,k);
    return max(a[t].key,maxless(a[t].right,k));
}


int main()
{
    tol=root=0;//初始化，根是0;
    //初始的时候树是空的，如果你想加入某个数x：insert(root，x);
    //如果你想删除某个已加入的数x：del(root，x)；
    //如果你想查找该集合中第k大的数：find(root，k)；
    int n,mi,i,j,k,tmp,cha,x,num;
    char op[10];
    while(scanf("%d %d",&n,&mi)!=EOF)
    {
        num=0;
        tol=root=tmp=0;
        for(i=0; i<n; i++)
        {
            scanf("%s %d",op,&cha);
            if(op[0]=='I')
            {
                cha=cha-mi;
                if(cha<0) continue;
                num++;
                insert(root,cha-tmp);
            }

            else if(op[0]=='A') tmp+=cha;
            else if(op[0]=='S')
            {
                tmp=tmp-cha;
                    x=maxless(root,-tmp);
                    while(num>0&&x!=-inf)
                    {
                        //printf("%d::\n",x);
                        num--;
                        del(root,x);
                        x=maxless(root,-tmp);
                    }

            }
            else
            {
                if(num<cha)
                    printf("-1\n");
                else
                    printf("%d\n",find(root,num-cha+1)+tmp+mi);
            }

        }
        printf("%d\n",tol-num);
    }

    return 0;
}

