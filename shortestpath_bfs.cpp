/*
	Implementation of breadth first search algorithm, which finds the shortest path.
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
	
	int orgv;
	
	public:
	graph_bfs(int vertices, bool dir, int orgv) //original v. for shortest path finding
	{
		V=vertices;
		directed = dir;
		this->orgv = orgv;
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
		if(reachable<orgv)
			cout<<reachable<<"<--";
		reachroot(parent[reachable]);
		
	}	
};

void transform(vector <vector<int> > edgestoadd, int V, bool dir)
{
	//if vertex u->v, and weight w between them: add w-1 vertex in middle
	int weights=0;
	for(int i=0;i<edgestoadd.size();i++)
		weights=weights+edgestoadd[i].at(2);
	
	int weightsum=weights - edgestoadd.size(); 
	int vertices=V + weightsum;
	graph_bfs graph(vertices,dir,V);
	
	int v_add=V;
	for(int i=0;i<edgestoadd.size();i++)
	{
		int u=edgestoadd[i].at(0);
		int v=edgestoadd[i].at(1);
		int w=edgestoadd[i].at(2);
		
		if(w==1)
		{
			graph.insertedge(u,v);
			continue;
		}
		
		graph.insertedge(u,v_add);
		//u--j--j+1--j+2---...v_add+w-1---v
		for(int j=v_add;j<v_add+w-2;j++)
			graph.insertedge(j,j+1);
		
		graph.insertedge(v_add+w-2,v);
		v_add=v_add+w-1;
	}
	
	cout<<endl;
	cout<<graph.bfs(1,4)<<endl;
	graph.reachroot(4);
	
}


int main()
{
	
	int V=5;
	bool dir=true;
	vector <vector<int> > edgestoadd;
	
	edgestoadd.push_back({0,1,4});
	edgestoadd.push_back({0,2,2});
	edgestoadd.push_back({1,3,3});
	edgestoadd.push_back({2,1,1});
	edgestoadd.push_back({1,4,6});
	edgestoadd.push_back({3,4,2});
	edgestoadd.push_back({2,3,1});
	transform(edgestoadd,V, dir);
	
	return 0;
}