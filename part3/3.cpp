//Находит кратчайшее слово, которое сжимает подаваемое множество до множества заданной мощности. 

#include <iostream>
#include <cmath>
#include<iostream>
#include <vector>
#include <cmath>
#include<map>
#include <queue>
#include<fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

void function(vector<int>matrix[2],string words,vector<int>states)
{
	string word;
	ifstream fd(words.c_str());
	int flag;
	int power=states[states.size()-1];
	while(getline(fd,word))
	{
		vector<int>newState;
		flag=0;
		for(int i=0; i<states.size()-1; ++i)
		{
			queue<int>Q;
            int top,result;
			top=states[i];
			Q.push(top);
			//---------------------------------------------------------
			//here it is necessary to remove the unit if words.txt file
			//---------------------------------------------------------
			for(int j=0; j<=word.length()-1; ++j)
			{
				int position,new_pos;
				position=Q.front();
				Q.pop();
				new_pos=matrix[word[j]-48][position-1];
				cout<<word[j]-48<<" "<<position<<" "<<new_pos<<endl;
				Q.push(new_pos);
				result=new_pos;
			}
			newState.push_back(result);
		}
		cout<<"word "<<word<<endl;
		for(int i=0; i<newState.size(); ++i)
			cout<<newState[i];
		cout<<endl;
		int difference=0;
		for(int i=0; i<matrix[0].size(); ++i)
		{
			difference=1;
			for(int j=0; j<matrix[0].size(); ++j)
			{
				if(i!=j && newState[i]!=newState[j])
				{
					++difference;
				}
			}
		}
		if(difference==power)
		{
			cout<<"For automatic: "<<endl;
			for(int i=0; i<2; ++i)
			{
				for(int j=0; j<matrix[0].size(); ++j)
					cout<<matrix[i][j];
				cout<<endl;
			}
			cout<<"Synchronizing word is "<<word<<endl<<endl;
			break;
		}
	}
}

void readFile(string config,string words,vector<int>states)
{
	ifstream fin(config.c_str());
	string str;
	int count=0;
	vector<int> matrix[2];
	while(getline(fin,str))
	{
		cout<<1<<endl;
		++count;
		if(count==1)
		{
			for(int i=0; i<str.length(); ++i)
			{
				matrix[0].push_back(str[i]-48);
			}
		}
		if(count==2)
		{
			count=0;
			for(int i=0; i<str.length(); ++i)
				matrix[1].push_back(str[i]-48);
			function(matrix,words,states);
			matrix[0].clear();
			matrix[1].clear();
		}
	}
		
}
vector<int> readSet(string set)
{
	ifstream fd (set.c_str());
	string str;
	vector<int> states;
	int power;
	int flag=0;
	int count=0;
	while(getline(fd,str))
	{
		if(flag==1)
		{
			string num="";
			for(int i=0; i<str.length(); ++i)
			{
				while(str[i]==' ' && i<str.length())
					++i;
				num+=str[i];
			}
			power=atoi(num.c_str());
			break;
		}
		for(int i=0; i<str.length(); ++i)
		{
			while(str[i]==' ' && i<str.length())
				++i;
			if(str[i]=='{')
				++i;
			if(str[i]=='}')
			{
				break;
			}
			
			string num="";
			while(str[i]!=',' && str[i]!='}' && i<str.length())
			{
				if(str[i]==' ')
				{
					++i;
					continue;
				}
				num+=str[i];
				++i;
			}
			int number;
			number=atoi(num.c_str());
			states.push_back(number);
			num="";
		}
		
	}
	return states;
	
}
int main(int argc, char *mas[], char *envp[])
{
	string config(mas[1]);
	string words(mas[2]);
	string set(mas[3]);
	vector<int>states=readSet(set);
	readFile(config,words,states);
	return 0;
}
