#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <vector>

#include <repr/graph.h>

#include "dfs.h"

template <typename Graph>
void add_edges(Graph &g)
{
    g.add_edge(0, 1);
    g.add_edge(2, 1);
    g.add_edge(3, 4);
    g.add_edge(5, 4);
    g.add_edge(3, 5);
    g.add_edge(6, 3);
    g.add_edge(6, 7);
}

std::vector<int> expected_undirected(int v_start)
{
    if (v_start == 0)
    {
        return {0, 1, 2};
    }
    else if (v_start == 3)
    {
        return {3, 4, 5, 6, 7};
    }
    else
    {
        return {};
    }
}

std::vector<int> expected_directed(int v_start)
{
    if (v_start == 0)
    {
        return {0, 1};
    }
    else if (v_start == 3)
    {
        return {3, 4, 5};
    }
    else
    {
        return {};
    }
}

auto make_dfs = []<typename Graph>(Graph &g)
{
    constexpr bool verbose = false;
    constexpr bool save_path = true;
    return DFS<decltype(g), verbose, save_path>(g);
};

TEST_CASE("DFS")
{
    constexpr int n_nodes = 10;
    // constexpr bool verbose = false;
    // constexpr bool save_path = true;

    auto v_start = GENERATE(0, 3);

    SECTION("Undirected")
    {
        SECTION("AdjLists")
        {
            AdjListsUndirected g(n_nodes);
            add_edges(g);
            auto dfs = make_dfs(g);
            dfs.traverse(v_start);
            REQUIRE(dfs.get_path() == expected_undirected(v_start));
        }
        SECTION("AdjMat")
        {
            AdjMatUndirected g(n_nodes);
            add_edges(g);
            auto dfs = make_dfs(g);
            dfs.traverse(v_start);
            REQUIRE(dfs.get_path() == expected_undirected(v_start));
        }
    }
    SECTION("Directed")
    {
        SECTION("AdjLists")
        {
            AdjListsDirected g(n_nodes);
            add_edges(g);
            auto dfs = make_dfs(g);
            dfs.traverse(v_start);
            REQUIRE(dfs.get_path() == expected_directed(v_start));
        }
        SECTION("AdjMat")
        {
            AdjMatDirected g(n_nodes);
            add_edges(g);
            auto dfs = make_dfs(g);
            dfs.traverse(v_start);
            REQUIRE(dfs.get_path() == expected_directed(v_start));
        }
    }
}
