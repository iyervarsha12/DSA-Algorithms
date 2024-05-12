/*
	Implementation of the breadth first search algorithm on a graph.
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class graph_bfs
{
	int V; //number of vertices
	bool directed;//true if directed, false if not
	
	map<int,int> level; //vertex key, level value
	map<int,int> parent; //vertex key, parent vertex value
	map<int,vector<int> > adj; //has vertex as key, adjacent elements as value
	
	
	public:
	graph_bfs(int vertices, bool dir)
	{
		V=vertices;
		directed = dir;
	}
	
	bool check_level(int v) //true if not in level map.
	{ 
    // Key is not present 
		if (level.find(v) == level.end()) 
			return false; 
  
		return true; 
	} 
	
	bool insertedge(int v, int u) //v->u for directed, v--u for undirected(no need to enter u--v here)
	{
		if((v<0 || v>V-1)||(u<0 || u>V-1))
			return false;
		
		adj[v].push_back(u); //at key v, insert u
		if(!directed)
			adj[u].push_back(v);
		return true;
		
		
	}
	
	bool bfs(int s, int reachable) 
	{
		if((s<0 || s>V-1)||(reachable<-1 || reachable>V-1))
			return false;
		
		level.clear();
		parent.clear();
		
		level.insert(pair<int,int>(s,0));
		parent.insert(pair<int,int>(s,-1));
		int i=1; //current level
		vector <int> frontier;
		frontier.push_back(s);
		vector <int> next;
		
		while(frontier.size()>0)
		{
			next.clear();
			for(int u: frontier)
			{
				
				for(int v: adj[u]) 
				{
					if(!check_level(v)) //v is not present in level
					{
						level.insert(pair<int,int> (v,i));
						parent.insert(pair<int,int> (v,u));
						next.push_back(v);
						if(reachable==v)
						{
							//cout<<"\n"<<v<<" is reachable from "<<s;
							return true;
						}
					}
				}
			}
			frontier.clear();
			frontier = next;
			i++;
			
		}
		return false;
	}	
	
	void reachroot(int reachable) //reachable to previously defined root shortest path
	{
		if((reachable<-1 || reachable>V-1))
			return;
		
		if((parent.find(reachable) == parent.end()))
			return;
		cout<<reachable<<"--";
		reachroot(parent[reachable]);
		
	}	
};


int main()
{
	graph_bfs graph(5,true);
	graph.insertedge(0,1);
	graph.insertedge(1,2);
	graph.insertedge(0,2);
	graph.insertedge(2,3);
	graph.insertedge(3,4);
	cout<<graph.bfs(0,4)<<endl;
	graph.reachroot(4);
	return 0;
}