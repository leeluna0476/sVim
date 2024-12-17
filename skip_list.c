#include "skip_list.h"
#include <string.h>
#include <stdio.h>

skip_list_T
*generate_node(size_t key, int level, const char* data)
{
    skip_list_T *new_node = calloc(1, sizeof(skip_list_T));
    if (new_node)
    {
        new_node->_key = key;
        new_node->_level = level;
        new_node->_data = data ? strdup(data) : NULL;
        if (data && !(new_node->_data))
        {
            free(new_node);
            new_node = NULL;
        }
    }

    return new_node;
}

skip_list_T
*initialize_skip_list()
{
    skip_list_T *new_header = calloc(1, sizeof(skip_list_T));
    if (new_header)
    {
        new_header->_level = 0;
        new_header->_key = SIZE_MAX;
    }

    return new_header;
}

/*
 * 0 <= random_level <= MAX_LEVEL - 1
 */
int
get_random_level()
{
    int level = 0;
    while ((arc4random() & 1) && level < MAX_LEVEL)
    {
        ++level;
    }

    return level;
}

void
insert_node(skip_list_T *header, size_t key, const char *data)
{
    // 새 노드를 추가할 위치의 이전 노드를 저장하는 배열.
    skip_list_T *update[MAX_LEVEL] = { NULL, };

    skip_list_T *x = header;
    for (int i = header->_level; i >= 0; --i)
    {
        // 각 계층마다 각 노드가 가리키고 있는 forward node를 체크한다.
        while (x->forward[i] && x->forward[i]->_key < key)
        {
            // 같은 계층의 다음 노드로 넘어간다.
            x = x->forward[i];
        }
        // 새 노드를 추가할 위치를 찾으면 update에 추가한다.
        update[i] = x;
    }

    // 최하위 계층으로 이동.
    x = x->forward[0];
    // 이미 존재하는 노드라면 데이터만 수정.
    if (x && x->_key == key)
    {
        free(x->_data);
        x->_data = data ? strdup(data) : NULL;
    }
    // 존재하지 않는 노드라면 새로 생성.
    else
    {
        int random_level = get_random_level();
        if (random_level > header->_level)
        {
            // 새로 생성할 노드의 레벨이 기존 최고 레벨보다 높다면
            // 잉여 update에 헤더를 추가한다. (계층 확장)
            for (int i = header->_level + 1; i <= random_level; ++i)
            {
                update[i] = header;
            }
            header->_level = random_level;
        }

        x = generate_node(key, random_level, data);

        // 새로 생성한 노드를 모든 계층에 연결한다.
        for (int i = 0; i <= random_level; ++i)
        {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
}

void
delete_node(skip_list_T *header, size_t key)
{
    // 삭제할 노드의 이전 노드를 저장하는 배열.
    skip_list_T *update[MAX_LEVEL] = { NULL, };

    skip_list_T *x = header;
    for (int i = header->_level; i >= 0; --i)
    {
        // 각 계층마다 각 노드가 가리키고 있는 forward node를 체크한다.
        while (x->forward[i] && x->forward[i]->_key < key)
        {
            // 같은 계층의 다음 노드로 넘어간다.
            x = x->forward[i];
        }
        // 삭제할 노드의 이전 노드를 찾으면 update에 추가한다.
        update[i] = x;
    }

    // 최하위 계층으로 이동.
    x = x->forward[0];
    // 삭제할 노드를 찾았다면
    if (x && x->_key == key)
    {
        for (int i = 0; i <= header->_level; ++i)
        {
            if (update[i]->forward[i] != x)
            {
                break;
            }

            update[i]->forward[i] = x->forward[i];
        }

        free(x->_data);
        free(x);

        while (header->_level > 0 && !header->forward[header->_level])
        {
            --(header->_level);
        }
    }
}

skip_list_T
*search_node(skip_list_T *header, size_t key)
{
    skip_list_T *x = header;
    for (int i = header->_level; i >= 0; --i)
    {
        while (x->forward[i] && x->forward[i]->_key < key)
        {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x->_key == key)
    {
        return x;
    }

    return NULL;
}

void
print_node(skip_list_T *node)
{
    printf("[level]: %d [key]: %zu [data]: %s\n", node->_level, node->_key, node->_data);
}

void
print_skip_list(skip_list_T *header)
{
    skip_list_T *x = header;
    for (int i = header->_level; i >= 0; --i)
    {
        printf("{\n");
        while (x)
        {
            printf("\t[level]: %d [key]: %zu [data]: %s [next]: %p\n", i, x->_key, x->_data, x->forward[i]);
            x = x->forward[i];
        }
        printf("}\n");
        x = header;
    }
}
