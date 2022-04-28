#include <iostream>
#include "Graph.hpp"
using namespace std;

int main()
{
    int vertices, edges;
    cin >> vertices >> edges;

    Graph<int> graph;

    for (int i = 0; i < vertices; i++)
        graph.add_vertex(i);

    for (int i = 0; i < edges; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;
        graph.add_edge(v1, v2);
    }
    // test case 1:
    graph.display();
    // test case 2:
    graph.dfs(0, [](auto &v)
              { cout << v.key << " "; });
    puts("");
    // test case 3:
    graph.bfs(0, [](auto &v)
              { cout << v.key << " "; });

    return 0;
}