/*
	Implementation of shortest path problem using dynamic programming.
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;
# define INF 0x3f3f3f3f 
  
//make cyclic acyclic. 0 to V-1 copies of vertices
class shortestpath  
{
	int V;
	int orgv;
	vector <vector <pair<int,int> > > adj; //adj[u] = (v,w)
	map< vector<int>, int > delta; //(s,v,level)--delta(s,v)
	
	//0		1		2		...ith
	//u 	u+orgv	u+2*orgv...u+i*orgv
	
	public:
	shortestpath(int V)
	{
		this->V = V*V;
		orgv=V;
		vector <vector <pair<int,int> > > adj2(V*V);//is just empty.
		adj=adj2;
	}
	
	void insertedge(int u,int v,int w)
	{
		//u, u+orgv, u+2*orgv....
		for(i=0;i<orgv-1;i=i++) //orgv-1 because end boundary mapping not needed
			adj[v+orgv+i*orgv].push_back(make_pair(u+i*orgv,w)); //u[0]--->v[1],u[1]--->v[2]...
	}
	
	int dag_shortestpath(int s, int v, int level=orgv-1)
	{
		
		if(level<0)
			return 0;
		
		if(s==v)
			return 0;
		
		
		int min=INF;
		for(int i=0;i<adj[v].size();i++)
		{
			int weight = adj[v][i].second;
			int u = adj[v][i].first;

			vector <int> temp {s,v,level};

			if(delta.find(temp)==delta.end()) //does not exist
				delta[temp] =dag_shortestpath(s,u);
			
			vector <int> temp2 {s,u,level-1};
			if(min>delta[temp2] + weight)
				min=delta[temp2] + weight;
		}
		delta[{s,v,level}] = min;
		return min;	
	}
	
	
	
};


/*
//works for acyclic positive weights
class shortestpath
{
	int V;
	vector <vector <pair<int,int> > > adj; //adj[u] = (v,w)
	map< pair<int,int>, int > delta; //(s,v)--delta(s,v)
	
	public: 
	
	shortestpath(int V)
	{
		this->V=V;
		vector <vector <pair<int,int> > > adj2(V);//is just empty.
		adj=adj2;
	}
	
	void insertedge(int u,int v,int w)
	{
		adj[v].push_back(make_pair(u,w)); //u--->v
		
	}
	
	int dag_shortestpath(int s,int v) //source, destination
	{
		//delta[make_pair(s,v)] = min(delta[make_pair(s,u)] + weight);
		//u is all vertexes leading to next vertex v
		if(s==v)
			return 0;
		
		
		int min=INF;
		for(int i=0;i<adj[v].size();i++)
		{
			int weight = adj[v][i].second;
			int u = adj[v][i].first;

			if(delta.find(make_pair(s,u))==delta.end()) //does not exist
				delta[make_pair(s,u)] =dag_shortestpath(s,u);
			
			if(min>delta[make_pair(s,u)] + weight)
				min=delta[make_pair(s,u)] + weight;

		}
		delta[make_pair(s,v)] = min;
		return min;
	}
	
};
*/


int main()
{
	shortestpath s(4);
	s.insertedge(0,1,1);
	s.insertedge(0,2,2);
	s.insertedge(2,1,2);
	s.insertedge(1,3,9);
	s.insertedge(2,3,1);
	cout<<s.dag_shortestpath(0,3,3);
	return 0;
}