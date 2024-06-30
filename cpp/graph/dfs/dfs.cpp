#include <iostream>

#include <repr/graph.h>

#include "dfs.h"

int main()
{
    using GraphRepr = AdjLists<false>;
    Graph<GraphRepr> g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.print();
    auto dfs = DFS<decltype(g), true, true>(g);
    dfs.traverse(0);
    const auto &path = dfs.get_path();
    dfs.print_path();
    return 0;
}