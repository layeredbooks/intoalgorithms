#include <catch2/catch_test_macros.hpp>

#include <repr/graph.h>

#include "dfs_path.h"

template <typename Graph>
void add_edges(Graph &g)
{
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(1, 5);
    g.add_edge(5, 2);
    g.add_edge(6, 5);
    g.add_edge(6, 4);
}

TEST_CASE("Undirected path")
{
    using GraphRepr = AdjListsUndirected;
    Graph<GraphRepr> g(8);
    add_edges(g);

    g.draw("test");

    auto dfs_path = DFSPath<GraphRepr, false>(g);
    auto found = dfs_path.traverse(0, 6);
    CHECK(found == true);
    auto path = dfs_path.get_path();
    CHECK(path == std::vector<int>{0, 1, 2, 3, 4, 6});

    found = dfs_path.traverse(0, 7);
    CHECK(found == false);
}

TEST_CASE("Directed path")
{
    using GraphRepr = AdjListsDirected;
    Graph<GraphRepr> g(8);
    add_edges(g);

    g.draw("test");

    auto dfs_path = DFSPath<GraphRepr, false>(g);
    auto found = dfs_path.traverse(0, 4);
    CHECK(found == true);
    auto path = dfs_path.get_path();
    CHECK(path == std::vector<int>{0, 1, 2, 3, 4});

    found = dfs_path.traverse(0, 6);
    CHECK(found == false);
}

TEST_CASE("Undirected all paths")
{
    using GraphRepr = AdjListsUndirected;
    Graph<GraphRepr> g(8);
    add_edges(g);

    g.draw("test");

    auto dfs_paths = DFSAllPaths<GraphRepr, false>(g);
    dfs_paths.traverse(0, 6);
    // dfs_paths.traverse(2, 1);
    dfs_paths.print_paths();

    auto paths = dfs_paths.get_paths();

    CHECK(paths.size() == 4);

    std::vector<std::vector<int>> expected = {{0, 1, 2, 3, 4, 6},
                                              {0, 1, 2, 5, 6},
                                              {0, 1, 5, 2, 3, 4, 6},
                                              {0, 1, 5, 6}};

    CHECK(paths == expected);
}
