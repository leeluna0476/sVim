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
    }

    return new_node;
}

skip_list_T
*initialize_skip_list(int level)
{
    skip_list_T *new_header = generate_node(SIZE_MAX, level, NULL);

    return new_header;
}

int
get_random_level()
{
    int level = 0;
    while (arc4random() % 2 && level < MAX_LEVEL)
    {
        ++level;
    }

    return level;
}

skip_list_T
*insert_node(skip_list_T *existing_highest_header, size_t key, const char* data)
{
    // 아무 노드도 없는 리스트라면
    // 노드 한개 추가하고 리턴.
    if (!existing_highest_header->next)
    {
        existing_highest_header->next = generate_node(key, existing_highest_header->_level, data);
        if (!existing_highest_header->next)
        {
            return NULL;
        }
        
        existing_highest_header->next->prev = existing_highest_header;

        return existing_highest_header;
    }

    skip_list_T *updated_highest_header = existing_highest_header;
    skip_list_T *vert_iterator = existing_highest_header;

    // 새로 생성할 노드의 계층 랜덤 생성.
    int random_level = get_random_level();
    // 새로 생성할 노드의 계층이 기존 최상위 계층보다 높을 때
    // 부족한 만큼의 계층들을 생성하고 탐색을 시작할 header를 새로운 최상위 계층으로 업데이트한다.
    if (random_level > existing_highest_header->_level)
    {
        skip_list_T *new_header = NULL;
        skip_list_T *higher_header = NULL;
        for (int l = random_level; l > existing_highest_header->_level; --l)
        {
            new_header = initialize_skip_list(l);
            if (!new_header)
            {
                // remove generated list
                return NULL;
            }

            // 새로 생성한 계층끼리 상하연결.
            new_header->up = higher_header;
            if (higher_header)
            {
                higher_header->down = new_header;
            }
            higher_header = new_header;
        }

        // 기존 최상위 계층과 상하연결.
        new_header->down = existing_highest_header;
        existing_highest_header->up = new_header;
        existing_highest_header = new_header;
        updated_highest_header = new_header;
        vert_iterator = new_header;
    }
    // 새로 생성할 노드의 계층이 기존 최상위 계층보다 낮을 때
    // 탐색을 시작할 헤더를 하위 계층으로 이동한다.
    else if (random_level < existing_highest_header->_level)
    {
        for (int l = existing_highest_header->_level; l > random_level; --l)
        {
            vert_iterator = vert_iterator->down;
        }
    }

    int l = vert_iterator->_level;
    skip_list_T *new_node = NULL;
    skip_list_T *higher_node = NULL;
    while (vert_iterator)
    {
        skip_list_T *horz_iterator = vert_iterator;

        // 새 노드가 위치할 곳을 찾는다.
        while (horz_iterator->next && horz_iterator->next->_key < key)
        {
            horz_iterator = horz_iterator->next;
        }

        // 새 노드를 생성한다.
        new_node = generate_node(key, l, data);
        if (!new_node)
        {
            // delete nodes : key
            return NULL;
        }

        // 좌우 연결
        new_node->next = horz_iterator->next;
        if (horz_iterator->next)
        {
            horz_iterator->next->prev = new_node;
        }
        horz_iterator->next = new_node;
        new_node->prev = horz_iterator;

        // 상하 연결
        new_node->up = higher_node;
        if (higher_node)
        {
            higher_node->down = new_node;
        }
        higher_node = new_node;

        // 하위 계층으로 이동
        vert_iterator = horz_iterator->down;
        --l;
    }

    return updated_highest_header;
}

skip_list_T
*search_node(skip_list_T *highest_header, size_t key)
{
    skip_list_T *vert_iterator = highest_header;
    while (vert_iterator)
    {
        skip_list_T *horz_iterator = vert_iterator;

        // key에 대한 노드를 찾는다.
        while (horz_iterator->next && horz_iterator->next->_key < key)
        {
            horz_iterator = horz_iterator->next;
        }

        // 가장 먼저 찾은 노드를 반환한다.
        if (horz_iterator->next && horz_iterator->next->_key == key)
        {
            return horz_iterator->next;
        }

        vert_iterator = horz_iterator->down;
    }

    return NULL;
}

skip_list_T
*delete_node(skip_list_T *highest_header, size_t key)
{
    skip_list_T *updated_highest_header = highest_header;
    skip_list_T *target = search_node(highest_header, key);
    while (target)
    {
        // 계층의 마지막 노드라면 계층 삭제.
        if (target->prev->_key == SIZE_MAX && !target->next)
        {
            // 최상위 계층을 삭제할 경우 반환할 최상위 헤더 업데이트.
            if (target->prev->_level == updated_highest_header->_level)
            {
                updated_highest_header = target->prev->down;
            }

            // 헤더 위아래 연결.
            if (target->prev->up)
            {
                target->prev->up->down = target->prev->down;
            }
            if (target->prev->down)
            {
                target->prev->down->up = target->prev->up;
            }

            // 헤더 삭제.
            free(target->prev);
        }
        // 아니라면 좌우 노드끼리 연결.
        else
        {
            target->prev->next = target->next;
            if (target->next)
            {
                target->next->prev = target->prev;
            }
        }

        skip_list_T *tmp = target;
        target = target->down;

        free(tmp->_data);
        tmp->_data = NULL;
        free(tmp);
    }

    return updated_highest_header;
}

void
print_skip_list(skip_list_T *highest_header)
{
    while (highest_header)
    {
        skip_list_T *tmp = highest_header;
        printf("{\n");
        while (tmp)
        {
            printf("\t[level]: %d [key]: %zu [data]: %s [next]: %p\n", tmp->_level, tmp->_key, tmp->_data, tmp->next);
            tmp = tmp->next;
        }
        printf("}\n");
        highest_header = highest_header->down;
    }
}
