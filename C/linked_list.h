#include <stdlib.h>
#include <stdio.h>

typedef struct linked_list_node linked_list_node;

typedef struct linked_list
{
    linked_list_node *head;
} linked_list;

struct linked_list_node
{
    int key;
    double data;
    linked_list_node *next;
    linked_list *llist;
};

linked_list *
linked_list_create()
{
    linked_list *new_linked_list = (linked_list *)malloc(sizeof(linked_list));
    new_linked_list->head = NULL;
    return new_linked_list;
}

void linked_list_insert(linked_list *linked_list_to_insert, int new_key, double new_data, int position)
{
    linked_list_node *new_node = (linked_list_node *)malloc(sizeof(linked_list_node));
    new_node->key = new_key;
    new_node->data = new_data;
    new_node->next = NULL;

    if (!linked_list_to_insert->head)
    {
        linked_list_to_insert->head = new_node;
        return;
    }

    if (position == 0)
    {
        new_node->next = linked_list_to_insert->head;
        linked_list_to_insert->head = new_node;
        return;
    }

    linked_list_node *current = linked_list_to_insert->head;
    int i = 0;
    while (current->next && (position != i + 1 || position == -1))
    {
        current = current->next;
        i++;
    }
    new_node->next = current->next;
    current->next = new_node;
    return;
}

linked_list *linked_list_get_llist_with_key(linked_list *linked_list_to_get_from, int key)
{
    linked_list_node *current = linked_list_to_get_from->head;
    while (current && current->key != key)
    {
        current = current->next;
        if (current && current->key == key)
        {
            return current->llist;
        }
    }
    return NULL;
}

void linked_list_insert_in_llist_with_key(linked_list *linked_list_to_insert_in_llist, int key_of_node_with_llist, int new_key, double new_data)
{
    if (linked_list_to_insert_in_llist)
    {
        linked_list_node *current = linked_list_to_insert_in_llist->head;
        while (current->key != key_of_node_with_llist && current->next)
        {
            current = current->next;
        }
        if (current->key == key_of_node_with_llist)
        {
            if (!current->llist)
            {
                current->llist = linked_list_create();
            }
            linked_list_insert(current->llist, new_key, new_data, 0);
        }
    }
}

int linked_list_contains(linked_list *linked_list_to_check, int key)
{
    if (!linked_list_to_check)
    {
        return 0;
    }
    linked_list_node *current = linked_list_to_check->head;
    while (current)
    {
        if (current->key == key)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int linked_list_llist_from_contains(linked_list *linked_list_to_check, int key_from, int key)
{
    linked_list *containing_linked_list = linked_list_get_llist_with_key(linked_list_to_check, key_from);
    if (containing_linked_list)
    {
        return linked_list_contains(containing_linked_list, key);
    }
    else
    {
        return 0;
    }
}

void linked_list_remove_item_at_position(linked_list *linked_list_to_remove_item, int position)
{
    if (!linked_list_to_remove_item->head)
    {
        return;
    }

    linked_list_node *current = linked_list_to_remove_item->head;

    if (position == 0)
    {
        linked_list_node *new_next = current->next;
        free(current);
        free(current->llist);
        linked_list_to_remove_item->head = new_next;
        return;
    }

    int i = 0;
    while (current->next->next && (position != i + 1 || position == -1))
    {
        current = current->next;
        i++;
    }
    if (current->next && current->next->next)
    {
        linked_list_node *new_next = current->next->next;
        free(current->next->llist);
        free(current->next);
        current->next = new_next;
        return;
    }
    free(current->next->llist);
    free(current->next);
    current->next = NULL;
    return;
}

void linked_list_delete(linked_list *linked_list_to_delete)
{
    linked_list_node *current = linked_list_to_delete->head;
    linked_list_node *node_to_delete;
    free(linked_list_to_delete);
    while (current)
    {
        node_to_delete = current;
        free(node_to_delete->llist);
        current = current->next;
        free(node_to_delete);
    }
}

void linked_list_map(linked_list *linked_list_to_map, void (*func)(linked_list_node *))
{
    if (!linked_list_to_map || !linked_list_to_map->head)
    {
        return;
    }
    linked_list_node *current = linked_list_to_map->head;
    while (current->next)
    {
        (*func)(current);
        current = current->next;
    }
    (*func)(current);
    return;
}

void linked_list_llist_print_key(linked_list_node *node)
{
    printf("%d ", node->key);
}

void linked_list_print_key(linked_list_node *node)
{
    printf("%d ", node->key);
    if (node->llist)
    {
        printf(":");
        linked_list_map(node->llist, *linked_list_llist_print_key);
    }
    printf("\n");
}

void linked_list_print(linked_list *linked_list_to_print)
{
    if (linked_list_to_print)
    {
        linked_list_map(linked_list_to_print, *linked_list_print_key);
    }
}