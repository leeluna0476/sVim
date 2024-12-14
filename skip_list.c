#include "skip_list.h"
#include <string.h>

skip_list_T
*generate_node_skip_list(size_t key, int level, char* data)
{
    skip_list_T *node_to_generate = calloc(1, sizeof(skip_list_T));

    if (node_to_generate != NULL)
    {
        node_to_generate->_key = key;
        node_to_generate->_level = level;
        node_to_generate->_data = strdup(data);
    }
    
    return node_to_generate;
}

/*
 * insert a node to the list.
 * PARAMS: head(head node of the list), key(key to search the position of the node), data(data to add)
 * RETURN VALUE: return the head node of the list. the first node of the highest level becomes the head node.
 */
skip_list_T
*insert_node_skip_list(skip_list_T *head, size_t key, char* data)
{
    skip_list_T *node_to_insert = NULL;

    if (head == NULL)
    {
        node_to_insert = generate_node_skip_list(key, 0, data);
    }
    else
    {
        // 확률에 걸리면 상위 계층으로 올라간다.
        // 0 <= level <= head + 1
        // rand seed 설정
        int n = 1;
        int level = 0;
        while ((rand() % n) && level <= head->_level)
        {
            ++level;
            n <<= 1;
        }

        // search and insert
    }

    return node_to_insert;
}
