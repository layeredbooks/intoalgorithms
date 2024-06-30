#pragma once

#include <vector>

template <bool directed = false>
class AdjMat
{
    std::vector<std::vector<int>> adj_mat;

    void add_edge_directed(int v_from, int v_to)
    {
        adj_mat[v_from][v_to] = 1;
    }

public:
    explicit AdjMat(int n_nodes) : adj_mat(n_nodes, std::vector<int>(n_nodes, 0))
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
        return static_cast<int>(adj_mat.size());
    }

    std::vector<int> get_nb_vec(int v) const
    {
        std::vector<int> res;
        for (int col = 0; col < get_n_nodes(); col++)
        {
            if (adj_mat[v][col] > 0)
            {
                res.push_back(col);
            }
        }
        return res;
    }
};
