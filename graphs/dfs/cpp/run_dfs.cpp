#include "dfs.h"

#include <iostream>

int main()
{
    auto g = Graph(5);
    g.add_edge(0, 1);
    g.add_edge(1, 3);
    g.add_edge(1, 2);
    g.add_edge(3, 4);
    g.print();
    auto d = DFS(g);
    d.dfs(0);
}