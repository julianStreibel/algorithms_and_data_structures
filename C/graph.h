#include <math.h>
#include "linked_list.h"
#include "heap.h"

typedef struct graph
{
    linked_list *vertices;
    int size;
} graph;

graph *graph_create()
{
    graph *new_graph = (graph *)malloc(sizeof(graph));
    new_graph->vertices = linked_list_create();
    new_graph->size = 0;
    return new_graph;
}

void graph_vertex_print(linked_list_node *node)
{
    printf("%d: ", node->key);
    linked_list_print(node->data);
}

void graph_print_adjacency_lists(graph *graph_to_print)
{
    printf("key, adjacency_list\n");
    linked_list_map(graph_to_print->vertices, *graph_vertex_print);
}

void graph_add_edge(graph *graph_to_add_edge, int key_v, int key_u, double weight, int directed)
{
    double *weight_ptr = malloc(sizeof(double));
    weight_ptr[0] = weight;
    if (!linked_list_contains(graph_to_add_edge->vertices, key_v))
    {
        linked_list_insert(graph_to_add_edge->vertices, key_v, linked_list_create(), 0);
        graph_to_add_edge->size++;
    }
    if (!linked_list_contains(graph_to_add_edge->vertices, key_u))
    {
        linked_list_insert(graph_to_add_edge->vertices, key_u, linked_list_create(), 0);
        graph_to_add_edge->size++;
    }

    linked_list *adjacency_list_of_v = linked_list_get_data_with_key(graph_to_add_edge->vertices, key_v);
    if (!linked_list_contains(adjacency_list_of_v, key_u))
    {
        linked_list_insert(adjacency_list_of_v, key_u, weight_ptr, 0);
    }
    if (!directed)
    {
        linked_list *adjacency_list_of_u = linked_list_get_data_with_key(graph_to_add_edge->vertices, key_u);

        if (!linked_list_contains(adjacency_list_of_u, key_v))
        {
            linked_list_insert(adjacency_list_of_u, key_v, weight_ptr, 0);
        }
    }
}

heap *graph_initialize_single_source_shortest_path(graph *graph_to_init, int *key_of_start_node)
{
    heap *vertices_heap = heap_create(graph_to_init->size);
    linked_list_node *current = graph_to_init->vertices->head;
    while (current)
    {
        // {shortest-path estimate, predecessor key}
        double *vertex_data = malloc(sizeof(double) * 2);
        vertex_data[0] = INFINITY;
        vertex_data[1] = -INFINITY;
        if (current->key == *key_of_start_node)
        {
            vertex_data[0] = 0;
        }
        heap_insert(vertices_heap, current->key, vertex_data[0], vertex_data);
        current = current->next;
    }
    return vertices_heap;
}

void graph_relax(double *u, int u_key, int v_key, heap *vertices_q, double *weight)
{
    int index_of_v = heap_get_index_of_key(vertices_q, v_key);
    double *v = vertices_q->heap_array[index_of_v].data;
    if (v[0] > u[0] + *weight)
    {
        v[0] = u[0] + *weight;
        v[1] = u_key;
        heap_decrease_sort_key(vertices_q, index_of_v, v[0]);
    }
}

linked_list *graph_dijkstra(graph *graph_with_start_node, int key_of_start_node)
{
    heap *vertices_q = graph_initialize_single_source_shortest_path(graph_with_start_node, &key_of_start_node);
    linked_list *determined_vertices = linked_list_create();
    while (vertices_q->size > 0)
    {
        heap_item u = heap_extract_min(vertices_q);
        linked_list_insert(determined_vertices, u.key, u.data, 0);

        linked_list *u_vertex_adjacency_list = linked_list_get_data_with_key(graph_with_start_node->vertices, u.key);
        linked_list_node *current_adjacent = u_vertex_adjacency_list->head;

        while (current_adjacent)
        {
            if (heap_get_index_of_key(vertices_q, current_adjacent->key) > -1)
            {
                graph_relax(u.data, u.key, current_adjacent->key, vertices_q, current_adjacent->data);
            }
            current_adjacent = current_adjacent->next;
        }
    }
    heap_delete(vertices_q);
    return determined_vertices;
}

void graph_print_dijkstra_results(linked_list *determined_vertices)
{
    linked_list_node *current = determined_vertices->head;
    while (current)
    {
        double *spe_pre = current->data;
        printf("---------------------------------\n");
        printf("Vertex: %d\n", current->key);
        printf("Shortest path estimate: %f\n", spe_pre[0]);
        printf("Predecessor:            %f\n", spe_pre[1]);
        current = current->next;
    }
}
