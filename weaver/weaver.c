#ifndef WEAVER_C
#define WEAVER_C

#include "weaver.h"

int is_legal_weaver_move(char *a, char *b)
{
    int diff = 0;
    for (int i = 0; i < 4; i++)
    {
        if (a[i] != b[i]) diff++;
        if (diff > 1) return 0;
    }
    return 1;
}

int get_desirability(char *a, char *b)
{
    int des = 0;
    for (int i = 0; i < 4; i++)
    {
        if (a[i] == b[i]) des++;
        
    }
    return des;
}


#endif