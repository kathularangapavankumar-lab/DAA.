#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

class GraphTraversal {
private:
    int numNodes;
    vector<vector<int>> adjList;

    // Renamed helper function for DFS
    void recursiveDFS(int current, vector<bool>& visitedNodes) {
        visitedNodes[current] = true;
        cout << current << " ";

        for (int neighbor : adjList[current]) {
            if (!visitedNodes[neighbor]) {
                recursiveDFS(neighbor, visitedNodes);
            }
        }
    }

public:
    // Constructor
    GraphTraversal(int nodes) {
        numNodes = nodes;
        adjList.resize(numNodes);
    }

    // Renamed from addEdge
    void createEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // Keep this for undirected graph
    }

    void executeDFS(int startNode) {
        vector<bool> visitedNodes(numNodes, false);
        recursiveDFS(startNode, visitedNodes);
    }

    void executeBFS(int startNode) {
        vector<bool> visitedNodes(numNodes, false);
        queue<int> nodeQueue;

        visitedNodes[startNode] = true;
        nodeQueue.push(startNode);

        while (!nodeQueue.empty()) {
            int current = nodeQueue.front();
            nodeQueue.pop();

            cout << current << " ";

            for (int neighbor : adjList[current]) {
                if (!visitedNodes[neighbor]) {
                    visitedNodes[neighbor] = true;
                    nodeQueue.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int totalVertices, totalEdges;

    cout << "--- Graph Traversal & Time Analysis ---\n";
    cout << "Enter total number of vertices: ";
    cin >> totalVertices;

    GraphTraversal graph(totalVertices);

    cout << "Enter total number of edges: ";
    cin >> totalEdges;

    cout << "Enter the edges (format: source destination):\n";
    for (int i = 0; i < totalEdges; ++i) {
        int src, dest;
        cin >> src >> dest;
        graph.createEdge(src, dest);
    }

    int startVertex;
    cout << "Enter the starting vertex for traversals: ";
    cin >> startVertex;

    // ----------------- DFS Execution & Timing -----------------
    auto t1_dfs = high_resolution_clock::now();

    cout << "\n[ DFS Traversal Path ]: ";
    graph.executeDFS(startVertex);

    auto t2_dfs = high_resolution_clock::now();
    auto durationDFS = duration_cast<nanoseconds>(t2_dfs - t1_dfs).count();

    // ----------------- BFS Execution & Timing -----------------
    auto t1_bfs = high_resolution_clock::now();

    cout << "\n[ BFS Traversal Path ]: ";
    graph.executeBFS(startVertex);

    auto t2_bfs = high_resolution_clock::now();
    auto durationBFS = duration_cast<nanoseconds>(t2_bfs - t1_bfs).count();

    // ----------------- Display Final Benchmarks -----------------
    cout << "\n\n--- Performance Results ---\n";
    cout << "DFS Execution Time: " << durationDFS << " ns\n";
    cout << "BFS Execution Time: " << durationBFS << " ns\n";
    cout << "---------------------------\n";

    return 0;
}
