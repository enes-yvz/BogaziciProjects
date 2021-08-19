#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

struct Node {
    
    int id;
    vector <int> childs;
    
};

vector <Node> tree;

vector <vector<int>> indices;

vector <int> hashTableFirst;

vector<int> hashTableSecond;

vector<int> hashTableThird;

int depth = 0;

int c = 0;

void preOrder() {
    
    stack<Node> nodes;
    
    stack<int> depths;
    
    nodes.push(tree[0]);
    
    depths.push(depth);
    
    while (!nodes.empty()) {
        
        Node curr = nodes.top();
        
        nodes.pop();
        
        int depth = depths.top();
        
        depths.pop();
        
        indices[depth].push_back(c);
        
        hashTableFirst[curr.id] = c; 
        
        hashTableSecond[c] = curr.id;
        
        hashTableThird[c] = depth;
        
        if (curr.childs.size() != 0) {
            
            depth++;
            
            for (int f=curr.childs.size()-1;f>=0;f--){
                
                nodes.push(tree[curr.childs[f]]);
                
                depths.push(depth);
                
            }
        
        }
        
        c++;
        
    }
    
}

int main(int argc, char const *argv[]) {
    
    string myResult;
    
    ifstream inFile;
    
    ofstream outFile;
    
    string final{};
    
    inFile.open(argv[1]);
    
    outFile.open(argv[2]);
    
    int first= 0;
    
    inFile >> first;
    
    tree.resize(first);
    
    int second =0;
    
    for (int i=0;i<first;i++) {
        
        inFile >> second;
        
        tree[second].childs.push_back(i);
        
        tree[i].id =i;
        
    }
    
    indices.resize(first);
    
    hashTableFirst.resize(first);
    
    hashTableSecond.resize(first);
    
    hashTableThird.resize(first);
    
    preOrder();
    
    int count=0;
    
    inFile >> count;
    
    for (int i=0; i< count ;i++) {
        
        inFile >> first;
    
        inFile >> second;
        
        int hashed = hashTableFirst[first];
        
        int searchedRow = hashTableThird[hashed];
        
        if (searchedRow-second<0) {
            
            myResult += "-1";
            
            myResult += "\n";
            
            continue;
        }
        
        int searchedInt;
        
        for (int h=0;h<indices[searchedRow-second].size();h++) {
            
            if (indices[searchedRow-second][h] < hashed) {
                
                searchedInt = indices[searchedRow-second][h];
            }
            
            else {
                
                break;
            }
        }
        
        myResult += to_string(hashTableSecond[searchedInt]);
        
        myResult += "\n";
        
    }
    
    outFile << myResult;
    
    return 0;
}


