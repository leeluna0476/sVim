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

/* INITIALIZE_SKIP_LIST
 *
 * initializes the header of the list.
 *
 * <initialized to...>:
 * header->_level = 0
 * header->_key = SIZE_MAX
 * header->_data = NULL;
 */
skip_list_T *initialize_skip_list();

/* GET_RANDOM_LEVEL
 *
 * generates a random number from 0 to MAX_LEVEL - 1 with a 50% probability at each level.
 */
int         get_random_level();

/* INSERT_NODE
 *
 * inserts a new data to the list.
 * reallocates the data to the node when the key exists in the list.
 * generates a new node when the key does not exists.
 *
 * <parameter(s)>:
 * header: the head of the list
 * key:    the key of the target node
 * data:   the real data to be assigned to the target node
 */
void        insert_node(skip_list_T *header, size_t key, const char *data);

/* DELETE_NODE
 *
 * deletes the node corresponding to the key.
 *
 * <parameter(s)>:
 * header: the head of the list
 * key:    the key of the target node
 */
void        delete_node(skip_list_T *header, size_t key);

/* SEARCH_NODE
 *
 * searches the node corresponding to the key.
 *
 * <parameter(s)>:
 * header: the head of the list
 * key:    the key of the target ndoe
 */
skip_list_T *search_node(skip_list_T *header, size_t key);

/* DESTRUCT_LIST
 *
 * frees every node of the list.
 *
 * <parameter(s)>:
 * header: the head of the list
 */
void        destruct_skip_list(skip_list_T *header);

/* PRINT_NODE
 *
 * prints the members of the node to STDOUT.
 * prints (null) when the node is NULL.
 *
 * <parameter(s)>:
 * node: the node to print out
 *
 * <output>:
 *  [level]: (node->_level) [key]: (node->_key) [data]: (node->_data)
 */
void        print_node(skip_list_T *node);

/* PRINT_SKIP_LIST
 *
 * prints the members of every node of the list including header.
 *
 * <parameter(s)>:
 * header: the head of the list
 *
 * <output>:
 *  {
 *      [level]: (node->_level) [key]: (node->_key) [data]: (node->_data)
 *      [level]: (node->_level) [key]: (node->_key) [data]: (node->_data)
 *      [level]: (node->_level) [key]: (node->_key) [data]: (node->_data)
 *  }
 *  {
 *      [level]: (node->_level) [key]: (node->_key) [data]: (node->_data)
 *      [level]: (node->_level) [key]: (node->_key) [data]: (node->_data)
 *      [level]: (node->_level) [key]: (node->_key) [data]: (node->_data)
 *  }
 */
void        print_skip_list(skip_list_T *header);

#endif
