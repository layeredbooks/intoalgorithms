#include "rand_graph.h"

int main()
{
    using GraphRepr = AdjMatUndirected;
    RandGraph<GraphRepr> g(20, 0.05);
    g.add_edges();
    // g.add_edge(0, 1);
    // g.add_edge(1, 3);
    g.print();
    g.draw("test");
    return 0;
}