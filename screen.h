#ifndef SCREEN_H
# define SCREEN_H

# include <stdbool.h>
# include <sys/ioctl.h>
# include "skip_list.h"

# define CLEAR_SCREEN "\033[2J\033[H"
# define LEFT_TOP "\033[H"

void    set_raw_mode(const bool enable);
void    move_cursor(int x, int y);
int     print_data_on_screen(skip_list_T *list, const struct winsize* w, size_t key_offset);

#endif
