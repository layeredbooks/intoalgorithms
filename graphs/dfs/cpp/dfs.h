#pragma once

#include <vector>
#include <iostream>

class Graph
{
    std::vector<std::vector<int>> adj_lists;

public:
    Graph(int n) : adj_lists(n, std::vector<int>{})
    {
    }

    void add_edge(int v1, int v2)
    {
        adj_lists[v1].push_back(v2);
    }

    size_t get_n_nodes() const
    {
        return adj_lists.size();
    }

    const std::vector<int> &get_nb_vec(int v) const
    {
        return adj_lists[v];
    }

    void print() const
    {
        for (size_t v = 0; v < get_n_nodes(); ++v)
        {
            std::cout << v << "->";
            for (auto v_nb : get_nb_vec(v))
            {
                std::cout << " " << v_nb;
            }
            std::cout << std::endl;
        }
    }
};

class DFS
{
    Graph g;

    void dfs_aux(int v, std::vector<bool> &visited, std::vector<int> &path)
    {
        visited[v] = true;
        path.push_back(v);
        for (auto v_nb : g.get_nb_vec(v))
        {
            if (!visited[v_nb])
            {
                dfs_aux(v_nb, visited, path);
            }
        }
    }

public:
    DFS(Graph g) : g(g) {}

    void dfs(int v)
    {
        std::vector<bool> visited(g.get_n_nodes(), false);
        std::vector<int> path;
        dfs_aux(v, visited, path);
        for (auto v_p : path)
        {
            std::cout << v_p << " ";
        }
        std::cout << std::endl;
    }
};
