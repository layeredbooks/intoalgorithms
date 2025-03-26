class Graph:

    def __init__(self, n):
        self.adj_lists = []
        for _ in range(n):
            self.adj_lists.append([])

    def add_edge(self, v1, v2):
        self.adj_lists[v1].append(v2)

    def get_n_nodes(self):
        return len(self.adj_lists)
    
    def get_nb_vec(self, v):
        return self.adj_lists[v]

    def print(self):
        for v in range(self.get_n_nodes()):
            msg = f'{v} ->'
            for v_nb in self.get_nb_vec(v):
                msg += f' {v_nb}'
            print(msg)
class DFS:
    
    def __init__(self, g):
        self.g = g

    def _dfs_aux(self, v, visited, path):
        visited[v] = True
        path.append(v)
        for v_nb in self.g.get_nb_vec(v):
            if not visited[v_nb]:
                self._dfs_aux(v_nb, visited, path)

    def dfs(self, v):
        visited = [False] * self.g.get_n_nodes()
        path = []
        self._dfs_aux(v, visited, path)
        print(*path)
