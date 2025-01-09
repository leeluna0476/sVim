#ifndef USER_INTERACTION_H
# define USER_INTERACTION_H

# include <stdbool.h>
# include "screen.h"
# include "skip_list.h"

bool    check_insert_mode(char c);
bool    execute_arrow(char c, skip_list_T *list, const struct winsize* w);
void    interact_with_user(skip_list_T *list, const struct winsize* w);

#endif
