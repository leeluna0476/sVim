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


    return 0;
}
