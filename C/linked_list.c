#include "linked_list.h"

int main()
{
    linked_list *my_linked_list = linked_list_create();
    int one = 1;
    int two = 2;
    linked_list_insert(my_linked_list, 1, &one, -1);
    linked_list_insert(my_linked_list, 2, &two, -1);
    linked_list_print(my_linked_list);
    return 0;
}