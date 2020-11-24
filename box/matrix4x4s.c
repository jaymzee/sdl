#include <immintrin.h>
#include "matrix4x4s.h"

__m128 m4x4v_SSE3(const __m128 rows[4], const __m128 x) {
  __m128 v0 = _mm_mul_ps(rows[0], x);
  __m128 v1 = _mm_mul_ps(rows[1], x);
  __m128 v2 = _mm_mul_ps(rows[2], x);
  __m128 v3 = _mm_mul_ps(rows[3], x);

  return _mm_hadd_ps(_mm_hadd_ps(v0, v1), _mm_hadd_ps(v2, v3));
}

__m128 m4x4v_SSE4(const __m128 rows[4], const __m128 x) {
  __m128 v0 = _mm_dp_ps (rows[0], x, 0xFF);
  __m128 v1 = _mm_dp_ps (rows[1], x, 0xFF);
  __m128 v2 = _mm_dp_ps (rows[2], x, 0xFF);
  __m128 v3 = _mm_dp_ps (rows[3], x, 0xFF);

  return _mm_shuffle_ps(_mm_movelh_ps(v0, v1),
                        _mm_movelh_ps(v2, v3),
                        _MM_SHUFFLE(2, 0, 2, 0));
}
