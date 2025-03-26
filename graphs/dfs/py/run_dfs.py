import dfs

def main():
    g = dfs.Graph(5)
    g.add_edge(0, 1)
    g.add_edge(1, 3)
    g.add_edge(1, 2)
    g.add_edge(3, 4)
    g.print()
    d = dfs.DFS(g)
    d.dfs(0)

main()
