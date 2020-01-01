#include <cstdio>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <malloc.h>
#include <string>
using namespace std;

string comd;

ifstream fin("code.zyl");
ofstream fout("result.txt",ios::app);

const int SFK=5;
string SF="+-*/%";

const int PDK=6;
string PD="&|><=!";

int haouse[128];

struct vari
{
    string name,data;
    vari *next;
}*head;

void insert_k(string nam,string dat,int k)//插入一个变量
{
	vari *p,*nNode;
	int i=0;
	p=head; nNode=new vari; nNode->data=dat; nNode->name=nam;
	while(p && i<k-1)
	{
		p=p->next;
		i++;
	}
	if(!p || i>k-1){free(p); free(nNode); return;}
	nNode->next=p->next;
	p->next=nNode;
	return;
}

void delete_k(string nam)//删除一个变量，用以赋值
{
    vari *i;
    for(i=head;i->next!=NULL && i->name!=nam;i=i->next);
    if(i->next==NULL)
    {
        return;
    }
    if(i->name==nam)
    {
        vari *p;
        p=i->next;
        i->next=p->next;
        free(p);
        return;
    }
    return;
}

string get_k(string nam)//得到某个变量的值
{
    vari *i;
    for(i=head;i->next!=NULL && i->name!=nam;i=i->next);
    if(i->name==nam) return i->data;
    return "";
}

string JudgeT(string bds)//计算表达式的值
{
    string x,y;
    bool flg=1;
    int mode=0;
    for(int i=0;i<bds.length();i++)//判断有无运算符
    {
        for(int j=0;j<SFK;j++)
        {
            if(bds[i]==SF[j])
                flg=0,mode=haouse[SF[j]];
        }
        if(flg)
            x+=bds[i];
        else//如果出现了运算符
        {
            y=JudgeT(bds.substr(i+1,bds.size()-i));
            break;
        }
    }
    if(mode)//如果有运算符
    {
        if(get_k(x)=="")//如果没有变量名称与x相同
        {
            if(atoi((char *)x.data())!=0 && atoi((char *)y.data())!=0)//如果两边是数字
            {
                int ans;
                switch(mode)
                {
                    case 1: ans=atoi((char *)x.data())+atoi((char *)y.data()); break;
                    case 2: ans=atoi((char *)x.data())-atoi((char *)y.data()); break;
                    case 3: ans=atoi((char *)x.data())*atoi((char *)y.data()); break;
                    case 4:
                        if(atoi((char *)y.data())!=0) ans=atoi((char *)x.data())/atoi((char *)y.data());
                        break;
                }
                return to_string(ans);
            }
            else//如果两边不是数字
            {
                string ans;
                switch(mode)
                {
                    case 1: ans=x+y;
                }
                return ans;
            }
        }
        else
        {
            x=get_k(x);
            if(atoi((char *)x.data())!=0 && atoi((char *)y.data())!=0)//如果两边是数字
            {
                int ans;
                switch(mode)
                {
                    case 1: ans=atoi((char *)x.data())+atoi((char *)y.data()); break;
                    case 2: ans=atoi((char *)x.data())-atoi((char *)y.data()); break;
                    case 3: ans=atoi((char *)x.data())*atoi((char *)y.data()); break;
                    case 4:
                        if(atoi((char *)y.data())!=0) ans=atoi((char *)x.data())/atoi((char *)y.data());
                        break;
                }
                return to_string(ans);
            }
            else//如果两边不是数字
            {
                string ans;
                switch(mode)
                {
                    case 1: ans=x+y;
                }
                return ans;
            }
        }
    }
    else//如果无运算符
        return x;
}

bool Judge(string bds)//判断表达式的真假
{
    for(int i=0;i<bds.length();i++)//有无运算符
    {
        for(int j=0;j<PDK;j++)
        {
            if(bds[i]==PD[j])
            {
                string x=bds.substr(0,i),y=bds.substr(i+1,bds.length()-i-1),z=bds.substr(i+2,bds.length()-i-2);
                int a,b,c;
                if(get_k(x)!="") {x=get_k(x);}
                if(get_k(y)!="") {y=get_k(y);}
                if(get_k(z)!="") {z=get_k(z);}
                if(atoi((char *)JudgeT(x).data())!=0) {a=atoi((char *)JudgeT(x).data());}
                if(atoi((char *)JudgeT(y).data())!=0) {b=atoi((char *)JudgeT(y).data());}
                if(atoi((char *)JudgeT(z).data())!=0) {c=atoi((char *)JudgeT(z).data());}
                //处理变量的情况
                if(bds[i]=='&') return Judge(x) && Judge(y);
                if(bds[i]=='|') return Judge(x) || Judge(y);
                if(bds[i]=='>')
                {
                    if(bds[i+1]=='=')
                    {
                        if(a==0 || c==0)
                            return JudgeT(x) >= JudgeT(z);
                        return a>=c;
                    }
                    if(a==0 || b==0)
                        return JudgeT(x) > JudgeT(y);
                    return a>b;
                }
                if(bds[i]=='<')
                {
                    if(bds[i+1]=='=')
                    {
                        if(a==0 || c==0)
                            return JudgeT(x) <= JudgeT(z);
                        return a<=c;
                    }
                    if(a==0 || b==0)
                        return JudgeT(x) < JudgeT(y);
                    return a<b;
                }
                if(bds[i]=='!')
                {
                    if(bds[i+1]=='=')
                        return JudgeT(bds.substr(0,i)) != JudgeT(bds.substr(i+2,bds.length()-i-2));
                    return ! Judge(z);
                }
                if(bds[i]=='=')
                    return (JudgeT(bds.substr(0,i)) == JudgeT(bds.substr(i+1,bds.length()-i-1)));
            }
        }
    }
    bds=JudgeT(bds);
    if(bds!="" && bds!="0")
        return true;
    return false;
}

