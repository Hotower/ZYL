#include <cstdio>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

string comd;

int main()
{
    FILE *fstdin;
    freopen("result.txt","w",stdout);
    fstdin=fopen("input.txt","rb");
    ifstream fin("code.zyl");
    ofstream fout("result.txt");

    while(fin>>comd)
    {
        if(comd.substr(0,4)=="out(")//out函数
        {
            for(int i=4;comd[i]!=')'&&i<comd.length();i++)
            {
                int j=0;
                if(comd[i]=='\"')//引号内内容原样输出
                {
                    for(j=i+1;comd[j]!='\"'&&j<comd.length();j++)
                    {
                        if(comd[j]=='@')
                        {
                            j++;
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
                    i=j+1;
                }
            }
        }
    }

    fclose(stdout); fclose(fstdin); fin.close();
    return 0;
}
