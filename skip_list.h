#ifndef SKIP_LIST_H
# define SKIP_LIST_H

# include <stdlib.h>

# define MAX_LEVEL 2147483647

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

#endif
