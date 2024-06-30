#include "graph.h"

int main()
{
    using GraphRepr = AdjMatDirected;
    Graph<GraphRepr> g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 3);
    g.print();
    g.draw("test");
    return 0;
}