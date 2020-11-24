#include <stdio.h>
#include <string.h>
#include <emmintrin.h>
#include "print_sse.h"

void sprint_4s(char *str, __m128 x)
{
    float p[4];
    char buf[80];

    _mm_storeu_ps(p, x);

    str[0] = 0;
    strcat(str, "[");
    for (int j = 0; j < 4; j++) {
        if (j > 0) {
            strcat(str, " ");
        }
        sprintf(buf, "%g", p[j]);
        strcat(str, buf);
    }
    strcat(str, "]");
}
