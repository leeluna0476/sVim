#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "skip_list.h"

void    leaks()
{
    system("leaks sVim");
}

int
main(void)
{
    atexit(leaks);

    skip_list_T *list = initialize_skip_list(0);
    skip_list_T *tmp = NULL;

    for (int i = 0; i < 100; i++)
    {
        tmp = insert_node(list, i, "hello");
        if (!tmp)
        {
            destruct_skip_list(&list);
            return 0;
        }

        list = tmp;
    }
//    printf("///////// print initial list\n");
//    print_skip_list(list);
//    printf("\n///////// initial search [50]\n");
//    skip_list_T *searched_node = search_node(list, 50);
//    printf("result: { [level]: %d [key]: %zu [data]: %s }\n", searched_node->_level, searched_node->_key, searched_node->_data);
//    printf("\n///////// initial search 50nd try [0]\n");
//    searched_node = search_node(list, 0);
//    printf("result: { [level]: %d [key]: %zu [data]: %s }\n", searched_node->_level, searched_node->_key, searched_node->_data);
//    list = delete_node(list, 50);
//    searched_node = search_node(list, 50);
//    printf("\n///////// search result after deletion [50]\n");
//    printf("after addr: %p\n", searched_node);
//    if (searched_node)
//    {
//        printf("after result: { [level]: %d [key]: %zu [data]: %s }\n", searched_node->_level, searched_node->_key, searched_node->_data);
//    }
//    else
//    {
//        printf("deleted\n");
//    }
//    printf("\n///////// print deleted list\n");
//    print_skip_list(list);

    destruct_skip_list(&list);
    printf("%p\n", list);
    print_skip_list(list);
    return 0;
}
