#ifndef SKIP_LIST_H
# define SKIP_LIST_H

# include <stdlib.h>

# define MAX_LEVEL 16

/*
 * _level:  current highest level of the node
 * _key:    node identifier
 * _data:   real data to store
 * _forward: pointers forward the node on every level
 */
typedef struct  _skip_list
{
    int                 _level;
    size_t              _key;
    char                *_data;
    struct _skip_list   *_forward[MAX_LEVEL];
} skip_list_T;

skip_list_T *initialize_skip_list();
int         get_random_level();
void        insert_node(skip_list_T *header, size_t key, const char *data);
void        delete_node(skip_list_T *header, size_t key);
skip_list_T *search_node(skip_list_T *header, size_t key);
void        destruct_list(skip_list_T *header);
void        print_node(skip_list_T *node);
void        print_skip_list(skip_list_T *header);

#endif
