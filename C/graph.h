#include "linked_list.h"

typedef struct graph
{
    linked_list *adjacency_list;
} graph;

graph *create_graph()
{
    graph *new_graph = (graph *)malloc(sizeof(graph));
    new_graph->adjacency_list = (linked_list *)malloc(sizeof(linked_list));
    return new_graph;
}

void graph_print_adjacency_list(graph *graph_to_print)
{
    linked_list_print(graph_to_print->adjacency_list);
}

void graph_add_edge(graph *graph_to_add_edges, int v, int u, double weight, int directed)
{
    if (!linked_list_contains(graph_to_add_edges->adjacency_list, v))
    {
        linked_list_insert(graph_to_add_edges->adjacency_list, v, 0, -1);
    }
    if (!linked_list_contains(graph_to_add_edges->adjacency_list, u))
    {
        linked_list_insert(graph_to_add_edges->adjacency_list, u, 0, -1);
    }
    linked_list_insert_in_llist_with_key(graph_to_add_edges->adjacency_list, v, u, weight);
    if (!directed)
    {
        linked_list_insert_in_llist_with_key(graph_to_add_edges->adjacency_list, u, v, weight);
    }
}
