#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include "skip_list.h"

#define MAX_LINE 512
#define CLEAR_SCREEN "\033[2J\033[H"
#define LEFT_TOP "\033[H"

int init_read(FILE *fp, skip_list_T *list);
int print_data_on_screen(skip_list_T *list, const struct winsize* w, size_t key_offset);

int
main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Open only a file at once.\n");
        return 1;
    }

    FILE    *fp = fopen(argv[1], "rw");
    if (fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    skip_list_T *list = initialize_skip_list();
    if (list == NULL)
    {
        perror("malloc");
        fclose(fp);
        return 1;
    }

    // store 512 line
    if (init_read(fp, list) < 0)
    {
        destruct_skip_list(list);
        fclose(fp);
        return 1;
    }

    // w.ws_row
    // w.ws_col
    struct winsize  w = { 0, };
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        perror("ioctl");
        destruct_skip_list(list);
        fclose(fp);
        return 1;
    }

    // initial print
    printf("%s", CLEAR_SCREEN);
    print_data_on_screen(list, &w, 0);
    printf("%s", LEFT_TOP);
    fflush(stdout);

//    for (;;);

    destruct_skip_list(list);
    fclose(fp);
    return 0;
}

int
init_read(FILE *fp, skip_list_T *list)
{
    char    *buf = NULL;
    size_t  line_cap = 0;
    for (int i = 0; i < MAX_LINE; ++i)
    {
        if (getline(&buf, &line_cap, fp) < 0)
        {
            if (errno)
            {
                perror("getline");
                return -1;
            }
            else
            {
                break;
            }
        }

        insert_node(list, i, buf);
    }

    free(buf);
    return 0;
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
