#ifndef SKIP_LIST_H
# define SKIP_LIST_H

# include <stdlib.h>

# define MAX_LEVEL 16

/*
 * _level:  current highest level of the node
 * _key:    node identifier
 * _data:   real data to store
 * forward: pointers forward the node on every level
 */
typedef struct  _skip_list
{
    int                 _level;
    size_t              _key;
    char                *_data;
    struct _skip_list   *forward[MAX_LEVEL];
} skip_list_T;

skip_list_T *initialize_skip_list();
int         get_random_level();
void        insert_node(skip_list_T *header, size_t key, const char *data);

#endif
