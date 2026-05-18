//Practical: Parallel Breadth First Search and Depth First Search based on existing algorithms using OpenMP
//%%writefile bfs.cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph{
    int V; vector<int>* adj;
public:
    Graph(int V){this->V=V; adj=new vector<int>[V];}
    void addEdge(int v,int w){adj[v].push_back(w); adj[w].push_back(v);}

    void bfs(int s){
        vector<bool> vis(V,false); queue<int> q;
        vis[s]=true; q.push(s);
        while(!q.empty()){
            int u=q.front(); q.pop(); cout<<u<<" ";
            for(int i=0;i<adj[u].size();i++){
                int v=adj[u][i];
                if(!vis[v]) vis[v]=true,q.push(v);
            }
        }
    }

    void dfs(int s){
        vector<bool> vis(V,false); dfsUtil(s,vis);
    }

    void dfsUtil(int u, vector<bool>& vis){
        vis[u]=true; cout<<u<<" ";
        for(int i=0;i<adj[u].size();i++){
            int v=adj[u][i];
            if(!vis[v]) dfsUtil(v,vis);
        }
    }
};

int main(){
    Graph g(6);
    g.addEdge(0,1); g.addEdge(0,2); g.addEdge(1,3);
    g.addEdge(2,4); g.addEdge(3,4); g.addEdge(3,5);

    cout<<"BFS starting from vertex 3: "; g.bfs(3); cout<<endl;
    cout<<"DFS starting from vertex 5: "; g.dfs(5);
}

//!g++ bfs.cpp -fopenmp -o bfs
//!./bfs