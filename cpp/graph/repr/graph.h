#pragma once

#include "graph_repr.h"

#include <cstdlib>

#include <iostream>
#include <fstream>

#include <string>
#include <string_view>

#include <set>

template <typename GraphRepr>
class Graph : public GraphRepr
{
public:
    explicit Graph(int n_nodes) : GraphRepr(n_nodes) {}

    void print() const
    {
        for (int v = 0; v < GraphRepr::get_n_nodes(); v++)
        {
            std::cout << v << " -> ";
            for (auto nb : GraphRepr::get_nb_vec(v))
            {
                std::cout << " " << nb;
            }
            std::cout << std::endl;
        }
    }

    void draw(std::string_view name) const
    {
        constexpr bool directed = []
        {
            if constexpr (std::is_same_v<GraphRepr, AdjListsDirected> || std::is_same_v<GraphRepr, AdjMatDirected>)
                return true;
            else
                return false;
        }();
        std::string gv_file_name = std::string(name) + ".gv";
        write_to_gv_file<directed>(gv_file_name);
        std::string png_file_name = std::string(name) + ".png";
        make_png_file(gv_file_name, png_file_name);
    }

private:
    void write_gv_directed(std::ofstream &file, std::string_view delimiter) const
    {
        std::set<int> nodes;
        for (int v = 0; v < GraphRepr::get_n_nodes(); v++)
        {
            for (auto nb : GraphRepr::get_nb_vec(v))
            {
                file << v << " " << delimiter << " " << nb << std::endl;
                nodes.insert(v);
                nodes.insert(nb);
            }
        }
        for (int v = 0; v < GraphRepr::get_n_nodes(); v++)
        {
            if (!nodes.contains(v))
            {
                file << v << std::endl;
            }
        }
    }

    void write_gv_undirected(std::ofstream &file, std::string_view delimiter) const
    {
        std::set<std::pair<int, int>> edges;
        std::set<int> nodes;
        for (int v = 0; v < GraphRepr::get_n_nodes(); v++)
        {
            for (auto nb : GraphRepr::get_nb_vec(v))
            {
                if (edges.contains({v, nb}))
                {
                    continue;
                }
                file << v << " " << delimiter << " " << nb << std::endl;
                edges.insert({v, nb});
                edges.insert({nb, v});
                nodes.insert(v);
                nodes.insert(nb);
            }
        }
        for (int v = 0; v < GraphRepr::get_n_nodes(); v++)
        {
            if (!nodes.contains(v))
            {
                file << v << std::endl;
            }
        }
    }

    template <bool directed>
    void write_to_gv_file(std::string_view file_name) const
    {
        std::ofstream file;
        file.open(file_name);
        constexpr std::string delimiter = directed ? "->" : "--";
        file << (directed ? "digraph" : "graph") << " {" << std::endl;
        if constexpr (directed)
        {
            write_gv_directed(file, delimiter);
        }
        else
        {
            write_gv_undirected(file, delimiter);
        }
        file << "}" << std::endl;
        file.close();
    }

    void make_png_file(std::string_view gv_file_name, std::string_view png_file_name) const
    {
        std::string cmd = "dot " + std::string(gv_file_name) + " -Tpng -o " + std::string(png_file_name);
        // https://stackoverflow.com/questions/13417411/laying-out-a-large-graph-with-graphviz
        // std::string cmd = "sfdp -x -Goverlap=scale -Tpng " + std::string(gv_file_name) + " > " + std::string(png_file_name);
        int res = std::system(cmd.c_str());
        if (res != 0)
        {
            std::cerr << "could not execute cmd: " << cmd << std::endl;
        }
    }
};
