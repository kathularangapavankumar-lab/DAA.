
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
};

bool compare(Edge a, Edge b)
{
    return a.weight < b.weight;
}

int findParent(int parent[], int i)
{
    if (parent[i] == i)
        return i;

    return parent[i] = findParent(parent, parent[i]);
}

void unionSet(int parent[], int rank[], int x, int y)
{
    int rootX = findParent(parent, x);
    int rootY = findParent(parent, y);

    if (rootX == rootY)
        return;

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    Edge edges[100];

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].u >> edges[i].v
            >> edges[i].weight;
    }

    sort(edges, edges + E, compare);

    int parent[100], rank[100] = {0};

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int totalCost = 0;
    int count = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (int i = 0; i < E && count < V - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        int rootU = findParent(parent, u);
        int rootV = findParent(parent, v);

        if (rootU != rootV)
        {
            cout << u << " - " << v
                 << " : " << edges[i].weight << "\n";

            totalCost += edges[i].weight;

            unionSet(parent, rank, rootU, rootV);
            count++;
        }
    }

    if (count != V - 1)
        cout << "Graph is disconnected; MST not possible.\n";
    else
        cout << "Minimum Spanning Tree Cost: "
             << totalCost << endl;

    return 0;
}
