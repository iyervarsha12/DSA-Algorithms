/*
	Implementation of the Bellman-ford algorithm.
*/

#include <iostream>
#include <map>
#include <iterator>

using namespace std;

# define INF 0x3f3f3f3f 

class bf_graph
{
	int V;
	map < pair<int,int>, int > adj;
	int *d;
	int *parent;
	
	public:
	
	bf_graph(int V)
	{
		this->V=V;
		d=new int[V];
		parent=new int[V];
	}
	
	int insertedge(int u, int v, int w)
	{
		adj[ make_pair(u,v) ] = w;
		
	}
	
	void init(int s)
	{
		for(int i=0;i<V;i++)
		{
			d[i]=INF;
			parent[i]=-1;
		}
		d[s]=0;
	}
	
	bool bellmanford(int s) //returns false if any negative cycle is present. Order VE+E
	{
		init(s);
		map< pair<int,int>, int >::iterator it;
		for(int i=0;i<V;i++) //Order V
		{
			for(it=adj.begin();it!=adj.end();it++) //order E
			{
				//pair is it->first
				//weight is it->second
				pair <int,int> temp = it->first;
				int u=temp.first;
				int v=temp.second;
				int weight = it->second;
				
				if(d[v]>d[u]+weight)
				{
					d[v]=d[u]+weight;
					parent[v]=u;
				}
			}
		}
		
		for(it=adj.begin();it!=adj.end();it++) //order E
		{
			//pair is it->first
			//weight is it->second
			pair <int,int> temp = it->first;
			int u=temp.first;
			int v=temp.second;
			int weight = it->second;
			
			if(d[v]>d[u]+weight)
			{
				printdistances();
				return false;
			}
		}
		printdistances();
		return true;	
	}
	
	void printdistances()
	{
		cout<<"Vertex\tDistance from source\n";
		for(int i=0;i<V;i++)
		{
			if(d[i]>=0)
				cout<<i<<"\t"<<d[i]<<endl;	
			else cout<<i<<"\t"<<"Not defined"<<endl;
		}
	}
	
	
};



int main()
{
	/*
	bf_graph d(5);
	d.insertedge(0,1,10);
	d.insertedge(1,3,2);
	d.insertedge(0,2,3);
	d.insertedge(1,2,1);
	d.insertedge(2,1,4);
	d.insertedge(2,3,8);
	d.insertedge(2,4,2);
	d.insertedge(3,4,7);
	d.insertedge(4,3,9);
	cout<<d.bellmanford(0);
	*/
	
	bf_graph bf(5);
	bf.insertedge(0,1,2);
	bf.insertedge(1,2,3);
	bf.insertedge(2,3,-1);
	bf.insertedge(3,4,-1);
	bf.insertedge(4,2,5);
	cout<<bf.bellmanford(0);
	
	
	return 0;
}