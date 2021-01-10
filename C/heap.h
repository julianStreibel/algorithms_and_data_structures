#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct heap_item
{
    int key;
    double sort_key;
    void *data;
} heap_item;

typedef struct heap
{
    heap_item *heap_array;
    int size;
} heap;

heap *heap_create(int size)
{
    heap *new_heap = (heap *)malloc(sizeof(heap));
    new_heap->heap_array = (heap_item *)malloc(sizeof(heap_item) * size);
    new_heap->size = 0;
    return new_heap;
}

int heap_parent(int i)
{
    return floor(i / 2);
}

int heap_left(int i)
{
    return 2 * i;
}

int heap_right(int i)
{
    return 2 * i + 1;
}

void heap_decrease_sort_key(heap *heap_to_decrease_sort_key, int index, double new_sort_key)
{
    if (new_sort_key > heap_to_decrease_sort_key->heap_array[index].sort_key)
    {
        printf("New sort key larger than current sort key. %f -> %f\n",
               heap_to_decrease_sort_key->heap_array[index].sort_key, new_sort_key);
        return;
    }
    heap_to_decrease_sort_key->heap_array[index].sort_key = new_sort_key;
    while (index > 0 &&
           heap_to_decrease_sort_key->heap_array[heap_parent(index)].sort_key > heap_to_decrease_sort_key->heap_array[index].sort_key)
    {
        heap_item tmp = heap_to_decrease_sort_key->heap_array[heap_parent(index)];
        heap_to_decrease_sort_key->heap_array[heap_parent(index)] = heap_to_decrease_sort_key->heap_array[index];
        heap_to_decrease_sort_key->heap_array[index] = tmp;
        index = heap_parent(index);
    }
}

void heap_insert(heap *heap_to_insert_in, int key, double sort_key, void *data)
{
    heap_to_insert_in->size++;
    heap_to_insert_in->heap_array[heap_to_insert_in->size - 1].key = key;
    heap_to_insert_in->heap_array[heap_to_insert_in->size - 1].sort_key = INFINITY;
    heap_to_insert_in->heap_array[heap_to_insert_in->size - 1].data = data;
    heap_decrease_sort_key(heap_to_insert_in, heap_to_insert_in->size - 1, sort_key);
}

void heap_min_heapify(heap *heap_to_min_heapify, int index)
{
    int left = heap_left(index);
    int right = heap_right(index);
    int smallest = index;

    if (left < heap_to_min_heapify->size &&
        heap_to_min_heapify->heap_array[left].sort_key < heap_to_min_heapify->heap_array[index].sort_key)
        smallest = left;

    if (right < heap_to_min_heapify->size &&
        heap_to_min_heapify->heap_array[right].sort_key < heap_to_min_heapify->heap_array[smallest].sort_key)
        smallest = right;
    if (smallest != index)
    {
        heap_item tmp = heap_to_min_heapify->heap_array[index];
        heap_to_min_heapify->heap_array[index] = heap_to_min_heapify->heap_array[smallest];
        heap_to_min_heapify->heap_array[smallest] = tmp;
        heap_min_heapify(heap_to_min_heapify, smallest);
    }
}

heap_item heap_extract_min(heap *heap_to_extract_min_from)
{
    if (heap_to_extract_min_from->size < 1)
    {
        printf("Heap underflow.\n");
    }
    heap_item min = heap_to_extract_min_from->heap_array[0];
    heap_to_extract_min_from->heap_array[0] = heap_to_extract_min_from->heap_array[heap_to_extract_min_from->size - 1];
    heap_to_extract_min_from->size--;
    heap_min_heapify(heap_to_extract_min_from, 0);
    return min;
}

int heap_get_index_of_key(heap *heap_to_find_key_in, int key)
{

    int index = 0;
    while (index < heap_to_find_key_in->size)
    {
        if (heap_to_find_key_in->heap_array[index].key == key)
        {
            return index;
        }
        index++;
    }
    return -1;
}

void heap_delete(heap *heap_to_delete)
{
    int i = 0;
    while (i < heap_to_delete->size)
    {
        free(heap_to_delete->heap_array[i].data);
    }
    free(heap_to_delete->heap_array);
    free(heap_to_delete);
    return;
}