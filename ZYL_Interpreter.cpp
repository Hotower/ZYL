#include <cstdio>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <malloc.h>
#include <string>
#include <cstring>
#include <ctime>
using namespace std;

string comd;

ifstream fin("code.zyl");
ofstream fout("result.txt",ios::app);
ofstream foe("debug.txt",ios::app);

int linen=0,temo=1;

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

void insert_k(string nam,string dat,int k)//ÊèíÂÖ•‰∏Ä‰∏™ÂèòÈáè
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

void delete_k(string nam)//“∆≥˝±‰¡ø£¨”√”⁄÷ÿ–¬∏≥÷µ 
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

string get_k(string nam)//’“µΩ√˚Œ™namµƒ±‰¡øµƒ÷µ 
{
    vari *i;
    for(i=head;i->next!=NULL && i->name!=nam;i=i->next);
    if(i->name==nam) return i->data;
    return "INVALID VARIABLE";
}

string JudgeT(string bds)//≈–∂œ±Ì¥Ô Ωµƒ÷µ£®–Ë÷ÿ–¥£© 
{
    
}

bool Judge(string bds)//¬ﬂº≠‘ÀÀ„£®–Ë÷ÿ–¥£©
{
    
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
    if(comd.substr(0,5)=="when(")//when & when<>repeatÃıº˛&—≠ª∑”Ôæ‰ 
    {
        if(!(comd.substr(comd.length()-6,6)=="repeat"))//whenÃıº˛”Ôæ‰ 
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
        else//when<>repeat—≠ª∑”Ôæ‰
        {
            FILE *dmo;
            char namef[50];
            sprintf(namef,"temp%d",temo);
            temo++;
            ofstream foutout(namef);
            string tiaojian=comd.substr(5,comd.length()-12);
            int stac[100],top=0;
            stac[top]=1;
            while(fin>>comd && top>=0)
            {
                if(comd=="end")
                {
                    top--; continue;
                }
                if(comd.substr(0,5)=="when(")
                {
                    top++;
                    if(!(comd.substr(comd.length()-6,6)=="repeat"))
                    {
                        stac[top]=0;
                    }
                    else
                    {
                        stac[top]=1;
                    }
                }
                foutout<<comd<<endl;
            }
            foutout.close();
            while(Judge(tiaojian))
            {
                ifstream fini(namef);
                while(fini>>comd)
                {
                    doing();
                }
            }
            remove(namef);
        }
    }
    else if(comd.substr(0,4)=="out(")//out ‰≥ˆ
    {
        for(int i=4;comd[i]!=')'&&i<comd.length();i++)
        {
            if(comd[i]=='\"')//¥¯“˝∫≈≤ø∑÷‘≠—˘ ‰≥ˆ 
            {
                if(comd[i]==',') continue;
                for(int j=i+1;comd[j]!='\"'&&j<comd.length();j++,i++)
                {
                    if(comd[j]=='@')
                    {
                        j++,i++;
                        switch(comd[j])//@◊™“Â∑˚∫≈ 
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
            else//∑Ò‘Ú ‰≥ˆ±‰¡øªÚ±Ì¥Ô Ωµƒ÷µ 
            {
                string name="",data="";
                for(int j=i;comd[j]!=',' && comd[j]!=')' && j<comd.length();i++,j++)
                {
                        name+=comd[j];
                }
                string ans=get_k(name);
                if(ans=="INVALID VARIABLE")
                	foe<<"In Line "<<linen<<":Invalid Variable"<<endl;
                else
                	for(int i=0;i<ans.length();i++)
                    	printf("%c",ans[i]);
            }
        }
    }
    else if(comd.substr(0,4)=="def(")//def∂®“Â±‰¡ø 
    {
        string name="",data="";
        int i;
        for(i=4;comd[i]!=',' && comd[i]!=')' && i<comd.length();i++)
        {
            name+=comd[i];
        }//œ¬√ÊºÏ≤‚ «∑Ò”–≥ı º÷µ 
        if(comd[i]==',')
            for(int j=i+1;comd[j]!=')';j++)
                data+=comd[j];
        else data="0";
        insert_k(name,data,1);
    }
    else if(comd.substr(0,3)=="in(")//in ‰»Î 
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
    else
    {
        bool flg=0;
        string name="",y;
        for(int i=0;i<comd.size();i++)
        {
            if(comd[i]=='=')
            {
                delete_k(name);
                insert_k(name,JudgeT(comd.substr(i+1,comd.size()-i-1)),1);
                flg=1;
            }
            else
            {
                name+=comd[i];
            }
        }
        if(flg)
        {
            foe<<"In Line "<<linen<<":Invalid Variable"<<endl;
        }
    }
}

void timenow()
{
    time_t now=time(0);
    tm *ltm=localtime(&now);
    foe<<1900+ltm->tm_year;
    if((1 + ltm->tm_mon)/10!=0)
    	foe<<"."<<1+ltm->tm_mon;
    else
    	foe<<".0"<<1+ltm->tm_mon;
    if((ltm->tm_mday)/10!=0)
    	foe<<"."<<ltm->tm_mday;
    else
    	foe<<".0"<<ltm->tm_mday;
    foe <<" - "<<ltm->tm_hour <<":";
    if((ltm->tm_min)/10!=0)
    	foe<<ltm->tm_min;
    else
    	foe<<"0"<<ltm->tm_min;
    if((ltm->tm_sec)/10!=0)
    	foe<<":"<<ltm->tm_sec;
    else
    	foe<<":0"<<ltm->tm_sec;
	foe<<" --------------"<<endl;
}

int main()
{
    freopen("result.txt","w",stdout);
    freopen("input.txt","r",stdin);
    head=(vari *)malloc(sizeof(vari));
    head->next=NULL;
    haouse['+']=1; haouse['-']=2; haouse['*']=3; haouse['/']=4; haouse['%']=5;
    haouse['&']=6; haouse['|']=7; haouse['>']=8; haouse['<']=9; haouse['=']=10; haouse['!']=11;
    foe<<"-------------- ZYL INTERPRET LOG --- "; timenow();
    while(linen++,fin>>comd)
    {
        doing();
    }
    fclose(stdout); fclose(stdin); fin.close(); fout.close();
    return 0;
}