bool zc(string a,string b)
{
    bool flg=0;
    int tot;
    for(int i=0;i<a.size();i++)
    {
        tot=0;
        for(int j=0;j<b.size();j++)
        {
            if(a[i]==b[j]) tot++;
        }
        if(tot==b.size()) flg=1;
    }
    return flg;
}

void doing()
{
    if(comd.substr(0,5)=="when(")//when & when<>repeat函数（完善）
    {
        if(!(comd.substr(comd.length()-6,6)=="repeat"))//when函数（完善）
        {
            string tiaojian=comd.substr(5,comd.length()-1);
            if(Judge(tiaojian))
            {
                while(fin>>comd && comd!="end")
                {
                    doing();
                }
            }
        }
        else//when<>repeat函数（完善）
        {
            FILE *dmo;
            ofstream foutout("temp.txt");
            string tiaojian=comd.substr(5,comd.length()-12);
            while(fin>>comd && comd!="end")
            {
                foutout<<comd<<endl;
            }
            foutout.close();
            while(Judge(tiaojian))
            {
                ifstream fini("temp.txt");
                while(fini>>comd)
                {
                    doing();
                }
            }
            remove("temp.txt");
        }
    }
    else if(comd.substr(0,4)=="out(")//out函数（完善）
    {
        for(int i=4;comd[i]!=')'&&i<comd.length();i++)
        {
            if(comd[i]=='\"')//引号内内容原样输出
            {
                if(comd[i]==',') continue;
                for(int j=i+1;comd[j]!='\"'&&j<comd.length();j++,i++)
                {
                    if(comd[j]=='@')
                    {
                        j++,i++;
                        switch(comd[j])//当遇到@转义符号时特殊输出
                        {
                            case '@':printf("@"); break;
                            case 'l':printf("\n"); break;
                            case '\"':printf("\""); break;
                            case 'e':printf(" "); break;
                        }
                    }
                    else
                        printf("%c",comd[j]);
                }
                i++;
            }
            else//否则输出变量的值
            {
                string name="",data="";
                for(int j=i;comd[j]!=',' && comd[j]!=')' && j<comd.length();i++,j++)
                {
                        name+=comd[j];
                }//找变量名
                string ans=get_k(name);
                for(int i=0;i<ans.length();i++)
                    printf("%c",ans[i]);
            }
        }
    }
    else if(comd.substr(0,4)=="def(")//def函数（完善）
    {
        string name="",data="";
        int i;
        for(i=4;comd[i]!=',' && comd[i]!=')' && i<comd.length();i++)
        {
            name+=comd[i];
        }//存储变量名
        if(comd[i]==',')
            for(int j=i+1;comd[j]!=')';j++)
                data+=comd[j];
        else data="0";
        insert_k(name,data,1);
    }
    else if(comd.substr(0,3)=="in(")//in函数（完善）
    {
        int i=3;
        while(1)
        {
            string name="",data="";
            for(;comd[i]!=',' && comd[i]!=')';i++)
            {
                name+=comd[i];
            }
            char d;
            while(scanf("%c",&d)!=EOF && d!=' ')
                data+=d;
            delete_k(name);
            insert_k(name,data,1);
            if(comd[i]==')')
                break;
            i++;
        }
    }
    else//赋值语句
    {
        string name="",y;
        for(int i=0;i<comd.size();i++)
        {
            if(comd[i]=='=')
            {
                delete_k(name);
                insert_k(name,JudgeT(comd.substr(i+1,comd.size()-i-1)),1);
            }
            else
            {
                name+=comd[i];
            }
        }
    }
}

int main()
{
    freopen("result.txt","w",stdout);
    freopen("input.txt","r",stdin);
    head=(vari *)malloc(sizeof(vari));
    head->next=NULL;
    haouse['+']=1; haouse['-']=2; haouse['*']=3; haouse['/']=4; haouse['%']=5;
    haouse['&']=6; haouse['|']=7; haouse['>']=8; haouse['<']=9; haouse['=']=10; haouse['!']=11;
    while(fin>>comd)
    {
        doing();
    }
    fclose(stdout); fclose(stdin); fin.close(); fout.close();
    return 0;
}
