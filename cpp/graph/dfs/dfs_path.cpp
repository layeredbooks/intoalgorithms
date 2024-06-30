#include <iostream>

#include <repr/graph.h>

#include "dfs_path.h"

int main()
{
    using GraphRepr = AdjListsDirected;
    Graph<GraphRepr> g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(2, 1);
    g.add_edge(2, 3);
    g.add_edge(4, 3);
    g.add_edge(0, 4);
    g.print();

    int v_start = 0;
    int v_dest = 3;

    auto dfs_path = DFSPath<GraphRepr, true>(g);
    auto found = dfs_path.traverse(v_start, v_dest);
    std::cout << "found: " << std::boolalpha << found << std::endl;
    dfs_path.print_path();

    auto dfs_paths = DFSAllPaths<GraphRepr, true>(g);
    dfs_paths.traverse(v_start, v_dest);
    dfs_paths.print_paths();
    return 0;
}