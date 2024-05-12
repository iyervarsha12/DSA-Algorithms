/*
	Implementation of the text justification problem using dynamic programming. 
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define pagewidth 10
#define INF 0x3f3f3f3f

int badness(int i,int j)
{
	int totalwidth = j-i+1;
	if(totalwidth > pagewidth)
		return INF;

	int ans = (pagewidth-totalwidth)*(pagewidth-totalwidth)*(pagewidth-totalwidth);
	return ans;
}


int textjustification(string str, vector <int> s)
{
	map <int, pair<int,int> > dp;
	dp[str.size()-1].first = 0;
	dp[str.size()-1].second = -1;
	//for(int i=str.size()-2;i>=0;i--)
	for(int t=s.size()-2;t>=0;t--)
	{
		int i=s[t];
		vector <pair<int,int> > choices;
		
		int min=INF;
		int index;
		
		int parent;
		//j is where next line begins. >i but also in s. j=i+1 to n

		for(int j:s)
		{
			if(j<=i) continue;
			
			choices.push_back(make_pair(dp[j].first + badness(i,j) , j));
		}
		
		
		for(int k=0;k<choices.size();k++)
		{
			if(min>choices[k].first)
			{
				min=choices[k].first;
				index=choices[k].second;
			}
		}
		//cout<<i<<" "<<index<<":"<<min<<endl;
		dp[i].first=min;
		dp[i].second = index;
	}
	int i=0;
	while(dp[i].second!=-1)
	{
		//cout<<i<<"("<<str[i]<<")"<<" to "<<dp[i].second <<"("<<str[dp[i].second ]<<")"<<" is one line."<<endl;
		cout<<endl;
		for(int t=i;t<dp[i].second;t++)
			cout<<str[t];
		
		
		
		i=dp[i].second;
		
	}
	cout<<str[str.size()-1];
	
	return dp[0].first;
	
}



int main()
{
	//			0123456789012345678901234
	string str="bla bla bla bla blablabla";
	//string str="Geeks for Geeks presents word wrap problem";
	vector <int> s={0}; //has all places a new word starts. word will go from s[i] to s[i+1]-2. //-2 for space and current beginning
	for(int i=0;i<str.size();i++)
	{
		if(str[i]==' ')
			s.push_back(i+1);
	}
	s.push_back(str.size()-1);
	
	textjustification(str,s);
	
	
	return 0;
}