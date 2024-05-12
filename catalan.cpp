/*
	Implementation of catalan numbers.
*/

#include <iostream>
using namespace std;

unsigned long int arr[20];

unsigned long int c_calculator(int n)
{
	if(n<0)
		return 0;
	
	if(n==0)
	{
		arr[0]=1;
		return 1;
	}
	//n--;
	unsigned long int ans=0;
	for(int i=0;i<=n-1;i++)
	{
		ans = ans + arr[i]*arr[n-1-i];
		//ans = ans + c_calculator(i) * c_calculator(n-1-i);
		arr[n]=ans;
	}
	return ans;
}


int main()
{
	for(int i=0;i<20;i++)
		arr[i]=0;
	
	for(int i=0;i<20;i++)
		cout<<(unsigned long int) c_calculator(i)<<endl;
	return 0;
}