#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <utility>
#include <string>
using namespace std;
class Graph {
private:
     // Λιστα γειτονιας
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjList;

    int edgeCount;  // Αριθμος ακμων

    void dfs(int node, std::unordered_map<int, bool> &visited); // DFS

public:
    Graph();   // Constructor

    void buildFromFile(string& filename);   // Φορτωνει απο αρχειο

    void insertEdge(int node1, int node2, int weight);  // Προσθηκη ακμης
    void deleteEdge(int node1, int node2);  // Διαγραφη ακμης

    std::pair<int,int> getSize() const;   // Κομβοι ακμες

    int computeShortestPath(int src, int dst); // Dijkstra
    int computeSpanningTreeCost();  // MST
    int findConnectedComponents();  // Συνηστωσες
};

#endif
