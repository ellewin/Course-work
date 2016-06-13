//Парсит файл, извлекая из него конфигурации, по ним строит автоматы из n состояний. Записывает полученные автоматы в файл. 

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
int countStateA,countStateB,lastRuleA,lastRuleB,n,minCountState,oldRuleA,oldRuleB,secondA, secondB;
int moduleA,moduleB;
fstream s;
//This structure describes the configuration for each state of
struct configuration
{
	int state;
	int number;
	int operation;
	int letter;
	int flag;
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
	//cout<<minCountState<<endl;
	//if(secondA==1)
		for(int i=1; i<minCountState+1; ++i)
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
					//cout<<setRulesA[i].number<<endl;
					matrix[0].push_back(setRulesA[i].number);
				}
				else
				{
					if(setRulesA[i].flag==1 || setRulesA[i].flag==0)
						matrix[0].push_back(i);
					else
						matrix[0].push_back(module);
					//matrix[0].push_back(i);
				}
			}
		}
	//cout<<minCountState+1<<endl;
	//if(secondB==1)
		for(int i=1; i<minCountState+1; ++i)
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
					//cout<<setRulesB[i].number<<endl;
					matrix[1].push_back(setRulesB[i].number);
				}
				else
				{
					if(setRulesB[i].flag==1 || setRulesB[i].flag==0) 
						matrix[1].push_back(i);
					else
						matrix[1].push_back(module);
					//matrix[1].push_back(i);
				}
			}
		}
	if(oldRuleA!=-1)
	{
		//cout<<"yes"<<endl;
		for(int i=moduleA+1; i<=n-1; ++i)
		{
			//cout<<"n-1 "<<n-1<<endl;
			int newState;
			if(setRulesA[oldRuleA].operation!=0)
			{
				newState=counting(i,setRulesA[oldRuleA].operation,setRulesA[oldRuleA].number,module);
				matrix[0].push_back(newState);
			}
			else
			{
				//cout<<setRulesA[1].number<<endl;
				if(setRulesA[oldRuleA].number!=0)
				{
					cout<<1<<endl;
					cout<<setRulesA[oldRuleA].number<<endl;
					matrix[0].push_back(setRulesA[oldRuleA].number);
				}
				else
				{
					if(setRulesA[oldRuleA].flag==1 || setRulesA[oldRuleA].flag==0)
						matrix[0].push_back(i);
					else
						matrix[0].push_back(module);
					//matrix[0].push_back(i);
				}
			}
		}
		int newState;
		if(setRulesA[lastRuleA].operation!=0)
		{
			newState=counting(module,setRulesA[lastRuleA].operation,setRulesA[lastRuleA].number,module);
			matrix[0].push_back(newState);
		}
		else
		{
			if(setRulesA[lastRuleA].number!=0)
			{
				//cout<<setRulesA[lastRuleA].number<<endl;
				matrix[0].push_back(setRulesA[lastRuleA].number);
			}
			else
			{
				matrix[0].push_back(module);
			}
		}
	}
	else
	{
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
					//cout<<setRulesA[lastRuleA].number<<endl;
					matrix[0].push_back(setRulesA[lastRuleA].number);
				}
				else
				{
					if(setRulesA[lastRuleA].flag==1 || setRulesA[lastRuleA].flag==0)
						matrix[0].push_back(i);
					else
						matrix[0].push_back(module);
					//matrix[0].push_back(i);
				}
			}
		}
	}
	if(oldRuleB!=-1)
	{
		for(int i=moduleB+1; i<=n-1; ++i)
		{
			int newState;
			if(setRulesB[oldRuleB].operation!=0)
			{
				//cout<<"i "<<i<<endl;
				newState=counting(i,setRulesB[oldRuleB].operation,setRulesB[oldRuleB].number,module);
				matrix[1].push_back(newState);
			}
			else
			{
				if(setRulesB[oldRuleB].number!=0)
				{
					//cout<<setRulesB[oldRuleB].number<<endl;
					matrix[1].push_back(setRulesB[oldRuleB].number);
				}
				else
				{
					if(setRulesB[oldRuleB].flag==1 || setRulesB[oldRuleB].flag==0)
						matrix[1].push_back(i);
					else
						matrix[1].push_back(module);
					//matrix[1].push_back(i);
					
				}
			}
		}
		int newState;
		if(setRulesB[lastRuleB].operation!=0)
		{
			//cout<<"i "<<i<<endl;
			newState=counting(module,setRulesB[lastRuleB].operation,setRulesB[lastRuleB].number,module);
			matrix[1].push_back(newState);
		}
		else
		{
			if(setRulesB[lastRuleB].number!=0)
			{
				//cout<<setRulesB[lastRuleB].number<<endl;
				matrix[1].push_back(setRulesB[lastRuleB].number);
			}
			else
			{
				matrix[1].push_back(module);
			}
		}
	}
	else
	{
		for(int i=moduleB+1; i<=n; ++i)
		{
			int newState;
			if(setRulesB[lastRuleB].operation!=0)
			{
				//cout<<"i "<<i<<endl;
				newState=counting(i,setRulesB[lastRuleB].operation,setRulesB[lastRuleB].number,module);
				matrix[1].push_back(newState);
			}
			else
			{
				if(setRulesB[lastRuleB].number!=0)
				{
					//cout<<setRulesB[lastRuleB].number<<endl;
					matrix[1].push_back(setRulesB[lastRuleB].number);
				}
				else
				{
					if(setRulesB[lastRuleB].flag==1 || setRulesB[lastRuleB].flag==0)
						matrix[1].push_back(i);
					else
						matrix[1].push_back(module);
					//matrix[1].push_back(i);
				}
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
	secondA=secondB=0;
	int stateInterval,flagN,flagNA,flagNB;
	countStateA=countStateB=0;
    ifstream fd(config.c_str());
    string rule;
	int first,second,memOperationA,memOperationB,memNumericA,memNumericB,memLastRuleA,memLastRuleB,memFlagA,memFlagB;
	oldRuleA=oldRuleB=-1;
    while(getline(fd,rule))
    {
		flagN=0;
		stateInterval=0;
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
				if((atoi(number.c_str()))!=0)
                	first=atoi(number.c_str());
				else
					first=-1;
				//cout<<"first "<<first<<endl;
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
							if(rule[i]==' ')
								++i;
							//break;
						}
						else
						{
							number+=rule[i];
							++i;
						}
					}
					//cout<<rule[i]<<endl;
					if(rule[i]=='-')
					{
						//cout<<"!!"<<endl;
						++i;
						while(!(rule[i]>='0' && rule[i]<='9') && rule[i]!='}')
							++i;
						if(rule[i]=='}')
							break;
						number+=rule[i];
						if(stateInterval<atoi(number.c_str()))
							stateInterval=atoi(number.c_str());
						number="";
					}
					//cout<<"st "<<stateInterval<<endl;
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
                        if(rule[i]=='k' || rule[i]=='n')
                        {
							if(rule[i]=='n')
							{
								flagN=1;
								//cout<<"YYEE"<<endl;
								++i;
							}
							else
							{
								//cout<<"!!! "<<rule[1]<<" "<<rule[i]<<endl;
								flag=1;
								++i;
							}
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
		//cout<<"first "<<first<<" second "<<second<<endl;
        if(second!=-1)
		{
			//cout<<1<<endl;
			if(letter==0)
			{
				secondA=1;
				for(int l=first; l<second+1; ++l)
				{
					if(flag==1)
						setRulesA[l].flag=1;
					else
					{
						if(flagN==1)
							setRulesA[l].flag=2;
						else
							setRulesA[l].flag=0;
					}
					setRulesA[l].state=l;
					setRulesA[l].number=numeric;
					setRulesA[l].operation=operation;
					++countStateA;
				}
			}
			else
			{
				secondB=1;
				for(int l=first; l<second+1; ++l)
				{
					if(flag==1)
						setRulesB[l].flag=1;
					else
					{
						if(flagN==1)
							setRulesB[l].flag=2;
						else
							setRulesB[l].flag=0;
					}
					setRulesB[l].state=l;
					setRulesB[l].number=numeric;
					setRulesB[l].operation=operation;
					++countStateB;
				}
			}
		}
		else
		{
			//cout<<2<<endl;
			if(letter==0)
			{
				//cout<<"s"<<endl;
				if(stateInterval!=0)
				{
					if(flag==1)
					{
						setRulesA[first].flag=1;
						cout<<first<<endl;
					}
					else
					{
						if(flagN==1)
							setRulesA[first].flag=2;
						else
							setRulesA[first].flag=0;
					}
					setRulesA[first].state=first;
					setRulesA[first].number=numeric;
					setRulesA[first].operation=operation;
					++countStateA;
					lastRuleA=first;
					oldRuleA=first;
				}
				else
				{
					//cout<<"s"<<endl;
					if(first==-1)
					{
						if(flag==1)
						{
							memFlagA=1;
						}
						else
						{
							if(flagN==1)
								memFlagA=2;
							else
								memFlagA=0;
						}
						memOperationA=operation;
						memNumericA=numeric;
						memLastRuleA=1;
					}
					else
					{
						//cout<<4<<endl;
						if(flag==1)
						{
							setRulesA[first].flag=1;
							//cout<<first<<endl;
						}
						else
						{
							if(flagN==1)
								setRulesA[first].flag=2;
							else
								setRulesA[first].flag=0;
						}
						setRulesA[first].state=first;
						setRulesA[first].number=numeric;
						setRulesA[first].operation=operation;
						++countStateA;
						lastRuleA=first;
						//cout<<"f "<<first<<endl;
					}
				}
			}
			else
			{
				if(stateInterval!=0)
				{
					if(flag==1)
						setRulesB[first].flag=1;
					else
					{
						if(flagN==1)
							setRulesB[first].flag=2;
						else
							setRulesB[first].flag=0;
					}
					setRulesB[first].state=first;
					setRulesB[first].number=numeric;
					setRulesB[first].operation=operation;
					++countStateB;
					lastRuleB=first;
					oldRuleB=first;
				}
				else
				{
					if(first==-1)
					{
						if(flag==1)
							memFlagB=1;
						else
						{
							if(flagN==1)
								memFlagB=2;
							else
								memFlagB=0;
						}
						memOperationB=operation;
						memNumericB=numeric;
						memLastRuleB=1;
					}
					else
					{
						if(flag==1)
							setRulesB[first].flag=1;
						else
						{
							if(flagN==1)
								setRulesB[first].flag=2;
							else
								setRulesB[first].flag=0;
						}
						setRulesB[first].state=first;
						setRulesB[first].number=numeric;
						setRulesB[first].operation=operation;
						++countStateB;
						lastRuleB=first;
					}
				}
			}
		}
	}
	int module;
	moduleA=moduleB=-1;
	if(countStateA<countStateB)
		minCountState=countStateA;
	else
		minCountState=countStateB;
	//cout<<minCountState<<endl;
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
	if(memLastRuleA==1)
	{
		//cout<<"yes"<<endl;
		setRulesA[module].state=module;
		setRulesA[module].number=memNumericA;
		setRulesA[module].operation=memOperationA;
		setRulesA[module].flag=memFlagA;
		lastRuleA=module;
		//cout<<setRulesA[module].state<<" "<<setRulesA[module].number<<" "<<setRulesA[module].operation<<endl;
	}
	if(memLastRuleB==1)
	{
		setRulesB[module].state=module;
		setRulesB[module].number=memNumericB;
		setRulesB[module].operation=memOperationB;
		setRulesB[module].flag=memFlagB;
		lastRuleB=module;
	}
	//cout<<"!!! "<<setRulesA[1].state<<" "<<setRulesA[1].flag<<endl;
	/*for(int i=0; i<20; ++i)
	{
		cout<<"state "<<setRulesA[i].state<<endl;
		cout<<"number "<<setRulesA[i].number<<endl;
		cout<<"operation "<<setRulesA[i].operation<<endl;
		cout<<"lastRuleA "<<lastRuleA<<endl;
		cout<<"FLAG "<<setRulesA[i].flag<<endl;
	}*/
	generateAutomate(module);
    fd.close();
}
int main(int argc, char *mas[], char *envp[])
{
	string config(mas[1]);
	s.open("result");
    readFile(config);
    return 0;
}
