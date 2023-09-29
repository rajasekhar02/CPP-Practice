![image](https://user-images.githubusercontent.com/13390833/199835782-2b2462cf-f70a-4cfd-bef7-189ab87042d0.png)
![image](https://user-images.githubusercontent.com/13390833/199835867-204b2c9c-3a1d-4a88-b139-a5a95ff69bf1.png)


Passes Only : 9/15 testcases
Remaining Cases fails due to Time limit Exceeded
May be Algorithm is slow 
```cpp
pair<int,int> dfs(vector<vector<int>> adjList, int nodeIndex, vector<bool> visited, vector<int> val){
    visited[nodeIndex] = true;
    int cost = 0;
    int nodesNotResolved = val[nodeIndex]%2 == 1 ? 1:0;
    vector<int> childNodeCosts;
    for(int i=0;i<(int)adjList[nodeIndex].size();i++){
        if(visited[adjList[nodeIndex][i]]) continue;
        pair<int,int> childNodeCntAndCost = dfs(adjList, adjList[nodeIndex][i], visited, val);
        if(!childNodeCntAndCost.first){
            cost += childNodeCntAndCost.second;
            continue;
        }
        // childNodeCosts.push_back(childNodeCntAndCost.second+childNodeCntAndCost.first);
        cost += childNodeCntAndCost.second+childNodeCntAndCost.first;
        nodesNotResolved++;
    }
    return make_pair(nodesNotResolved%2, cost);
}

int getMinCost(vector<int> val, int t_nodes, vector<int> t_from, vector<int> t_to) {
    int total_val = 0;
    cout<<t_nodes<<endl;
    vector<vector<int>> adjList(t_nodes);
    vector<bool> visited(t_nodes, false);
    for(int i=0;i<(int)t_from.size();i++){
        adjList[t_from[i]-1].push_back(t_to[i]-1);
        adjList[t_to[i]-1].push_back(t_from[i]-1);
    }
    pair<int,int> nodesAndCost = dfs(adjList, 0, vector<bool>(visited), vector<int>(val));
    return nodesAndCost.second; 
}
```
