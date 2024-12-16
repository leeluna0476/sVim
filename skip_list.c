#include "skip_list.h"
#include <string.h>

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
*insert_node(skip_list_T *existing_header, size_t key, const char* data)
{
    // 아무 노드도 없는 리스트라면
    // 노드 한개 추가하고 리턴.
    if (!existing_header->next)
    {
        existing_header->next = generate_node(key, existing_header->_level, data);
        if (!existing_header->next)
        {
            return NULL;
        }
        
        existing_header->next->prev = existing_header;

        return existing_header;
    }

    skip_list_T *updated_header = existing_header;

    // 새로 생성할 노드의 계층 랜덤 생성.
    int random_level = get_random_level();
    // 새로 생성할 노드의 계층이 기존 최상위 계층보다 높을 때
    // 부족한 만큼의 계층들을 생성하고 탐색을 시작할 header를 새로운 최상위 계층으로 업데이트한다.
    if (random_level > existing_header->_level)
    {
        skip_list_T *new_header = NULL;
        skip_list_T *higher_header = NULL;
        for (int l = random_level; l > existing_header->_level; --l)
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
        new_header->down = existing_header;
        existing_header->up = new_header;
        existing_header = new_header;
        updated_header = new_header;
    }
    // 새로 생성할 노드의 계층이 기존 최상위 계층보다 낮을 때
    // 탐색을 시작할 헤더를 하위 계층으로 이동한다.
    else if (random_level < existing_header->_level)
    {
        for (int l = existing_header->_level; l > random_level; --l)
        {
            existing_header = existing_header->down;
        }
    }

    int l = existing_header->_level;
    skip_list_T *new_node = NULL;
    skip_list_T *higher_node = NULL;
    while (existing_header)
    {
        skip_list_T *iterator = existing_header;

        // 새 노드가 위치할 곳을 찾는다.
        while (iterator->next && iterator->next->_key < key)
        {
            iterator = iterator->next;
        }

        // 새 노드를 생성한다.
        new_node = generate_node(key, l, data);
        if (!new_node)
        {
            // delete nodes : key
            return NULL;
        }

        // 좌우 연결
        new_node->next = iterator->next;
        if (iterator->next)
        {
            iterator->next->prev = new_node;
        }
        iterator->next = new_node;
        new_node->prev = iterator;

        // 상하 연결
        new_node->up = higher_node;
        if (higher_node)
        {
            higher_node->down = new_node;
        }
        higher_node = new_node;

        // 하위 계층으로 이동
        existing_header = existing_header->down;
        --l;
    }

    return updated_header;
}
