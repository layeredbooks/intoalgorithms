#include <algorithm>
#include <optional>
#include <ranges>
#include <vector>

class BFSState {
    std::vector<int> prev;

  public:
    explicit BFSState(int n_nodes) : prev(n_nodes, -1) {}

    void set_prev(int v, int v_prev) { prev[v] = v_prev; }

    std::vector<int> compute_path(int v_start, int v_dest) {
        std::vector<int> res;
        res.push_back(v_dest);
        int v_prev = prev[v_dest];
        while (res.size() < prev.size() && v_prev != -1) {
            res.push_back(v_prev);
            if (v_prev == v_start) {
                v_prev = -1;
            } else {
                v_prev = prev[v_prev];
            }
        }
        std::ranges::reverse(res);
        return res;
    }
};

template <typename Graph, bool verbose = false, bool save_path = false>
class BFSPath {
    Graph g;

    std::vector<int> bfs_path;

    void visit(int v, std::queue<int> &q, std::vector<bool> &visited,
               std::vector<int> &distance, int distance_v) {
        if constexpr (verbose) {
            std::cout << "visiting v: " << v << std::endl;
        }
        visited[v] = true;
        distance[v] = distance_v;
        q.push(v);
    }

    std::optional<int> bfs(int v, int v_dest) {
        std::queue<int> q;
        std::vector<bool> visited(g.get_n_nodes(), false);
        std::vector<int> distance(g.get_n_nodes(), -1);
        BFSState state(g.get_n_nodes());
        visit(v, q, visited, distance, 0);
        while (!q.empty()) {
            auto v_q = q.front();
            q.pop();
            for (auto v_nb : g.get_nb_vec(v_q)) {
                if (!visited[v_nb]) {
                    if constexpr (save_path) {
                        state.set_prev(v_nb, v_q);
                    }
                    auto dist = distance[v_q] + 1;
                    if (v_nb == v_dest) {
                        if constexpr (save_path) {
                            bfs_path = state.compute_path(v, v_dest);
                        }
                        return dist;
                    }
                    visit(v_nb, q, visited, distance, dist);
                }
            }
        }
        return std::nullopt;
    }

  public:
    explicit BFSPath(const Graph &g) : g(g) {}

    std::optional<int> traverse(int v_start, int v_dest) {
        return bfs(v_start, v_dest);
    }

    std::vector<int> get_path() const { return bfs_path; }

    void print_path(const std::vector<int> &path) const {
        for (auto v : path) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
};
