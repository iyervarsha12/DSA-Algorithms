/*
	Implementation of the depth-first search in a graph, including edge classification and times taken.
*/

#include <iostream>
#include <vector>
#include <map>
#include <time.h>

using namespace std;

class graph_dfs
{
	int time;
	
	int v_no;
	vector <int> V;
	bool directed; 
	bool cycle;
	
	map<int,int> level; //vertex key, level value
	map<int,int> parent; //vertex key, parent vertex value
	map<int,vector<int> > adj; //has vertex as key, adjacent elements as value
	map<int,vector<int> > start_finish_times; //vertex key, start elt1, end elt2
	
	vector<int> treestack;
	map< vector<int>, int > classification; //first is edge. 0 if tree edge, 1 if forward, 2 if backward, 3 if cross.
	
	
	public:
	graph_dfs(int num, bool dir)
	{
		time=0;
		cycle=false;
		v_no=num;
		directed=dir;
		for(int i=0;i<num;i++)
			V.push_back(i);
	}
	
	bool insertedge(int v, int u) //v->u for directed, v--u for undirected(no need to enter u--v here)
	{
		if((v<0 || v>v_no-1)||(u<0 || u>v_no-1))
			return false;
		
		adj[v].push_back(u); //at key v, insert u
		if(!directed)
			adj[u].push_back(v);
		return true;
		
		
	}
	bool check_parent(int v) //false if v not in parent
	{ 
		if (parent.find(v) == parent.end()) 
			return false; 
		return true; 
	} 
	
	void DFS_visit(int s)
	{
		time++;
		start_finish_times[s].push_back(time); 
		parent[s]=-1;
		for(auto v: adj[s])
		{
			if(check_parent(v)==false)
			{
				parent[v]=s;
				cout<<v<<"--";
				treestack.push_back(v);
				DFS_visit(v);
			}
		}
		time++;
		start_finish_times[s].push_back(time); 
	}
	
	void DFS()
	{
		parent.clear();
		for(int s: V)
		{
			
			if(!check_parent(s))
			{
				
				time++;
				start_finish_times[s].push_back(time); 
				parent[s]=-1;
				cout<<s<<"--";
				treestack.push_back(s);
				DFS_visit(s);
				treestack.push_back(-1);
				cout<<"\n";
				time++;
				start_finish_times[s].push_back(time); 
				
			}
			
		}
		edgeclassification();
	}
	
	void edgeclassification()
	{
		/*
		time wise and stack wise: 
		tree edge if in stack, neighbors.
		forward edge i->j if j time within i time.
		backward edge i->j if i time within j time.
		cross edge whatever else.
		*/
		for(int i=0;i<treestack.size();i++) //linear.
		{
			if(treestack[i]!=-1 && treestack[i+1]!=-1)
			{
				vector <int> temp;
				temp.push_back(treestack[i]);
				temp.push_back(treestack[i+1]);
				classification[temp]=0;
				cout<<"\n"<<treestack[i]<<"->"<<treestack[i+1]<<"\t"<<"Tree edge";
			}
		}
		
		for(int i=0;i<adj.size();i++)
		{
			for(int j=0;j<adj[i].size();j++) //i to adj[i].at(j) edge.
			{
				//forward edge, if  i.start j.start j.end i.end...i -> j
				//backward edge if j.start i.start i.end j.end...i -> j
				int lt1 = start_finish_times[i].size()-1;
				int lt2 = start_finish_times[adj[i].at(j)].size()-1;
				if((start_finish_times[i].at(0) < start_finish_times[adj[i].at(j)].at(0))&&(start_finish_times[adj[i].at(j)].at(lt2) < start_finish_times[i].at(lt1)))
				{
					vector <int> temp;
					temp.push_back(i);
					temp.push_back(adj[i].at(j));
					if(classification.find(temp) == classification.end())
					{
						classification[temp]=1;
						cout<<"\n"<<i<<"->"<<adj[i].at(j)<<"\t"<<"Forward edge";
					}
				}
				else
				if((start_finish_times[adj[i].at(j)].at(0) < start_finish_times[i].at(0))&&(start_finish_times[i].at(lt1) < start_finish_times[adj[i].at(j)].at(lt2)))
				{
					vector <int> temp;
					temp.push_back(i);
					temp.push_back(adj[i].at(j));
					if(classification.find(temp) == classification.end())
					{
						cycle=true;
						classification[temp]=2;
						cout<<"\n"<<i<<"->"<<adj[i].at(j)<<"\t"<<"Backward edge";
					}
				}
				else
				{
					vector <int> temp;
					temp.push_back(i);
					temp.push_back(adj[i].at(j));
					if(classification.find(temp) == classification.end())
					{
						classification[temp]=3;
						cout<<"\n"<<i<<"->"<<adj[i].at(j)<<"\t"<<"Cross edge";
					}
					
				}
			}
		}
	}
	
	void printtimes()
	{
		for(int i=0;i<v_no;i++)
		{
			cout<<i<<":  ";
			cout<<start_finish_times[i].at(0)<<"\t"<<start_finish_times[i].at(start_finish_times[i].size()-1);
			cout<<endl;
		}
	}
};


int main()
{
	graph_dfs g(6,true);
	g.insertedge(0,1);
	g.insertedge(1,4);
	g.insertedge(4,3);
	g.insertedge(0,3);
	g.insertedge(3,1);
	g.insertedge(2,4);
	g.insertedge(2,5);
	g.DFS();
	cout<<endl;
	//g.printtimes();
	
	return 0;
}