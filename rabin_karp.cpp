/*
	Implementation of the Rabin-Carp algorithm, which finds if a substring is present in a bigger string using the method of hashing.
*/

#include <iostream>
#include <string.h>

using namespace std;

int hashfn(string s)
{
	int ans=0;
	for(int i=0;i<s.size();i++)
		ans=ans+s.at(i);
	
	return ans;
}

int changehash(char first, char last, int oldhashvalue)
{
	return oldhashvalue + last - first;
}

int subsetofstring(string input, string tofind,int pos) //returns -1 if not found
{
	if(input.size()<tofind.size())
		return -1;
	
	if(pos + tofind.size() >= input.size())
		return -1;
	
	int tofind_hashed = hashfn(tofind);
	string temp;
	for(int i=0;i<tofind.size();i++)
	{
		temp=temp+input.at(pos+i);
	}
	int input_hashed = hashfn(temp);
	
	for(int i=pos;i<=input.size()-tofind.size();i++)
	{
		if(tofind_hashed == input_hashed) //manage collisions here
		{
			string iseq;
			for(int t=0;(t<tofind.size())&&(t+i<input.size());t++)
				iseq = iseq + input.at(i+t);
			if(iseq.compare(tofind)==0)
				return i;
		}
		if(i+tofind.size() <input.size())
			input_hashed = changehash(input.at(i),input.at(i+tofind.size()),input_hashed);
	}
	
	return -1;
	
}

void printinstance(string input, string tofind, int pos)
{
	
		cout<<"\nFound at position "<<pos<<" at the instance: ";
		string temp;
		temp.append("...");
		int t=pos-2*tofind.size();
		if(t<0) t=0;
		for(int i=t;(i<pos+4*tofind.size())&&(i<input.size());i++)
		{
			if((i<pos)||(i>=pos+tofind.size()))
				temp = temp + input.at(i);
			else
			{
				temp = temp + (char) toupper(input.at(i));
			}
		}
		temp.append("...");
		cout<<temp;
		
}

void ispresent(string input, string tofind)
{
	cout<<"\nIn the string: '"<<input<<"' :";
	int flag=0;
	int pos=0;
	cout<<"\nThe string '"<<tofind<<"' is:";
	while(1)
	{
		pos=subsetofstring(input,tofind,pos);
		if(pos==-1)
			break;
		printinstance(input,tofind,pos);
		pos++;
		flag=1;
	}
	if(flag==0)
		cout<<"not found!";
	
}


int main()
{
	cout<<"\nCase sensitive wordfinder\n";
	
	string input("the quick brown fox jumps over the lazy dog");
	//string input("A typical example is an aircraft’s software system, or a car’s software system. Let us mention only a few tasks in the car’s software system – the speedometer and the airbag function. The system designer is interested in ensuring that all parts of the system work at all times. However, that is not always possible. There are many issues that pop up – when faced with a choice between two functions to be executed, which has to be chosen? Criticality of the airbag function is intuitively much higher than the speedometer. However, the more tasks there are, the harder it becomes to clearly distinguish which criticalities each should belong to, and to decide how many criticality levels should be present.  Also, what if the localised parts necessary to run the airbag function is damaged? The only way to reduce such chances is to have duplicate units adhering to this function elsewhere.  In other words, how do we resolve the conflicting requirements between partitioning for safety assurance (in case some units fail), and sharing for efficient resource usage?");
	
	
	string tofind("the");
	
	ispresent(input,tofind);
	
	return 0;
}