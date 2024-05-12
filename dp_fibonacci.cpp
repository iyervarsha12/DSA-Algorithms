/*
	Implementation of Fibonacci sequence via Dynamic programming.
	Code is provided for both the bottom-up algorithm and the memoization approach.
*/

#include <iostream>
#include <map>

using namespace std;

//using bottom-up algorithm with only 2 elt
int fiboBottomUp(int n) //simple topological sort approach
{
	int arr[2];
	for (int k=1;k<=n;k++)
	{
		if(k<=2)
		{
			arr[0]=1;
			arr[1]=1;
		}
		else 
		{
			//arr[0] contains n-1, arr[1] has n-2
			//we need arr[0] to have n, arr[1] to have n-1
			int temp=arr[0]; //n-1
			arr[0]=arr[0]+arr[1];
			arr[1]=temp;
			
		}
	}
	
	return arr[0];
}

//using memoization
map<int,int> memo; //default init for key that does not exist is 0.
int fiboMemoization(int n)
{
	if(memo[n]!=0)
		return memo[n];
	if((n==1)||(n==2))
	{
		memo[n]=1;
		return 1;
	}
	int f= fib(n-1)+fib(n-2);
	memo[n]=f;
	return f;
}


int main()
{
	int n;
	cin>>n;
	cout<<fiboBottomUp(n);
	cout<<fiboMemoization(n);
	return 0;
}