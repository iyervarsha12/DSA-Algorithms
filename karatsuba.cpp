/*
	Implementation of the Karatsuba algorithm. 
*/
#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>

#include <sstream>
using namespace std;

int lengthequalandeven(string &s1, string &s2) //returns final size 
{
	if((s1.size()==s2.size())&&(s1.size()%2==0))
		return s1.size();
	
	if(s1.size()==s2.size())
	{
		s1.insert(0,"0");
		s2.insert(0,"0");
		return s1.size();
	}
	
	if(s1.size()>s2.size())
	{
		int s1size = s1.size();
		int s2size = s2.size();
		for(int i=1;i<=(s1size-s2size);i++)
			s2.insert(0,"0");
		if(s1.size()%2!=0)
		{
			s1.insert(0,"0");
			s2.insert(0,"0");
		}
		return s1.size();
	}
	
	if(s2.size()>s1.size())
	{
		int s1size = s1.size();
		int s2size = s2.size();
		for(int i=1;i<=(s2size-s1size);i++)
			s1.insert(0,"0");
		if(s2.size()%2!=0)
		{
			s1.insert(0,"0");
			s2.insert(0,"0");
		}
		return s2.size();
	}
	return -1;
}

long long int karatsuba(string s1,string s2) //answer can only be 19 bit max
{
	int n=lengthequalandeven(s1,s2);
	//cout<<endl<<s1<<"   "<<s2<<"  "<<n<<endl;
	string a,b,c,d;
	
	for(int i=0;i<s1.size();i++)
	{
		if(i<(s1.size()/2))
			a = a + s1.at(i);
		else b = b + s1.at(i);
	}
	
	for(int i=0;i<s2.size();i++)
	{
		if(i<(s2.size()/2))
			c = c + s2.at(i);
		else d = d + s2.at(i);
	}
	/*
	long long int s1l=atoi(b.c_str());
	long long int s1h=atoi(a.c_str());
	long long int s2l=atoi(d.c_str());
	long long int s2h=atoi(c.c_str());
	*/
	long long int s1l;
	long long int s1h;
	long long int s2l;
	long long int s2h;
	stringstream i(a);
	stringstream j(b);
	stringstream k(c);
	stringstream l(d);
	i>>s1h;
	j>>s1l;
	k>>s2h;
	l>>s2l;
	long long int c0 = s1l*s2l;
	long long int c1 = s1h*s2h;
	long long int c2 = (s1l+s1h)*(s2l+s2h)-c0-c1;
	long long int ans=(long long int)c1*((long long int)pow(10,n))+c2*((long long int)pow(10,n/2))+c0;
	return ans;
	
}

void computesquare(int a, long double xi)
{
	long double xi2 = (xi +(a/xi))/2;
	cout<<(long double)xi2<<endl;
	if(xi2==sqrt(2))
		return;
	computesquare(a,xi2);
	
}



int main()
{
	
	string s1="54312000";
	string s2="16123455600";
	cout<<s1<<"*"<<s2<<":";
	//cout<<"\nVia normal multiplication: "<<(long long int)((long long int)(atoi(s1.c_str()))*(long long int)(atoi(s2.c_str())));
	cout<<"\nVia karatsuba: "<<(long long int)(karatsuba(s1,s2));
	
	/*
	int a=2;
	computesquare(a,1);
	*/
	
	return 0;
}