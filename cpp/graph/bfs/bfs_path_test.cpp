#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <algorithm>
#include <ranges>
#include <vector>

#include <dfs/dfs_path.h>
#include <repr/graph.h>

#include "bfs_path.h"

template <typename Graph> void add_edges(Graph &g) {
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 5);
    g.add_edge(5, 6);
    g.add_edge(4, 6);
    g.add_edge(2, 7);
    g.add_edge(6, 7);
}

std::vector<int> expected_undirected(int v_dest) {
    if (v_dest == 7) {
        return {0, 2, 7};
    } else if (v_dest == 6) {
        return {0, 1, 4, 6};
    } else {
        return {};
    }
}

std::vector<int> expected_directed(int v_dest) {
    if (v_dest == 7) {
        return {0, 2, 7};
    } else if (v_dest == 6) {
        return {0, 1, 4, 6};
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

template <typename GraphRepr>
size_t min_dfs_path_length(const GraphRepr &g, int v_start, int v_dest) {
    auto dfs_paths = DFSAllPaths<GraphRepr, false>(g);
    dfs_paths.traverse(v_start, v_dest);
    auto cmp = [](const std::vector<int> &v1, const std::vector<int> &v2) {
        return v1.size() < v2.size();
    };
    auto dfs_path_vec = dfs_paths.get_paths();
    auto min_length_vec_it = std::ranges::min_element(dfs_path_vec, cmp);
    auto min_length = min_length_vec_it->size();
    dfs_paths.print_paths();
    return min_length;
}

TEST_CASE("BFS Path") {
    constexpr int n_nodes = 9;

    int v_start = 0;
    int v_dest = GENERATE(6, 7);

    SECTION("Undirected") {
        SECTION("AdjLists") {
            AdjListsUndirected g(n_nodes);
            add_edges(g);
            auto bfs = make_bfs<decltype(g), BFSPath>(g);
            bfs.traverse(v_start, v_dest);
            auto expected_path = expected_undirected(v_dest);
            CHECK(bfs.get_path() == expected_path);
            auto min_length = min_dfs_path_length(g, v_start, v_dest);
            CHECK(min_length == expected_path.size());
        }
        SECTION("AdjMat") {
            AdjMatUndirected g(n_nodes);
            add_edges(g);
            auto bfs = make_bfs<decltype(g), BFSPath>(g);
            bfs.traverse(v_start, v_dest);
            auto expected_path = expected_undirected(v_dest);
            CHECK(bfs.get_path() == expected_path);
            auto min_length = min_dfs_path_length(g, v_start, v_dest);
            CHECK(min_length == expected_path.size());
        }
    }
    SECTION("Directed") {
        SECTION("AdjLists") {
            AdjListsDirected g(n_nodes);
            add_edges(g);
            auto bfs = make_bfs<decltype(g), BFSPath>(g);
            bfs.traverse(v_start, v_dest);
            auto expected_path = expected_directed(v_dest);
            CHECK(bfs.get_path() == expected_path);
            auto min_length = min_dfs_path_length(g, v_start, v_dest);
            CHECK(min_length == expected_path.size());
        }
        SECTION("AdjMat") {
            AdjMatDirected g(n_nodes);
            add_edges(g);
            auto bfs = make_bfs<decltype(g), BFSPath>(g);
            bfs.traverse(v_start, v_dest);
            auto expected_path = expected_directed(v_dest);
            CHECK(bfs.get_path() == expected_path);
            auto min_length = min_dfs_path_length(g, v_start, v_dest);
            CHECK(min_length == expected_path.size());
        }
    }
}
