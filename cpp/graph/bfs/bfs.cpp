#include <iostream>

#include <repr/graph.h>

#include "bfs.h"

int main()
{
    using GraphRepr = AdjLists<false>;
    Graph<GraphRepr> g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(0, 3);
    g.add_edge(2, 4);
    g.print();
    g.draw("bfs");
    auto bfs = BFS<decltype(g), true, true>(g);
    bfs.traverse(0);
    const auto &path = bfs.get_path();
    bfs.print_path();
    return 0;
}