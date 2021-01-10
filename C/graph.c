#include "graph.h"

int main()
{
    graph *g = graph_create();

    graph_add_edge(g, 1, 2, 7, 1);
    graph_add_edge(g, 1, 3, 20, 1);
    graph_add_edge(g, 2, 5, 10, 1);
    graph_add_edge(g, 3, 5, 33, 1);
    graph_add_edge(g, 3, 4, 20, 1);
    graph_add_edge(g, 2, 4, 50, 1);
    graph_add_edge(g, 4, 5, 20, 1);
    graph_add_edge(g, 5, 6, 1, 1);
    graph_add_edge(g, 4, 6, 2, 1);

    graph_print_adjacency_lists(g);

    linked_list *determined_vertices = graph_dijkstra(g, 1);

    graph_print_dijkstra_results(determined_vertices);

    graph_delete(g);
    return 0;
}