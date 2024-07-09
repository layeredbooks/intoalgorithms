#include <iostream>

#include <repr/graph.h>

#include "bfs_path.h"

int main() {
    // using GraphRepr = AdjListsUndirected;
    using GraphRepr = AdjListsDirected;
    Graph<GraphRepr> g(7);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(0, 4);
    g.add_edge(2, 1);
    g.add_edge(2, 3);
    g.add_edge(3, 1);
    g.add_edge(4, 5);
    g.add_edge(5, 3);
    g.print();
    g.draw("bfs_path");

    int v_start = 0;
    int v_dest = 5;

    auto bfs_path = BFSPath<GraphRepr, true, true>(g);
    auto length = bfs_path.traverse(v_start, v_dest);
    auto found = length.has_value();
    std::cout << "found: " << std::boolalpha << found << std::endl;
    if (found) {
        std::cout << "length: " << length.value() << std::endl;
    }
    std::cout << "path:";
    auto path = bfs_path.get_path();
    bfs_path.print_path(path);

    return 0;
}