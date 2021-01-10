#include "graph.h"
#include "csv.h"

int main()
{
    graph *g = graph_create();

    linked_list **columns = read_dh_stanford_edges();

    linked_list_node *current_start = columns[0]->head;
    linked_list_node *current_target = columns[1]->head;
    linked_list_node *current_weight = columns[2]->head;

    while (current_start)
    {
        graph_add_edge(g,
                       *(int *)current_start->data,
                       *(int *)current_target->data,
                       *(int *)current_weight->data,
                       0);
        current_start = current_start->next;
        current_target = current_target->next;
        current_weight = current_weight->next;
    }

    linked_list *determined_vertices = graph_dijkstra(g, 1);

    graph_print_dijkstra_results(determined_vertices);

    graph_print_adjacency_lists(g);

    return 0;
}