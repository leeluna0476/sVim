#include "skip_list.h"
#include <string.h>

//        // 확률에 걸리면 상위 계층으로 올라간다.
//        // 0 <= level <= head + 1
//        // rand seed 설정
//        int n = 1;
//        int level = 0;
//        while ((rand() % n) && level <= head->_level)
//        {
//            ++level;
//            n <<= 1;
//        }
