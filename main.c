#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "skip_list.h"

void    leaks()
{
    system("leaks --list -- sVim");
}

int
main(void)
{
//    atexit(leaks);


    skip_list_T *header = initialize_skip_list();
    if (header)
    {
        for (int i = 0; i < 10; i++)
        {
            insert_node(header, i, "hello");
        }
    }
//    insert_node(header, 3, "world");
//    insert_node(header, 5, "sanglee2");
//    insert_node(header, 7, "seojchoi");

    print_node(search_node(header, 3));
    print_node(search_node(header, 5));
    print_node(search_node(header, 7));

//    printf("\n\n\n");
    print_skip_list(header);

    return 0;
}
