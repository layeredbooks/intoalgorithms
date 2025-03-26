#include "dfs.h"

#include <iostream>

int main()
{
    auto g = Graph(5);
    std::cout << "hello" << std::endl;
    g.add_edge(0, 1);
    g.add_edge(1, 3);
    g.add_edge(1, 2);
    g.add_edge(3, 4);
    g.print();
    auto dfs = DFS(g);
    dfs.dfs(0);
}