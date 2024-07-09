#include "graph.h"

#include <random>

class Choice
{
    std::random_device rand_dev;
    std::mt19937 generator;
    std::bernoulli_distribution distr;

public:
    explicit Choice(double p) : generator(rand_dev()), distr(p) {}

    bool draw() { return distr(generator); }
};

template <typename GraphRepr>
class RandGraph : public Graph<GraphRepr>
{
    Choice choice;

public:
    explicit RandGraph(int n_nodes, double p) : Graph<GraphRepr>(n_nodes), choice(p)
    {
    }

    void add_edges()
    {
        for (int v1 = 0; v1 < GraphRepr::get_n_nodes(); ++v1)
        {
            for (int v2 = 0; v2 < GraphRepr::get_n_nodes(); ++v2)
            {
                if (v1 == v2)
                {
                    continue;
                }
                bool add = choice.draw();
                if (add)
                {
                    GraphRepr::add_edge(v1, v2);
                }
            }
        }
    }
};