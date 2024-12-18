#include "screen.h"
#include <termios.h>
#include <string.h>
#include <stdio.h>

void
set_raw_mode(const bool enable)
{
	static struct termios oldt;
	static struct termios newt;

	if (enable == true)
	{
		// 원래 터미널 설정 저장.
		tcgetattr(0, &oldt);
		// 터미널을 raw 모드로 설정.
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(0, TCSANOW, &newt);
	}
	else
	{
		// 원래 터미널 설정 복원.
		tcsetattr(0, TCSANOW, &oldt);
	}
}

void    move_cursor(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

int
print_data_on_screen(skip_list_T *list, const struct winsize* w, size_t key_offset)
{
    skip_list_T     **nodes_to_print = calloc(w->ws_row, sizeof(skip_list_T *));
    if (!nodes_to_print)
    {
        return -1;
    }

    unsigned short  col_overflow = 0;
    unsigned short  data_len = 0;
    unsigned short  key = 0;
    unsigned short  i = 0;
    while (i < w->ws_row)
    {
        nodes_to_print[key] = search_node(list, key_offset + key);
        if (nodes_to_print[key])
        {
            data_len = strlen(nodes_to_print[key]->_data);
            data_len -= data_len ? 1 : 0;
            col_overflow = (data_len + w->ws_col) / w->ws_col;
            i += col_overflow;
            ++key;
        }
        else
        {
            break;
        }
    }

    for (unsigned short i = 0; i < key - 1; ++i)
    {
        printf("%s", nodes_to_print[i]->_data);
    }

    if (nodes_to_print[key - 1]->_data)
    {
        char    *data_copy = strdup(nodes_to_print[key - 1]->_data);
        if (data_copy)
        {
            int newline_idx = data_len;
            if (data_len > w->ws_col)
            {
                newline_idx = (i - w->ws_row + 1) * w->ws_col;
            }

            if (data_copy[newline_idx] == '\n')
            {
                data_copy[newline_idx] = '\0';
            }

            printf("%s", data_copy);
        }
        free(data_copy);
    }

    fflush(stdout);
    free(nodes_to_print);

    return 0;
}
