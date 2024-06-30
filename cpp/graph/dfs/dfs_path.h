#include <vector>

template <typename Graph, bool verbose = false>
class DFSPath
{
    Graph g;

    struct DFSState
    {
        std::vector<int> path;
        std::vector<bool> in_path;
    };

    DFSState dfs_state;

    bool
    dfs(int v, int v_dest, DFSState &state)
    {
        if constexpr (verbose)
        {
            std::cout << "visiting v: " << v << std::endl;
        }
        if (v == v_dest)
        {
            return true;
        }
        for (auto v_nb : g.get_nb_vec(v))
        {
            if (!state.in_path[v_nb])
            {
                state.path.push_back(v_nb);
                state.in_path[v_nb] = true;
                auto found = dfs(v_nb, v_dest, state);
                if (found)
                {
                    return true;
                }
                state.path.pop_back();
                state.in_path[v_nb] = false;
            }
        }
        return false;
    }

public:
    explicit DFSPath(const Graph &g) : g(g)
    {
    }

    bool traverse(int v_start, int v_dest)
    {
        dfs_state.path.clear();
        dfs_state.in_path.assign(g.get_n_nodes(), false);
        dfs_state.path.push_back(v_start);
        dfs_state.in_path[v_start] = true;
        return dfs(v_start, v_dest, dfs_state);
    }

    const std::vector<int> &get_path() const
    {
        return dfs_state.path;
    }

    void print_path() const
    {
        for (auto v : dfs_state.path)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
};

template <typename Graph, bool verbose = false>
class DFSAllPaths
{
    Graph g;

    struct DFSState
    {
        std::vector<int> path;
        std::vector<bool> in_path;
        std::vector<std::vector<int>> paths;
    };

    DFSState dfs_state;

    void dfs(int v, int v_dest, DFSState &state)
    {
        if constexpr (verbose)
        {
            std::cout << "visiting v: " << v << std::endl;
        }
        if (v == v_dest)
        {
            state.paths.push_back(state.path);
            return;
        }
        for (auto v_nb : g.get_nb_vec(v))
        {
            if (!state.in_path[v_nb])
            {
                state.path.push_back(v_nb);
                state.in_path[v_nb] = true;
                dfs(v_nb, v_dest, state);
                state.path.pop_back();
                state.in_path[v_nb] = false;
            }
        }
    }

    void print_path(const std::vector<int> &path) const
    {
        for (auto v : path)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

public:
    explicit DFSAllPaths(const Graph &g) : g(g)
    {
    }

    void traverse(int v_start, int v_dest)
    {
        dfs_state.path.clear();
        dfs_state.in_path.assign(g.get_n_nodes(), false);
        dfs_state.paths.clear();
        dfs_state.path.push_back(v_start);
        dfs_state.in_path[v_start] = true;
        dfs(v_start, v_dest, dfs_state);
    }

    const std::vector<std::vector<int>> &get_paths() const
    {
        return dfs_state.paths;
    }

    void print_paths() const
    {
        for (const auto &path : dfs_state.paths)
        {
            print_path(path);
        }
    }
};
