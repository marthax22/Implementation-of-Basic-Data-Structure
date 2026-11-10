#include "Graph.h"
#include <fstream>
#include <queue>
#include <set>
#include <climits>

Graph::Graph() {
    edgeCount = 0;
}

     // Φορτωση γραφου απο αρχειο
void Graph::buildFromFile(string& filename) {
    std::ifstream file(filename);
    int node1, node2, weight;

        // assume αρχειο ειναι ενταξει
    while (file >> node1 >> node2 >> weight) {
        insertEdge(node1, node2, weight);  
    }

    file.close();
}

// προσθηκη ακμης
void Graph::insertEdge(int node1, int node2, int weight) {
    adjList[node1].push_back(std::make_pair(node2, weight));
    adjList[node2].push_back(std::make_pair(node1, weight));
    edgeCount++;
}

   // διαγραφη ακμης
void Graph::deleteEdge(int node1, int node2) {
    for (auto it = adjList[node1].begin(); it != adjList[node1].end(); ++it) {
        if ((*it).first == node2) {
            adjList[node1].erase(it);
            break;  
        }
    }

    for (auto it = adjList[node2].begin(); it != adjList[node2].end(); ++it) {
        if ((*it).first == node1) {
            adjList[node2].erase(it);
            break;
        }
    }

    edgeCount--;
}

std::pair<int, int> Graph::getSize() const {
    return std::pair<int, int>(adjList.size(), edgeCount);
}



int Graph::computeShortestPath(int src, int dst) {
    std::unordered_map<int, int> dist;
    std::set<int> visited;

    for (auto it = adjList.begin(); it != adjList.end(); ++it){
        dist[it->first] = INT_MAX;
    }

    dist[src] = 0;

    for (size_t i = 0; i < adjList.size(); i++){
        int minNode = -1;
        int minDist = INT_MAX;

        for (auto it = dist.begin(); it != dist.end(); ++it) {
            if (visited.find(it->first) == visited.end() && it->second < minDist) {
                minDist = it->second;
                minNode = it->first;
            }
        }

        if (minNode == -1) break;

        visited.insert(minNode);

        for (size_t j = 0; j < adjList[minNode].size(); j++){
            int neighbor = adjList[minNode][j].first;
            int cost = adjList[minNode][j].second;

            int newDist = dist[minNode] + cost;
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
            }
        }
    }

    return dist[dst];   
}

   // prim για minimum spanning tree
int Graph::computeSpanningTreeCost() {
    if (adjList.empty())
        return 0;

    std::set<int> inTree;
    std::priority_queue<std::pair<int, int>,
        std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int totalCost = 0;
    int startNode = adjList.begin()->first;
    pq.push(std::make_pair(0, startNode));

    while (!pq.empty()){
        std::pair<int, int> top = pq.top();
        pq.pop();

        int node = top.second;
        int cost = top.first;

        if (inTree.count(node))
            continue;

        inTree.insert(node);
        totalCost += cost;

        for (int i = 0; i < adjList[node].size(); i++) {
            int neighbor = adjList[node][i].first;
            int edgeCost = adjList[node][i].second;

            if (!inTree.count(neighbor)) {
                pq.push(std::make_pair(edgeCost, neighbor));
            }
        }
    }

    return totalCost;
}

   // επιστροφη αριθμου συνιστoσων
int Graph::findConnectedComponents(){
    std::unordered_map<int, bool> visited;
    int count = 0;

    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
        int node = it->first;
        if (!visited[node]) {
            dfs(node, visited);
            count++;   // νεα συνιστωσα
        }
    }

    return count;
}


 // dfs βοηθεια
void Graph::dfs(int node, std::unordered_map<int, bool>& visited) {
    visited[node] = true;

    for (int i = 0; i < adjList[node].size(); ++i) {
        int neighbor = adjList[node][i].first;
        if (!visited[neighbor]) {
            dfs(neighbor, visited);
        }
    }
}