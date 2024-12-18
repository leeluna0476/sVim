#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/errno.h>
#include "skip_list.h"
#include "screen.h"

#define MAX_LINE 512

int     init_read(FILE *fp, skip_list_T *list);

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

    set_raw_mode(true);

    // initial print
    printf("%s", CLEAR_SCREEN);
    print_data_on_screen(list, &w, 0);
    printf("%s", LEFT_TOP);
    fflush(stdout);

    for (;;);

    destruct_skip_list(list);
    fclose(fp);

    set_raw_mode(false);
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
