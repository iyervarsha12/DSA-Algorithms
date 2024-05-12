/*
	Implementation of Open addressing, taking null values to be -1 and delete flag to be -3. 
*/

#include <iostream>
#include <math.h>

#define nullval -1
#define deleteme -3
#define m 8

using namespace std;

class Openaddr
{
	//int m; //tablesize
	int arr[m];
	
	public:
	Openaddr(int num=0)
	{
		//m=num;
		for(int i=0;i<m;i++)
			arr[i]=nullval;
	}
	
	int hashfn1(int k)
	{
		return k%m;
	}
	
	int hashfn2(int k)
	{
		return (m-k)%m;
		//return floor(m*((int)(k*0.5))%1);
	}
	
	int hashfn(int k, int i)
	{
		int ans = (hashfn1(k) + i*hashfn2(k))%m;
		return ans;
	}
	
	bool insert(int k, int val) //false if no place to insert
	{
		int hashed=nullval;
		int i=0;
		while(i<m)
		{
			hashed = hashfn(k,i);
			if(arr[hashed]==nullval || arr[hashed]==deleteme)
			{
				//cout<<"\ninserted at pos "<<hashed;
				arr[hashed]=val;
				return true;
			}
			i++;
		}
		return false;
	}
	
	int search(int k) 
	{
		int i=0;
		int hashed=nullval;
		while(i<m)
		{
			hashed = hashfn(k,i);
			i++;
			
			if(arr[hashed]==deleteme)
				continue;
			
			if(arr[hashed]==nullval)
				return nullval;
			
			return arr[hashed];
		}
		return nullval;
	}
	
	int delet(int k) //item deleted or no such item
	{
		int i=0;
		int hashed=nullval;
		while(i<m)
		{
			hashed = hashfn(k,i);
			i++;
			if(hashed==nullval)
				return nullval;
			if(hashed==deleteme)
				continue;
			
			int t=arr[hashed];
			arr[hashed]=deleteme;
				return t;
		}
		return nullval;
	}	
};



int main()
{
	Openaddr h(8);
	cout<<h.insert(3,5);
	cout<<h.insert(2,9);
	cout<<h.insert(3,7);
	cout<<endl;
	cout<<h.search(3);
	cout<<h.delet(3);
	cout<<h.search(3);
	cout<<endl;
	
	return 0;
}
