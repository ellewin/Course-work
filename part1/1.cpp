#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int countStateA,countStateB,lastRuleA,lastRuleB,n;
int moduleA,moduleB;
fstream s;
//This structure describes the configuration for each state of
struct configuration
{
	int state;
	int number;
	int operation;
	int letter;
};
configuration * setRulesA = new configuration [20];
configuration * setRulesB = new configuration [20];
int counting (int top, int operation, int number,int module)
{
	int result;
	if(operation==1)
	{
		if(top+number<=module)
			return top+number;
		else
			return (module+top+number)%module;
	}
	if(operation==2)
	{
		if(top-number<=module && top-number>0)
			return top-number;
		else
			return (module+top-number)%module;
	}
	if(operation==3)
	{
		if(top*number<=module)
			return top*number;
		else
			return (module+top*number)%module;
	}
	if(operation==4)
	{
		if(top/number<=module)
			return top/number;
		else
			return (module+top/number)%module;
	}
}
void generateAutomate(int module)
{
	/*if(letter==-1)
	{
		cout<<"error: letter is not"<<endl;
		return;
	}
	if(rightBorder==-1)
	{
		cout<<"Infinity"<<endl;
	}*/
	if(module==8)
		return;
	vector<int> matrix[2];
	matrix[0].push_back(0);
	matrix[1].push_back(1);
	n=module;
	for(int i=1; i<countStateA+1; ++i)
	{
		int newState;
		if(setRulesA[i].operation!=0)
		{
			newState=counting(i,setRulesA[i].operation,setRulesA[i].number,module);
			matrix[0].push_back(newState);
		}
		else
		{
			if(setRulesA[i].number!=0)
			{
				cout<<setRulesA[i].number<<endl;
				matrix[0].push_back(setRulesA[i].number);
			}
			else
			{
				matrix[0].push_back(i);
			}
		}
	}
	for(int i=1; i<countStateB+1; ++i)
	{
		int newState;
		if(setRulesB[i].operation!=0)
		{
			newState=counting(i,setRulesB[i].operation,setRulesB[i].number,module);
			matrix[1].push_back(newState);
		}
		else
		{
			if(setRulesB[i].number!=0)
			{
				cout<<setRulesB[i].number<<endl;
				matrix[1].push_back(setRulesB[i].number);
			}
			else
			{
				matrix[1].push_back(i);
			}
		}
	}
	for(int i=moduleA+1; i<=n; ++i)
	{
		int newState;
		if(setRulesA[lastRuleA].operation!=0)
		{
			newState=counting(i,setRulesA[lastRuleA].operation,setRulesA[lastRuleA].number,module);
			matrix[0].push_back(newState);
		}
		else
		{
			if(setRulesA[lastRuleA].number!=0)
			{
				cout<<setRulesA[lastRuleA].number<<endl;
				matrix[0].push_back(setRulesA[lastRuleA].number);
			}
			else
			{
				matrix[0].push_back(i);
			}
		}
	}
	for(int i=moduleB+1; i<=n; ++i)
	{
		int newState;
		if(setRulesB[lastRuleB].operation!=0)
		{
			cout<<"i "<<i<<endl;
			newState=counting(i,setRulesB[lastRuleB].operation,setRulesB[lastRuleB].number,module);
			matrix[1].push_back(newState);
		}
		else
		{
			if(setRulesB[lastRuleB].number!=0)
			{
				cout<<setRulesB[lastRuleB].number<<endl;
				matrix[1].push_back(setRulesB[lastRuleB].number);
			}
			else
			{
				matrix[1].push_back(i);
			}
		}
	}
	++module;
	//cout<<"n "<<n<<endl;
	for(int i=0; i<2; ++i)
	{
		for(int j=1; j<matrix[i].size(); ++j)
			s<<matrix[i][j];
		s<<endl;
	}
	generateAutomate(module);
}
void readFile(string config)
{
	countStateA=countStateB=0;
    ifstream fd(config.c_str());
    string rule;
	int first,second;
    while(getline(fd,rule))
    {
        int letter=-1;
        int operation=0;
        int flag=0;
		first=-1;
        second=-1;
		int inf=0;
		int numeric=0;
        for(int i=0; i<rule.length(); ++i)
        {
            char symbol=rule[i];
            string number="";
            if(symbol=='{')
            {
                int j=i+1;
                while(rule[j]!='.' && rule[j]!='}')
                {
                    number+=rule[j];
                    ++j;
                }
                first=atoi(number.c_str());
                number="";
                i=j;
                while(rule[i]!='}')
                {
                    if(rule[i]=='.')
                    {
                        ++i;
                    }
					else
					{
						if(rule[i]=='n')
						{
							inf=1;
							++i;
							break;
						}
						number+=rule[i];
						++i;
					}
                }
				if(inf!=1 && number!="")
				{
					second=atoi(number.c_str());
                	number="";	
				}
            }
			//cout<<"!!! "<<first<<" "<<second<<endl;
            if(symbol=='a')
            {
                letter=0;
                ++i;
            }
            if(symbol=='b')
            {
                letter=1;
                ++i;
            }
            if (symbol=='=')
            {
                ++i;
                while(i!=rule.length())
				//for(;i!=rule.length();++i)
                {
                    if(rule[i]==' ')
                    {
                        ++i;
                    }
                    else
                    {
                        if(rule[i]=='k')
                        {
                            flag=1;
                            ++i;
                        }
                        else
                        {
                            number+=rule[i];
                            ++i;
                        }
                        if(rule[i]=='+')
                        {
                            operation=1;
                            ++i;
                            continue;
                        }
                        if(rule[i]=='-')
                        {
                            operation=2;
                            ++i;
                            continue;
                        }
                        if(rule[i]=='*')
                        {
                            operation=3;
                            ++i;
                            continue;
                        }
                        if(rule[i]=='/')
                        {
                            operation=4;
                            ++i;
                            continue;
                        }
                    }
                }
                numeric=atoi(number.c_str());
            }
        }
        if(second!=-1)
		{
			if(letter==0)
			{
				for(int l=first; l<second+1; ++l)
				{
					setRulesA[l].state=l;
					setRulesA[l].number=numeric;
					setRulesA[l].operation=operation;
					++countStateA;
				}
			}
			else
			{
				for(int l=first; l<second+1; ++l)
				{
					setRulesB[l].state=l;
					setRulesB[l].number=numeric;
					setRulesB[l].operation=operation;
					++countStateB;
				}
			}
		}
		else
		{
			if(letter==0)
			{
				setRulesA[first].state=first;
				setRulesA[first].number=numeric;
				setRulesA[first].operation=operation;
				++countStateA;
				lastRuleA=first;
			}
			else
			{
				setRulesB[first].state=first;
				setRulesB[first].number=numeric;
				setRulesB[first].operation=operation;
				++countStateB;
				lastRuleB=first;
			}
		}
	}
	int module;
	moduleA=moduleB=-1;
	for(int i=1; i<countStateA+1; ++i)
	{
		if(moduleA<setRulesA[i].state)
		{
			moduleA=setRulesA[i].state;
		}
	}
	for(int i=1; i<countStateB+1; ++i)
	{
		if(moduleB<setRulesB[i].state)
		{
			moduleB=setRulesB[i].state;
		}
	}
	if(moduleA>moduleB)
		module=moduleA;
	else
		module=moduleB;
	++module;
	generateAutomate(module);
    fd.close();
}
int main(int argc, char *mas[], char *envp[])
{
	string config(mas[1]);
	s.open("aa");
    readFile(config);
    return 0;
}
