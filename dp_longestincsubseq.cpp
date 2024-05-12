/*
	Implementation of the shortest subsequence problem using dynamic programming. 
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std; 

int shortestsubseq(int arr[],int n)
{
	map <int, pair <int,int> > dp; //dp[i] = (shortest subseq starting i, parent pointer)
	
	for(int i=n-1;i>=0;i--)
	{
		int parent=-1;
		vector <pair<int,int> > choices={make_pair(1,i)};
		for(int j=i+1;j<n;j++)
		{
			if(arr[j]>arr[i])
			{
				choices.push_back(make_pair(dp[j].first + 1,j));
				
			}
		}
		int max=choices[0].first;
		for(int k=0;k<choices.size();k++)
			if(max<choices[k].first)
			{
				max=choices[k].first;
				parent = choices[k].second;
			}
		dp[i]=make_pair(max,parent);
		
	}
	int max=0;
	int index=-1;
	for(int k=0;k<dp.size();k++)
	{
		if(max<dp[k].first) //finding max of dp: from where is it best to start?
		{
			max=dp[k].first;	
			index=k;
		}
	}			
	cout<<arr[index]<<" ";

	while(dp[index].second!=-1 && index<n)
	{
		cout<<arr[dp[index].second]<<" ";
		index = dp[index].second;
	}
	
	cout<<endl;

	return max;
	
}

int main()
{
	int n=8; //8,3,5,2,4,9,7,11
	int arr[]={8,7,6,5,4,3,2,1};
	cout<<shortestsubseq(arr,n);
	
	return 0;
}