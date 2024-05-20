#include <vector>

template <typename Graph, bool verbose = false, bool save_path = false>
class DFS
{
    Graph g;
    std::vector<int> path;

    void dfs(int v, std::vector<bool> &visited)
    {
        if constexpr (verbose)
        {
            std::cout << "visiting v: " << v << std::endl;
        }
        visited[v] = true;
        if constexpr (save_path)
        {
            path.push_back(v);
        }
        for (auto v_nb : g.get_nb_vec(v))
        {
            if (!visited[v_nb])
            {
                dfs(v_nb, visited);
            }
        }
    }

public:
    explicit DFS(const Graph &g) : g(g)
    {
    }

    void traverse(int v_start)
    {
        std::vector<bool> visited(g.get_n_nodes(), false);
        dfs(v_start, visited);
    }

    const std::vector<int> &get_path() const
    {
        return path;
    }

    void print_path() const
    {
        for (auto v : path)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
};
