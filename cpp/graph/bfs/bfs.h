#include <queue>
#include <vector>

template <typename Graph, bool verbose = false, bool save_path = false>
class BFS
{
    Graph g;
    std::vector<int> path;

    void visit(int v, std::queue<int> &q, std::vector<bool> &visited)
    {
        if constexpr (verbose)
        {
            std::cout << "visiting v: " << v << std::endl;
        }
        visited[v] = true;
        q.push(v);
        if constexpr (save_path)
        {
            path.push_back(v);
        }
    }

    void bfs(int v)
    {
        std::queue<int> q;
        std::vector<bool> visited(g.get_n_nodes(), false);
        visit(v, q, visited);
        while (!q.empty())
        {
            auto v_q = q.front();
            q.pop();
            for (auto v_nb : g.get_nb_vec(v_q))
            {
                if (!visited[v_nb])
                {
                    visit(v_nb, q, visited);
                }
            }
        }
    }

public:
    explicit BFS(const Graph &g) : g(g)
    {
    }

    void traverse(int v_start)
    {
        bfs(v_start);
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
