#include <iostream>

#include <repr/graph.h>

#include "dfs.h"

int main()
{
    using Graph = AdjLists<false>;
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    print(g);
    auto dfs = DFS<Graph, true, true>(g);
    dfs.traverse(0);
    auto path = dfs.get_path();
    dfs.print_path();
    return 0;
}