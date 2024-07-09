#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <vector>

#include <repr/graph.h>

#include "bfs.h"

template <typename Graph> void add_edges(Graph &g) {
    g.add_edge(0, 1);
    g.add_edge(2, 1);
    g.add_edge(3, 4);
    g.add_edge(3, 5);
    g.add_edge(3, 8);
    g.add_edge(5, 4);
    g.add_edge(6, 3);
    g.add_edge(6, 7);
    g.add_edge(8, 9);
}

std::vector<int> expected_undirected(int v_start, bool adj_mat) {
    if (v_start == 0) {
        return {0, 1, 2};
    } else if (v_start == 3) {
        if (adj_mat) {
            return {3, 4, 5, 6, 8, 7, 9};
        } else {
            return {3, 4, 5, 8, 6, 9, 7};
        }
    } else {
        return {};
    }
}

std::vector<int> expected_directed(int v_start) {
    if (v_start == 0) {
        return {0, 1};
    } else if (v_start == 3) {
        return {3, 4, 5, 8, 9};
    } else {
        return {};
    }
}

template <typename Graph, template <typename, bool, bool> typename Bfs>
auto make_bfs(Graph &g) {
    constexpr bool verbose = false;
    constexpr bool save_path = true;
    return Bfs<Graph, verbose, save_path>(g);
};

TEST_CASE("BFS") {
    constexpr int n_nodes = 10;

    auto v_start = GENERATE(0, 3);

    SECTION("Undirected") {
        SECTION("AdjLists") {
            AdjListsUndirected g(n_nodes);
            add_edges(g);
            auto bfs = make_bfs<decltype(g), BFS>(g);
            bfs.traverse(v_start);
            CHECK(bfs.get_path() == expected_undirected(v_start, false));
        }
        SECTION("AdjMat") {
            AdjMatUndirected g(n_nodes);
            add_edges(g);
            auto bfs = make_bfs<decltype(g), BFS>(g);
            bfs.traverse(v_start);
            CHECK(bfs.get_path() == expected_undirected(v_start, true));
        }
    }
    SECTION("Directed") {
        SECTION("AdjLists") {
            AdjListsDirected g(n_nodes);
            add_edges(g);
            auto bfs = make_bfs<decltype(g), BFS>(g);
            bfs.traverse(v_start);
            CHECK(bfs.get_path() == expected_directed(v_start));
        }
        SECTION("AdjMat") {
            AdjMatDirected g(n_nodes);
            add_edges(g);
            auto bfs = make_bfs<decltype(g), BFS>(g);
            bfs.traverse(v_start);
            CHECK(bfs.get_path() == expected_directed(v_start));
        }
    }
}
