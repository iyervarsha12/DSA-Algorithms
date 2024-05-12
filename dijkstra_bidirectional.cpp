/*
	Implementation of the Dijkstra algorithm bidirectionally, using a priority queue 
*/

#include<bits/stdc++.h> 

using namespace std; 
# define INF 0x3f3f3f3f 
  
//using priority_queue with stl container as minheap.< pair<int,int>, vector < pair <int,int> >, greater <pair <int,int> > >. pair(i,j), ordered by i, j is associated val.
class Dijkstra_graph
{
	int V;
	bool direction;
	vector < vector <pair<int,int> > > adj; //map: key is vertex. Pair is (adj vertex,weight). (cant work because you can't have different values to same key)
	//so you use vector with int,int as adjvertex, weight.
		vector < vector <pair<int,int> > > adjrev;
	int *parentb;
	int *parentf;
	int *df;
	int *db;

	
	vector <int> sb;
	vector <int> sf;
	
	public:
	Dijkstra_graph(int V, bool dir)
	{
		direction=dir;
		this->V = V;
		parentf = new int[V];
		parentb = new int[V];
		df = new int[V];
		db = new int[V];
		vector <pair<int,int> > temp1;
		temp1.push_back(make_pair(0,0));
		
		vector <pair<int,int> > temp2;
		temp2.push_back(make_pair(V-1,0));
		for(int i=0;i<V;i++)
		{
			adj.push_back(temp1);
			adjrev.push_back(temp2);
		}
		
	}
	
	
	int addEdge(int u, int v, int w)
	{
		if(direction==false)
		{
			adj[v].push_back( make_pair(u,w));
			adjrev[u].push_back( make_pair(v,w));
		}
		adj[u].push_back( make_pair(v,w));
		adjrev[v].push_back( make_pair(u,w));
	}
	
	void init(int s, int t)
	{
		for(int i=0;i<V;i++)
		{
			df[i]=INF;
			db[i]=INF;
			parentf[i]=-1;
			parentb[i]=-1;
		}
		df[s]=0;
		db[t]=0;
		
	}
	
	bool check()
	{
		
		for(int i=0;i<sf.size();i++)
		{
			for(int j=0;j<sb.size();j++)
			{
				if(sf[i]==sb[j])
				{
					//cout<<"\n"<<sf[i]<<"on both lists.";
					return false;
				}
			}
		}
		return true;
	}


	void shortestPath(int s, int t)
	{
		//int t=V-1;
		init(s,t);
		priority_queue < pair<int,int>, vector < pair <int,int> >, greater <pair <int,int> > > pqf;
		priority_queue < pair<int,int>, vector < pair <int,int> >, greater <pair <int,int> > > pqb;
		pqf.push( make_pair(0,s) ); //ordered by first of the pair.
		pqb.push( make_pair(0,t) ); //ordered by first of the pair.
		for(int i=0;i<V;i++)
			if(i!=s)
				pqf.push( make_pair(INF,i) );
			
		for(int i=0;i<V;i++)
			if(i!=t)
				pqb.push( make_pair(INF,i) );
	
		while(check())//while pqb and pqf both miss one common element. Or when Sb and Sf have one common element
		{
			
			int u = pqf.top().second;
			//int d[u] =pq.top().first;
			sf.push_back(u);
			pqf.pop();
			for(int i=0;i<adj[u].size();i++)
			{
				//neighboring vertex present in adj[u][i].
				int v=adj[u][i].first;
				int weight = adj[u][i].second;
				
				if(df[v]>df[u]+weight)
				{
					
					df[v]=df[u]+weight;
					parentf[v]=u;
					pqf.push(make_pair(df[v],v)); 
				}
			}
			
			
			if(check())
			{
				u=pqb.top().second;
				sb.push_back(u);
				pqb.pop();
				
				for(int i=0;i<adjrev[u].size();i++)
				{
					int v=adjrev[u][i].first;
					int weight = adjrev[u][i].second;
					//cout<<endl<<"b"<<" "<<u<<" "<<db[u]<<" "<<v<<" "<<db[v]<<" "<<weight;
					if(db[v]>db[u]+weight)
					{
						
						db[v]=db[u]+weight;
						parentb[v]=u;
						pqb.push(make_pair(db[v],v)); 
					}
					
				}
			}
			
			
		}
		printshortestdist();
	}

	int endingelt()
	{
		int min=df[0]+db[0];
		int index=0;
		for(int x=1;x<V;x++)
		{
			if(df[x]+db[x] < min)
			{
				min = df[x]+db[x];
				index=x;
			}
			
		}
		return index;
	}

	void printshortestdist()
	{
		//forward go till x, backward go till x
		int x=endingelt();
		cout<<"\nShortest path is of length: "<<df[x]+db[x]<<endl;
		int u=x;
		cout<<"<-"<<u<<"<-";
		while(parentf[u]!=-1)
		{
			cout<<parentf[u]<<"<-";
			u=parentf[u];
		}
		cout<<endl;
		while(parentb[x]!=-1)
		{
			cout<<parentb[x]<<"->";
			x=parentb[x];
		}
		
		cout<<endl;
		cout<<endl;
		
		cout<<"\nVertex\tDistance from source\n";
		for(int i=0;i<V;i++)
		{
			if(i<=x)
			{
				if((df[i]>=0)&&(df[i]!=INF))
					cout<<i<<"\t"<<df[i]<<endl;	
				else cout<<i<<"\t"<<"Not defined"<<endl;
			}
			else
			{
				if((db[i]>=0)&&(db[i]!=INF))
					cout<<i<<"\t"<<db[i]<<endl;	
				else cout<<i<<"\t"<<"Not defined"<<endl;

			}
		} 
		
	}

};

int main()
{
	Dijkstra_graph d(5,true);
	d.addEdge(0,1,3);
	d.addEdge(1,2,3);
	d.addEdge(2,4,3);
	d.addEdge(0,3,5);
	d.addEdge(3,4,5);
	d.shortestPath(0,3);
	
	return 0;
}

