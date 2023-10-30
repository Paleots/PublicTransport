#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Structure.hpp"
#include "stdc++.hpp"
using namespace std;


int main() {
    
    Structure vv;
    
    vv.openTerminal();
    
    return 0;
}

















//C++ program to find the Shortest Path in an Unweighted Graph
//#include "stdc++.hpp"

 
// Graph class implemented using an adjacency list



/*

class Graph{

public:
    int V;  // Number of Vertices
    int E;  // Number of Edges
    vector<int> *adj; // adjacency list
    Graph(int num_vertices, int num_edges){
        this->V = num_vertices;
        this->E = num_edges;
        this->adj = new vector<int>[num_vertices];
    }
    // function to add Edge
void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
 }

    // function to compute all paths
void computeAllPaths(int src, int dest, vector<int> &path, vector<bool> &vis, vector<vector<int>> &paths){
        if(vis[src]){   // if this node is already visited then return
            return ;
        }
        // if src == dest means that we have reached the destination and found the path
        if(src == dest){
            path.push_back(src);
            paths.push_back(path);
            path.pop_back();
            return;
        }
        // mark current node as visited
        vis[src] = 1;
        path.push_back(src);
        // traverse the path via current node's adjacent nodes
        for(int node: this->adj[src]){
            if(!vis[node]){  // if adjacent node is not visited
                // path.push_back(node);    // push to the possible path list
                computeAllPaths(node, dest, path, vis, paths); // recursively traverse path
                // path.pop_back(); // pop_back from the possible path list
            }
        }
        vis[src] = 0; // mark current node as unvisited
        path.pop_back(); // pop the current source node
    }

    // function that prints out the shortest path
void ShortestPath(int src, int dest){
       vector<int> path;   // possible path list
       vector<bool> vis(V, 0); // visited list
       vector<vector<int>> paths; // list of all paths from src to dest
       computeAllPaths(src, dest, path, vis, paths); // find All paths
       vector<int> Shortest_path; // vector to store the Shortest_path
       for(vector<int> v: paths){
           // find the Shortest_path
           if(Shortest_path.size()==0 or (Shortest_path.size()>v.size())){
               Shortest_path = v;
           }
       }
       cout<<"The Shortest Path of the Unweighted Graph is: ";
       // print the shortest path
       for(int i=0;i<Shortest_path.size();++i){
           if(i!=Shortest_path.size()-1){
               cout<<Shortest_path[i]+1<<" -> ";
           }else{
               cout<<Shortest_path[i]+1<<'\n';
           }
       }
    cout<<endl;
       cout<<"The length is "<<Shortest_path.size()<<endl;
    }
};
 

int getIndex(vector<string> v, string K)
{
    auto it = find(v.begin(), v.end(), K);
  
    // If element was found
    if (it != v.end())
    {
      
        // calculating the index
        // of K
        int index = it - v.begin();
        return index;
    }else return - 1;
    
}
 


int main(){
    map<string,vector<string>> MapOflines;
    MapOflines["12"] = {"154", "578", "123", "422", "3112", "99", "12", "1221", "1212"};
    MapOflines["MINI"] = {"154", "578", "23", "1024", "111", "1221", "1212"};
    MapOflines["81L"] = {"154", "578", "23", "1024","103", "123" ,"422" ,"3112" ,"219", "1", "312"};
    vector<string> Linije = {"12","MINI","81L"};
    Graph G(3,4);
    
    vector<string> CheckConnections;
    for(auto& e : Linije){
        for(auto& g : MapOflines[e]){
            int pol = 0;
            for(auto& h: Linije){
                for (auto& p : CheckConnections ){if ((h+e == p) || (e+h == p)) continue; }
                int n = 0;
                if(h!=e){
                    for(auto& l:MapOflines[h]){
                        if(l == g)n++; pol++;
                        if(n>0) {G.addEdge(getIndex(Linije, e), getIndex(Linije, h)); CheckConnections.push_back(e+h); break;}
                    }
                }
            }
            if(pol>0) break;
        }
        
        
    }

    /*
     int n = 0;
     for(auto& k : CheckConnections1){
         if(c==k || h==k)n++;
     }
     */
    
    //12  - 0
    //MINi - 1
    //81L  - 2
    
/*
    int i = getIndex(Linije, "81L");
    cout<<i<<endl;
    return 0;
}

*/
 
 

/*
int main() {
    // Number of Edges and Vertices
    int num_vertices = 16;
    int num_edges = 17;
    Graph G(num_vertices, num_edges); // Graph G
    // add all edges to graph
    //int v = 17;
    vector<int> t;
    t.push_back(154);//1
    t.push_back(578);//2
    t.push_back(123);//3
    t.push_back(422);//4
    t.push_back(3112);//5
    t.push_back(99);//6
    t.push_back(12);//7
    t.push_back(1221);//8
    t.push_back(1212);//9
    t.push_back(23);//10
    t.push_back(1024);//11
    t.push_back(111);//12
    t.push_back(103);//13
    //t.push_back(3112);//14 ///
    t.push_back(219);//15 // 14
    t.push_back(1);//16 // 15
    t.push_back(312);//17 // 16
    int g = t.size();
    
    G.addEdge(1,2);
    G.addEdge(2,1);
    G.addEdge(2,3);
    G.addEdge(3,2);
    G.addEdge(3,4);
    G.addEdge(4,3);
    G.addEdge(4,5);
    G.addEdge(5,4);
    G.addEdge(5,6);
    G.addEdge(6,5);
    G.addEdge(6,7);
    G.addEdge(7,6);
    G.addEdge(7,8);
    G.addEdge(8,7);
    G.addEdge(8,9);
    G.addEdge(9,8);
    
   // G.addEdge(154,578);
    //G.addEdge(578,154);
    G.addEdge(2,10);
    G.addEdge(10,2);
    G.addEdge(10,11);
    G.addEdge(11,10);
    G.addEdge(11,12);
    G.addEdge(12,11);
    G.addEdge(12,8);
    G.addEdge(8,12);
    //G.addEdge(1221,1212);
    //G.addEdge(1212,1221);
    
    //G.addEdge(154,578);
    //G.addEdge(578,154);
    //G.addEdge(578,23);
    //G.addEdge(23,578);
    //G.addEdge(23,1024);
    //G.addEdge(1024,23);
    G.addEdge(11,13);
    G.addEdge(13,11);
    G.addEdge(13,3);
    G.addEdge(3,13);
    //-----
    G.addEdge(5,14);
    G.addEdge(14,5);
    G.addEdge(14,15);
    G.addEdge(15,14);
    G.addEdge(15,16);
    G.addEdge(16,15);


    // compute the Shortest_path

    int src = 6; int dest = 10;
    G.ShortestPath(src-1, dest-1); // 0-based indexing
    return 0;
}







*/

