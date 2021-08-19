#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <chrono>

using namespace std;

int n;

vector<vector<int>> capacity;;

vector<vector<int>> cost;

vector<vector<int>> adj;

vector<int> dis; 
    
vector<int> len;

vector<bool> control;

const int inf = 10000;

void shortestPath(int n, int s) {
    
    dis.resize(n);
    
    fill(dis.begin(),dis.begin()+n,inf);
    
    dis[s] = 0;
    
    len.resize(n);
    
    fill(len.begin(),len.begin()+n,-1);
    
    control.resize(n);
    
    fill(control.begin(),control.begin()+n,false);
    
    queue<int> queue;
    
    queue.push(s);

    while (!queue.empty()) {
        
        int u = queue.front();
        
        queue.pop();
        
        control[u] = false;
        
        for (int v : adj[u]) {
            
            if (capacity[u][v] > 0 && dis[u] + cost[u][v] < dis[v]) {
                
                dis[v] = dis[u] + cost[u][v];
                len[v] = u;
                
                if (!control[v]) {
                    
                    queue.push(v);
                    control[v] = true;
                }
            }
        }
    }
}

int minCostMaxFlow(int s, int t) {
    
    n = capacity.size();
    
    int flow = 0;
    
    int cost = 0;
    
    while (flow <= n) {
        
        shortestPath(n, s);
        
        if (dis[t] == inf){
            
            break;  
        
        } 
            
        int f = n - flow;
        int current = t;
        
        while (current != s) {
            f = min(f, capacity[len[current]][current]);
            current = len[current];
        }
        
        flow += f;
        cost += f * dis[t];
        current = t;
        
        while (current != s) {
            capacity[len[current]][current] -= f;
            capacity[current][len[current]] += f;
            current = len[current];
        }
    }
    
    return cost;
}

int main(int argc, char const *argv[]) {
    
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    
    ifstream inFile;
    
    ofstream outFile;
    
    string final{};
    
    inFile.open(argv[1]);
    
    outFile.open(argv[2]);
    
    int countFirst;
    
    inFile >> countFirst;
    
    int s = 0;
    
    int t;
    
    for(int i=0;i<countFirst;i++) {
      
        int countSecond;
    
        inFile >> countSecond;  
        
        t = countSecond *2 +1;
        
        capacity.resize(countSecond*2+2);
            
        for (int i=0 ;i<capacity.size();i++) {
            
            capacity[i].resize(countSecond*2+2);
            
        }
        
        cost.resize(countSecond*2+2);
        
        for (int i=0 ;i<capacity.size();i++) {
            
            cost[i].resize(countSecond*2+2);
            
        }
        
        for (int f=0;f<countSecond*2+2;f++) {
            
            for (int k=0;k<countSecond*2+2;k++) {
                
                if (f==0 && k>0 && k<countSecond+1) {
                    
                    capacity[f][k]=1;
                }
                
                else if (f>0 && f<countSecond+1 && k>countSecond && k<countSecond*2+1) {
                    
                    capacity[f][k]=1;
                    
                    int num;
                    
                    inFile >>num;
                    
                    cost[f][k]= -num;
                    
                    cost[k][f]=num;
                }
                
                else if(f>countSecond && f <countSecond*2+1 && k==countSecond*2+1) {
                    
                    capacity[f][k]=1;
                    
                }
                
            }
            
        }
        
        adj.resize(countSecond*2+2);
        
        for(int l=1; l<countSecond+1;l++) {
            
            adj[0].push_back(l);
            adj[l].push_back(0);
            
        }
            
        for(int h =1;h<countSecond+1;h++) {    
            
            for(int l= countSecond+1;l<countSecond*2+1;l++) {
                
                adj[h].push_back(l);
                adj[l].push_back(h);
            }
            
        }
        
        for(int l= countSecond+1;l<countSecond*2+1;l++) {
            
            adj[l].push_back(countSecond*2+1);
            
            adj[countSecond*2+1].push_back(l);
            
        }
    
        int finalResult = - minCostMaxFlow(s, t);
        
        capacity.clear();
        
        cost.clear();
        
        adj.clear();
    
        final += to_string(finalResult) ;
        
        final += "\n";
        
    }
    
    outFile << final;
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    
    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "mikrosaniye"<< endl;
        
    return 0;
}