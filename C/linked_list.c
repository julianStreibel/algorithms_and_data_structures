#include "linked_list.h"

int main()
{
    linked_list *l = linked_list_create();
    int i = 0;
    while (i < 10)
    {
        linked_list_insert(l, i, &i, -1);
        i++;
    }

    printf("Before:\n");
    linked_list_print(l);

    printf("After:\n");
    linked_list_reverse(l);
    linked_list_print(l);

    return 0;
}