#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "linked_list.h"

#define MAXCHAR 1000

linked_list **read_dh_stanford_edges()
{
    FILE *file = fopen("../Data/Graph/dh_stanford_edges.csv", "r");

    char buf[MAXCHAR];
    linked_list **columns = (linked_list **)malloc(sizeof(linked_list *) * 4);
    int i = 0;
    while (i < 3)
    {
        columns[i] = linked_list_create();
        i++;
    }
    fgets(buf, sizeof(buf), file);
    while (fgets(buf, sizeof(buf), file))
    {
        int *id = (int *)malloc(sizeof(int));
        int *s = (int *)malloc(sizeof(int));
        int *t = (int *)malloc(sizeof(int));
        int *w = (int *)malloc(sizeof(int));
        sscanf(buf, "%d,%d,%d,%d", id, s, t, w);
        linked_list_insert(columns[0], *id, s, -1);
        linked_list_insert(columns[1], *id, t, -1);
        linked_list_insert(columns[2], *id, w, -1);
    }

    fclose(file);
    return columns;
}