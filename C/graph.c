#include "graph.h"

int main()
{
    graph *g = create_graph();
    graph_add_edge(g, 1, 2, 4, 0);
    graph_add_edge(g, 4, 2, 3, 0);
    graph_add_edge(g, 4, 5, 6, 0);
    graph_add_edge(g, 1, 5, 3, 0);
    graph_add_edge(g, 3, 2, 4, 0);
    graph_add_edge(g, 3, 4, 1, 0);
    graph_add_edge(g, 5, 2, 9, 0);

    graph_print_adjacency_list(g);
}