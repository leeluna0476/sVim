#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "skip_list.h"

int
main(void)
{
    skip_list_T *list = initialize_skip_list(0);
    skip_list_T *tmp = NULL;

    for (int i = 0; i < 100; i++)
    {
        tmp = insert_node(list, i, "hello");
        if (!tmp)
        {
            return 0;
        }

        list = tmp;
    }

    skip_list_T *header = list;
    while (header)
    {
        tmp = header;
        printf("{\n");
        while (tmp)
        {
            printf("\t{ [level]: %d [key]: %zu [data]: %s }\n", tmp->_level, tmp->_key, tmp->_data);
            tmp = tmp->next;
        }
        printf("}\n");
        header = header->down;
    }

    skip_list_T *searched_node = search_node(list, 33);
    printf("search: { [level]: %d [key]: %zu [data]: %s }\n", searched_node->_level, searched_node->_key, searched_node->_data);

    return 0;
}
