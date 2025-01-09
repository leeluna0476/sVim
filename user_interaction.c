#include "user_interaction.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

# define MIN(x, y) x < y ? x : y

static const char   *insert_modes = "aAiIcCs";
static size_t  i = 1;
static size_t  j = 1;

bool
check_insert_mode(char c)
{
    int i = 0;
    while (c != insert_modes[i])
    {
        if (!insert_modes[i])
        {
            return false;
        }

        ++i;
    }
    return true;
}

/*
 * h: left
 * l: right
 * j: down
 * k: up
 */
bool
execute_arrow(char c, skip_list_T *list, const struct winsize* w)
{
    if (c == 'h' && i > 1)
    {
        --i;
    }
    else if (c == 'j' && j < w->ws_row)
    {
        ++j;
    }
    else if (c == 'k' && j > 1)
    {
        --j;
    }
    else if (c == 'l' && i < w->ws_col)
    {
        ++i;
    }

    size_t  revised_i = i;
    skip_list_T *node = search_node(list, j - 1);
    if (node)
    {
        const char  *line = node->_data[0];
        revised_i = strlen(line);
        if (revised_i > 1 && line[revised_i - 1] == '\n')
        {
            --revised_i;
        }
    }

    i = MIN(i, revised_i);
    move_cursor(i, j);
    return true;
}

void
interact_with_user(skip_list_T *list, const struct winsize* w)
{
    char    c = '\0';
    for (;;)
    {
        if (read(STDIN_FILENO, &c, 1) > 0)
        {
            execute_arrow(c, list, w);
            // 1. hjkl인지 확인하기.
            // 2. 커서 인덱스 업데이트.
            // 3. 커서 인덱스 j를 가지고 리스트에서 라인 불러오기.
            // 4. 라인 길이에 맞게 커서 위치 업데이트.
        }
        fflush(stdout);
    }
}
