#include "Profiling.hpp"

#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;



Profiler P;
auto *P_t = &P;

#define _MYTIMER_(funcname) ProfileUnit pu(P_t,funcname);

#define maxl 100005
#define maxa 100005
int sz[maxa],chi[maxa][2],cc[maxa],f[maxa],np,rt;
unsigned long long w[maxa],_power[100005],pow_num=29;
void _read(int &x)
{
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        ch=getchar();
    }
    x=0;
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return ;
}
void push_up(int now)
{
    sz[now]=1;w[now]=0;
    if(chi[now][1])
    {
        sz[now]+=sz[chi[now][1]];
        w[now]=w[chi[now][1]];
    }
    w[now]=w[now]*pow_num+cc[now];
    if(chi[now][0])
    {
        sz[now]+=sz[chi[now][0]];
        w[now]=w[chi[now][0]]+w[now]*_power[sz[chi[now][0]]];
    }
    return ;
}
void Link(int i,int d,int j)
{
    chi[i][d]=j;
    f[j]=i;
    return ;
}
void rot(int x)
{
    int y=f[x];int z=f[y];
    if(!y)return ;
    int d=(chi[y][0]==x);
    Link(y,d^1,chi[x][d]);
    Link(z,chi[z][1]==y,x);
    Link(x,d,y);
    push_up(y);push_up(x);
    return ;
}
void Splay(int &now,int x,int anc)
{
    int y,z;
    while(f[x]!=anc)
    {
        y=f[x]; z=f[y];
        if(z!=anc)
        {
            if((chi[z][1]==y)==(chi[y][1]==x))
            {
                rot(y);
            }
            else
            {
                rot(x);
            }
        }
        rot(x);
    }
    if(anc==0)
    {
        now=x;
    }
    return ;
}
int Kth(int &now,int k,int anc)
{
    int t,ct=0,p=now;
    while(p)
    {
        t=sz[chi[p][0]]+1;
        if(ct+t==k)
        {
            break;
        }
        else if(ct+t<k)
        {
            ct+=t;
            p=chi[p][1];
        }
        else
        {
            p=chi[p][0];
        }
    }
    if(p)Splay(now,p,anc);
    return p;
}
void update(int x,int c)
{
    int p=Kth(rt,x,0);
    cc[p]=c;
    push_up(p);
    return ;
}
void Insert(int x,int c)
{
    int p=Kth(rt,x,0);
    int q=Kth(rt,x+1,p);
    np++; w[np]=cc[np]=c;sz[np]=1;
    Link(q,0,np);
    push_up(q);
    push_up(p);
    return ;
}
unsigned gethash(int x,int y)
{
    _MYTIMER_("gethash")
    int p=Kth(rt,x-1,0);
    int q=Kth(rt,y+1,p);
    return w[chi[q][0]];
}
void query(int x,int y)
{
    _MYTIMER_("query_wxp")

    int l=0,r=min(np-x,np-y),mid,ans=0;
    unsigned long long t1,t2;
    while(l<=r)
    {
        mid=(l+r)>>1;
        t1=gethash(x,x+mid-1);
        t2=gethash(y,y+mid-1);
        if(t1==t2)
        {
            ans=mid;
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }
    }
    // printf("%d\n",ans);
    return ;
}
void ready()
{
    np=2; rt=1;
    f[1]=0;
    sz[1]=2; sz[2]=0; cc[1]=cc[2]=0;
    Link(1,1,2);
    return ;
}
char s0[maxl];
 
void Init()
{
    scanf("%s",s0);
//  fprintf(stderr,"%s\n",s0);
    int l=strlen(s0);
    ready();
 
    for(int i=0;i<l;i++)
    {
        Insert(i+1,s0[i]-'a');
        Splay(rt,np,0);
 
    }
    return ;
}
int m;
void work()
{
    ProfileUnit pu(P_t,"WORK");
    scanf("%d",&m);
//  if(m>100)return ;
//  fprintf(stderr,"%d\n",m);
    char op,col;
    int x,y;
    for(int i=1;i<=m;i++)
    {
        op=getchar();
        while(op!='Q' && op!='R' && op!='I')
        {
            op=getchar();
        }
        if(op=='Q')
        {
            _read(x); _read(y);
        //  fprintf(stderr,"%c %d %d\n",op,x,y);
            x++; y++;
            query(x,y);
        }
        else if(op=='R')
        {
            _read(x);
            x++;
            col=getchar();
            while(col<'a' || col>'z')
            {
                col=getchar();
            }
        //  fprintf(stderr,"%c %d %c\n",op,x-1,col);
            update(x,col-'a');
        }
        else
        {
            _read(x);
            x++;
            col=getchar();
            while(col<'a' || col>'z')
            {
                col=getchar();
            }
        //  fprintf(stderr,"%c %d %c\n",op,x-1,col);
            Insert(x,col-'a');
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    _power[0]=1;
    for(int i=1;i<=100000;i++)
    {
        _power[i]=_power[i-1]*pow_num;
    }
    Init();
    work();
    return 0;
}