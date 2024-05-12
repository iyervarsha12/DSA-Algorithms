/*
	Implementation of Dijkstra algorithm using a minheap as a queue.
*/

#include <iostream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

//Dijkstra using a minheap for queue.

class minheap //key of node <= key of children
{
	public:
	int n_size;
	vector <vector<int> > arr;
	
	
	void minheap_init(int no, int d[])
	{
		n_size=no;

		for(int i=0;i<no;i++)
		{
			vector <int> temp;
			temp.push_back(i);
			temp.push_back(d[i]);
			arr.push_back(temp);
		}
		
	}
	
	void heapify(int n, int i) //i is parent,  makes subtree with i as root into a min_heap recursively
	{
	int largest = i;
	int left=2*i+1;
	int right=2*i+2;

	if((left<n)&&(arr[left][1]<arr[largest][1]))
		largest = left;
	if((right<n)&&(arr[right][1]<arr[largest][1]))
		largest = right;
	
	if(largest==i)
		return;
	
	else //largest is no longer root
	{
		int temp1 = arr[largest][0];
		int temp2 = arr[largest][1];
		
		arr[largest][0]=arr[i][0];
		arr[largest][1]=arr[i][1];
		arr[i][0]=temp1;
		arr[i][1]=temp2;
		heapify(n,largest); 
	}
	}
	int extract_min()
	{
		if(n_size<=0)
			return -1;
		for(int i=(n_size/2) -1;i>=0;i--) //build maxheap
			heapify(n_size,i);
		
		int temp1 = arr[0][0];
		int temp2 = arr[0][1];
		
		int i=n_size-1;
		arr[0][0]=arr[i][0];
		arr[0][1]=arr[i][1];
		arr[i][0]=temp1;
		arr[i][1]=temp2;
		
		heapify(i,0);
		n_size--;
		return arr[i][0];
	}
		
};


class dijkstra
{
	int V;
	map<int,vector<int> > adj; //has vertex as key, adjacent elements as value
	map< vector<int>, int > weight; //weight of given edge
	
	int *d;
	int *parent;
	
	minheap q;
	
	
	public:
	dijkstra(int vno)
	{
		V=vno;
		d = new int[vno]; 
		parent = new int[vno];
		
	}
	
	bool insertedge(int v, int u, int wvu) 
	{
		if((v<0 || v>V-1)||(u<0 || u>V-1))
			return false;
		
		adj[v].push_back(u); //at key v, insert u
		
		vector <int> temp;
		temp.push_back(v);
		temp.push_back(u);
		weight[temp]=wvu;
		
		return true;
	}
	
	void initialisation(int s)
	{
		for(int i=0;i<V;i++)
		{
			d[i]=numeric_limits<int>::max();
			parent[i]=-1;
		}
		d[s]=0;
		
		q.minheap_init(V, d);
	}
	
	
	void dijkstra_algorithm(int s)
	{
		initialisation(s);
		while(1) //change condition
		{
			int u=q.extract_min();
			if(u<0)
				return;
			for(int v: adj[u]) 
			{
				vector <int> temp;
				temp.push_back(u);
				temp.push_back(v);
				if(d[v]>d[u]+weight[temp])
				{
					d[v]=d[u]+weight[temp];
					
					vector <int> temp2;
					temp2.push_back(v);
					temp2.push_back(d[v]);
					int index=-1;
					for(int i=0;i<q.n_size;i++)
						if(q.arr[i][0]==v)
						{
							q.arr[i]=temp2;
						}
					parent[v]=u;
				}
			}
		}	
	}
	
	void printshortestpath(int s, int u)
	{
		if(d[u]==numeric_limits<int>::max() || d[u]<0)
			return;
		cout<<"Path length is "<<d[u]<<endl;
		cout<<u<<"<-";
		while(parent[u]!=-1)
		{
			cout<<parent[u]<<"<-";
			u=parent[u];
		}
		cout<<endl;
		
	}
	
	~dijkstra()
	{
		delete[] d;
		delete[] parent;
	}	
};


//Dijkstra using queue as array
/*
class dijkstra
{
	int V;
	map<int,vector<int> > adj; //has vertex as key, adjacent elements as value
	map< vector<int>, int > weight; //weight of given edge
	
	int *Q;
	int *d;
	int *parent;
	
	public:
	dijkstra(int vno)
	{
		V=vno;
		Q = new int[vno]; //has all vertices to process
		d = new int[vno]; 
		parent = new int[vno];
	}
	
	bool insertedge(int v, int u, int wvu) 
	{
		if((v<0 || v>V-1)||(u<0 || u>V-1))
			return false;
		
		adj[v].push_back(u); //at key v, insert u
		
		vector <int> temp;
		temp.push_back(v);
		temp.push_back(u);
		weight[temp]=wvu;
		
		return true;
	}
	
	void initialisation(int s)
	{
		for(int i=0;i<V;i++)
		{
			Q[i]=i;
			d[i]=numeric_limits<int>::max();
			parent[i]=-1;
		}
		d[s]=0;
	}
	
	int extract_min()
	{
		int min=numeric_limits<int>::max();
		int index=-1;
		for(int i=0;i<V;i++)
		{
			if((Q[i]!=-1)&&(min>d[Q[i]]))
			{
				min=d[Q[i]];
				index=i;
			}
		}
		Q[index]=-1;
		return index;
	}
	
	bool check()
	{
		for(int i=0;i<V;i++)
			if(Q[i]!=-1)
				return true;
			
		return false;
	}
	
	void dijkstra_algorithm(int s)
	{
		initialisation(s);
		while(check()) //change condition
		{
			int u=extract_min();
			if(u<0)
				return;
			for(int v: adj[u]) 
			{
				vector <int> temp;
				temp.push_back(u);
				temp.push_back(v);
				if(d[v]>d[u]+weight[temp])
				{
					d[v]=d[u]+weight[temp];
					parent[v]=u;
				}
			}
		}	
	}
	
	void printshortestpath(int s, int u)
	{
		if(d[u]==numeric_limits<int>::max()|| d[u]<0)
			return;
		cout<<"Path length is "<<d[u]<<endl;
		cout<<u<<"<-";
		while(parent[u]!=-1)
		{
			cout<<parent[u]<<"<-";
			u=parent[u];
		}
		cout<<endl;
		
	}
	
	
	~dijkstra()
	{
		delete[] Q;
		delete[] d;
		delete[] parent;
	}	
};
*/

int main()
{
	dijkstra d(5);
	d.insertedge(0,1,10);
	d.insertedge(1,3,2);
	d.insertedge(0,2,3);
	d.insertedge(1,2,1);
	d.insertedge(2,1,4);
	d.insertedge(2,3,8);
	d.insertedge(2,4,2);
	d.insertedge(3,4,7);
	d.insertedge(4,3,9);
	
	d.dijkstra_algorithm(0);
	d.printshortestpath(0,4);
	
	return 0;
}