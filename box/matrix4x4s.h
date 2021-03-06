#ifndef MATRIX4X4S_H
#define MATRIX4X4S_H

#include <emmintrin.h>

__m128 m4x4v_SSE3(const __m128 rows[4], __m128 v);
__m128 m4x4v_SSE4(const __m128 rows[4], __m128 v);

#endif /* MATRIX4X4S_H */
