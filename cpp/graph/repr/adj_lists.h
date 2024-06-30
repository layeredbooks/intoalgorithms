#pragma once

#include <vector>

template <bool directed = false>
class AdjLists
{
    std::vector<std::vector<int>> adj_lists;

    void add_edge_directed(int v_from, int v_to)
    {
        adj_lists[v_from].push_back(v_to);
    }

public:
    explicit AdjLists(int n_nodes) : adj_lists(n_nodes)
    {
    }

    void add_edge(int v1, int v2)
    {
        add_edge_directed(v1, v2);
        if constexpr (!directed)
        {
            add_edge_directed(v2, v1);
        }
    }

    int get_n_nodes() const
    {
        return static_cast<int>(adj_lists.size());
    }

    const std::vector<int> &get_nb_vec(int v) const
    {
        return adj_lists[v];
    }
};
