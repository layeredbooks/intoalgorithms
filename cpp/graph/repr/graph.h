#include <vector>
#include <iostream>
#include <string>

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

    std::vector<int> get_nb_vec(int v)
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

using AdjMatUndirected = AdjMat<false>;
using AdjMatDirected = AdjMat<true>;

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
    friend std::ostream &operator<<(std::ostream &os, const AdjLists<directed> &g);
};

using AdjListsUndirected = AdjLists<false>;
using AdjListsDirected = AdjLists<true>;

template <typename Graph>
void print(const Graph &g)
{
    for (int v = 0; v < g.get_n_nodes(); v++)
    {
        std::string delim = " ->";
        std::cout << v << delim;
        auto nb_vec = g.get_nb_vec(v);
        for (auto nb : nb_vec)
        {
            std::string space = " ";
            std::cout << space << nb;
        }
        std::cout << std::endl;
    }
}
