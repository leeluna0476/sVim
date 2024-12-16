#ifndef SKIP_LIST_H
# define SKIP_LIST_H

# include <stdlib.h>

# define MAX_LEVEL 16

typedef struct _skip_list
{
    size_t                 _key;
    int                    _level;
    char                   *_data;
    struct _skip_list      *prev;
    struct _skip_list      *next;
    struct _skip_list      *up;
    struct _skip_list      *down;
} skip_list_T;


skip_list_T *generate_node(size_t key, int level, const char* data);
skip_list_T *initialize_skip_list(int level);
skip_list_T *insert_node(skip_list_T *existing_header, size_t key, const char* data);
skip_list_T *search_node(skip_list_T *highest_header, size_t key);

#endif
