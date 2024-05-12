/*
	Implementation of hasing with chaining, with different hash functions coded.
	Division method, multiplication method, and midsquare method.
	This implementation grows the table to twice its size if the number of elements exceed number of table entries.
	It also shrinks the table to half its size if the number of elements is lesser than 1/4th the number of table entries. 
*/

#include <iostream>
#include <vector>
#include <list>
#include <iterator>

#include <math.h> //for multiplication method hashing and midsquare method
#include <cmath>
using namespace std;

class Hash
{
	int numberofbuckets;
	int numberofelements;
	
	vector<list<int>> table;
	
	
	
	public:
	Hash(int n)
	{
		numberofbuckets=n;
		numberofelements=0;
		list<int> l;
		for(int i=0;i<n;i++)
			table.push_back(l);

	}
	
	int retbucket() {return numberofbuckets;}
	int retelt() {return numberofelements;}


	int hashfn(int elt)
	{
		
		//division method
		return elt%numberofbuckets;
		
		//multiplication method: h(k) = floor(  n( kA mod 1 ) ),A between 0 and 1
		//return floor(numberofbuckets * ((int)(elt*0.5))%1);
		
		/*
		//midsquare method: It involves squaring the value of the key and then extracting the middle r digits as the hash value. r: no of digits to store bucketno
		int sq = elt*elt;
		int r = floor(log10(numberofbuckets-1) + 1); //counting number of digits
		
		int noofdigitsinsq = floor(log10(sq) + 1);
		sq = fmod(sq,pow(10,noofdigitsinsq-ceil(r/2)));
		sq = floor(sq * pow(0.1,ceil(r/2)));
		cout<<sq;
		return sq;
		
		*/
		/*
		//(a*elt)mod 2^64 >> (64-r)
		int w=64;
		int r=log(numberofbuckets);
		int a = (pow(2,w) + pow(2,w-1))/2;
		if(a%2==0) a++;
		int expr = fmod((a*elt),(pow(2,w)));
		cout<<(expr>>(w-r))<<endl;
		return (abs(expr>>(w-r)));
		*/
		
		
	}
	
	bool shrinktable()
	{
		if(numberofelements <= numberofbuckets/4)
		{
			
			cout<<"\bBefore:\n";
			printhashtable();
			cout<<"\nShrinking table...\n";
			vector<int> to_be_added;
			for(int i=0;i<numberofbuckets;i++)
			{
				list <int> :: iterator it; 
				for(it = ((table.at(i)).begin()); it != (table.at(i)).end(); ++it) 
				{
					to_be_added.push_back(*it);
				}
			}
			table.clear();
			numberofbuckets=numberofbuckets/2;
			list<int> l;
			for(int i=0;i<numberofbuckets;i++)
				table.push_back(l);
			
			for(int i=0;i<to_be_added.size();i++)
				insert_elt_grow(to_be_added.at(i));
			printhashtable();
			return true;
		}
		else return false;
	}
	
	
	bool growtable()
	{
		if(numberofelements>numberofbuckets)
		{
			cout<<"\bBefore:\n";
			printhashtable();
			cout<<"\nGrowing table...\n";
			vector<int> to_be_added;
			for(int i=0;i<numberofbuckets;i++)
			{
				list <int> :: iterator it; 
				for(it = ((table.at(i)).begin()); it != (table.at(i)).end(); ++it) 
				{
					to_be_added.push_back(*it);
				}
			}
			table.clear();
			numberofbuckets=numberofbuckets*2;
			list<int> l;
			for(int i=0;i<numberofbuckets;i++)
				table.push_back(l);
			
			for(int i=0;i<to_be_added.size();i++)
				insert_elt_grow(to_be_added.at(i));
			
			printhashtable();
			return true;
		}
		else return false;
	}
	
	void insert_elt_grow(int elt)
	{
		int hashed = hashfn(elt);
		(table.at(hashed)).push_back(elt);
	}
	
	
	
	void insert_element(int elt)
	{
		int hashed = hashfn(elt);
		(table.at(hashed)).push_back(elt);
		numberofelements++;
		if(growtable())
			cout<<"\nGrows at element "<<elt<<endl;
	}
	
	bool delete_element(int elt)
	{
		int hashed=hashfn(elt);
		list <int> :: iterator it; 
		for(it = (table.at(hashed)).begin(); it != (table.at(hashed)).end(); ++it) 
		{
			if(*it == elt)
			{
				(table.at(hashed)).erase(it);
				numberofelements--;
				if(shrinktable())
					cout<<"\nShrinks at element "<<elt<<endl;
				return true;
			}
		}
	
		return false;
	}
	
	bool ispresent(int elt)
	{
		int hashed=hashfn(elt);
		list <int> :: iterator it; 
		for(it = (table.at(hashed)).begin(); it != (table.at(hashed)).end(); ++it) 
		{
			if(*it == elt)
			{
				return true;
			}
		}
	
		return false;
	}
	
	void printhashtable()
	{
		for(int i=0;i<numberofbuckets;i++)
		{
			list <int> :: iterator it; 
			int flag=0;
		for(it = ((table.at(i)).begin()); it != (table.at(i)).end(); ++it) 
		{
			
			cout<<(*it)<<" --> ";
			if((*it)!=0)
				flag=1;
		}
		if(flag==1) cout<<"\n";
		}
	}

};


int main()
{
	//78,97,65,55,11,32,80,18,87,85
	vector<int> input{78,97,65,55,11};
	Hash h(4);
	for(int i=0;i<input.size();i++)
	{
		h.insert_element(input.at(i));

	}
	h.delete_element(78);
	h.delete_element(97);
	h.delete_element(55);
	h.delete_element(11);
	h.insert_element(85);
	h.insert_element(20);
	/*
	cout<<"\nElement 65 present? "<<h.ispresent(65);
	h.delete_element(65);
	cout<<"\nDeleted elt 65. Can delete element 100? "<<h.delete_element(100);
	cout<<"\nElement 65 present? "<<h.ispresent(65) ;
	*/
	return 0;
}