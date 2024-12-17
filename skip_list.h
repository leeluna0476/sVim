#ifndef SKIP_LIST_H
# define SKIP_LIST_H

# include <stdlib.h>

# define MAX_LEVEL 16

/*
 * _level:   current highest level of the node
 * _key:     node identifier
 * _data:    real data to store
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
 * uses "malloc()". must free the list by "destruct_skip_list()" after use.
 *
 * <initialized to...>:
 * header->_level = 0
 * header->_key = SIZE_MAX
 * header->_data = NULL;
 *
 * <return value>:
 * the header of the new list
 */
skip_list_T *initialize_skip_list();

/* GET_RANDOM_LEVEL
 *
 * generates a random number from 0 to MAX_LEVEL - 1 with a 50% probability at each level.
 *
 * <return value>:
 * a random number ranging from 0 to MAX_LEVEL -1
 */
int         get_random_level();

/* INSERT_NODE
 *
 * inserts a new data to the list.
 * reassigns the data to the node when the key exists in the list.
 * generates a new node and inserts it to the list when the key does not exists.
 *
 * <parameter(s)>:
 * header: the head of the list
 * key:    the key of the target node to be inserted to the list
 * data:   the real data to be assigned to the target node
 *
 * <return value>:
 * none
 */
void        insert_node(skip_list_T *header, size_t key, const char *data);

/* DELETE_NODE
 *
 * deletes the node corresponding to the key.
 *
 * <parameter(s)>:
 * header: the head of the list
 * key:    the key of the target node to be deleted from the list
 *
 * <return value>:
 * none
 */
void        delete_node(skip_list_T *header, size_t key);

/* SEARCH_NODE
 *
 * searches the node corresponding to the key.
 *
 * <parameter(s)>:
 * header: the head of the list
 * key:    the key of the target node to search in the list
 *
 * <return value>:
 * the target node searched or NULL
 */
skip_list_T *search_node(skip_list_T *header, size_t key);

/* DESTRUCT_LIST
 *
 * frees every node of the list including header
 * the pointer to header becomes invalid and must not be reused.
 *
 * <parameter(s)>:
 * header: the head of the list
 *
 * <return value>:
 * none
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
 *
 * <return value>:
 * none
 */
void        print_node(skip_list_T *node);

/* PRINT_SKIP_LIST
 *
 * prints the members of every node of the list including header.
 * nodes in the same level are grouped by braces {}.
 *
 * <parameter(s)>:
 * header: the head of the list
 *
 * <output>:
 *  {
 *      [level]: (current level) [key]: (node->_key) [data]: (node->_data)
 *      [level]: (current level) [key]: (node->_key) [data]: (node->_data)
 *      [level]: (current level) [key]: (node->_key) [data]: (node->_data)
 *  }
 *  {
 *      [level]: (current level) [key]: (node->_key) [data]: (node->_data)
 *      [level]: (current level) [key]: (node->_key) [data]: (node->_data)
 *      [level]: (current level) [key]: (node->_key) [data]: (node->_data)
 *  }
 *
 * <return value>:
 * none
 */
void        print_skip_list(skip_list_T *header);

#endif
