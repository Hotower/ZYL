#include <cstdio>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <malloc.h>
using namespace std;

string comd;

struct vari
{
    string name,data;
    vari *next;
}*head;

void insert_k(string nam,string dat,int k)
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

void delete_k(string nam)
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

string get_k(string nam)
{
    vari *i;
    for(i=head;i->next!=NULL && i->name!=nam;i=i->next);
    if(i->name==nam) return i->data;
    return "";
}

int main()
{
    freopen("result.txt","w",stdout);
    freopen("input.txt","r",stdin);
    ifstream fin("code.zyl");
    ofstream fout("result.txt");
    head=(vari *)malloc(sizeof(vari));
    head->next=NULL;

    while(fin>>comd)
    {
        if(comd.substr(0,4)=="out(")//out函数（完善）
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
    }

    fclose(stdout); fclose(stdin); fin.close(); fout.close();
    return 0;
}
