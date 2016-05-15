//Находит кратчайшее синхронизируемое слово для автоматов

#include <iostream>
#include <cmath>
#include<iostream>
#include <vector>
#include <cmath>
#include<map>
#include <queue>
#include<fstream>
using namespace std;

void function(vector<int>matrix[2],string words)
{
	string word;
	ifstream fd(words.c_str());
	int flag;
	while(getline(fd,word))
	{
		vector<int>newState;
		flag=0;
		for(int i=1; i<=matrix[0].size(); ++i)
		{
			queue<int>Q;
            int top,result;
			top=i;
			Q.push(top);
			//cout<<word<<" "<<word.length()<<endl;
			for(int j=0; j<word.length()-1; ++j)
			{
				//cout<<j<<endl;
				int position,new_pos;
				position=Q.front();
				Q.pop();
				new_pos=matrix[word[j]-48][position-1];
				//cout<<word[j]-48<<" "<<position<<" "<<new_pos<<endl;
				Q.push(new_pos);
				result=new_pos;
			}
			newState.push_back(result);
		}
		/*for(int i=0; i<4; ++i)
			cout<<newState[i];
		cout<<endl;*/
		int matches=0;
		for(int i=0; i<matrix[0].size(); ++i)
		{
			matches=0;
			for(int j=0; j<matrix[0].size(); ++j)
			{
				if(i!=j && newState[i]==newState[j])
				{
					++matches;
				}
			}
		}
		//cout<<"mat "<<matches<<endl;
		if(matches==matrix[0].size()-1)
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

void readFile(string config,string words)
{
	ifstream fin(config.c_str());
	string str;
	int count=0;
	vector<int> matrix[2];
	while(getline(fin,str))
	{
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
			function(matrix,words);
			matrix[0].clear();
			matrix[1].clear();
		}
	}
		
}
int main(int argc, char *mas[], char *envp[])
{
	string config(mas[1]);
	string words(mas[2]);
	readFile(config,words);
	return 0;
}
