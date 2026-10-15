
#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    int graph[20][20];

    cout << "Enter adjacency matrix (0 for no edge):\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    int parent[20];
    int key[20];
    bool visited[20] = {false};

    for (int i = 0; i < n; i++)
        key[i] = INT_MAX;

    key[0] = 0;
    parent[0] = -1;

    int totalCost = 0;

    for (int count = 0; count < n; count++)
    {
        int u = -1;
        int minKey = INT_MAX;

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && key[v] < minKey)
            {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1)
        {
            cout << "Graph is disconnected!\n";
            return 0;
        }

        visited[u] = true;

        if (parent[u] != -1)
        {
            cout << parent[u] << " - " << u
                 << " : " << graph[parent[u]][u] << "\n";

            totalCost += graph[parent[u]][u];
        }

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] != 0 && !visited[v] &&
                graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "Minimum Spanning Tree Cost: "
         << totalCost << endl;

    return 0;
}
