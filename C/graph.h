#include "linked_list.h"

typedef struct graph
{
    linked_list *nodes;
} graph;

typedef struct vertex
{
    int key;
    linked_list *adjacency_list;
} vertex;

graph *create_graph()
{
    graph *new_graph = (graph *)malloc(sizeof(graph));
    new_graph->nodes = linked_list_create();
    return new_graph;
}

vertex *vertex_create(int key)
{
    vertex *new_vertex = malloc(sizeof(vertex));
    new_vertex->key = key;
    new_vertex->adjacency_list = linked_list_create();
    return new_vertex;
}

void vertex_print(linked_list_node *node)
{
    vertex *vertex = node->data;
    printf("%d: ", vertex->key);
    linked_list_print(vertex->adjacency_list);
    printf("\n");
}

void graph_print_adjacency_lists(graph *graph_to_print)
{
    printf("key, adjacency_list\n");
    linked_list_map(graph_to_print->nodes, *vertex_print);
}

void graph_add_edge(graph *graph_to_add_edge, int key_v, int key_u, double weight, int directed)
{
    if (!linked_list_contains(graph_to_add_edge->nodes, key_v))
    {
        vertex *vertex_v = vertex_create(key_v);
        linked_list_insert(graph_to_add_edge->nodes, key_v, vertex_v, 0);
    }
    if (!linked_list_contains(graph_to_add_edge->nodes, key_u))
    {
        vertex *vertex_u = vertex_create(key_u);
        linked_list_insert(graph_to_add_edge->nodes, key_u, vertex_u, 0);
    }

    vertex *vertex_v = linked_list_get_data_with_key(graph_to_add_edge->nodes, key_v);
    if (!linked_list_contains(vertex_v->adjacency_list, key_u))
    {
        linked_list_insert(vertex_v->adjacency_list, key_u, &weight, 0);
    }
    if (!directed && linked_list_contains(graph_to_add_edge->nodes, key_u))
    {
        vertex *vertex_u = linked_list_get_data_with_key(graph_to_add_edge->nodes, key_u);

        if (!linked_list_contains(vertex_u->adjacency_list, key_v))
        {
            linked_list_insert(vertex_u->adjacency_list, key_v, &weight, 0);
        }
    }
}
