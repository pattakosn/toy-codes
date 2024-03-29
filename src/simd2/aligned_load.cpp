#include <iostream>
//NIKOS TODO MOVE THESE TO CMakeFile.txt parameters depending on compiler
#pragma GCC target("avx2")
#pragma GCC optimize("O3")

#include <x86intrin.h>
//#include <bits/stdc++.h>

using namespace std;

int main() {
    constexpr int n = 8 * 8;
    //alignas(32)
    int a[16*8], b[16*8], c[16*8];

    // unaligned data access
    for (int i = 3; i + 7 < n; i += 8) {
        __m256i x = _mm256_loadu_si256((__m256i*) &a[i]);
        __m256i y = _mm256_loadu_si256((__m256i*) &b[i]);
        __m256i z = _mm256_add_epi32(x, y);
        _mm256_storeu_si256((__m256i*) &c[i], z);
    }

    for (int i = 0; i < n; i += 8) {
        __m256i x = _mm256_load_si256((__m256i*) &a[i]);
        __m256i y = _mm256_load_si256((__m256i*) &b[i]);
        __m256i z = _mm256_add_epi32(x, y);
        _mm256_store_si256((__m256i*) &c[i], z);
    }


    __m256 iota = _mm256_setr_epi32(0., 1., 2., 3., 4., 5., 6., 7.);
    __m256i zero2 = _mm256_setzero_si256();
    __m256i v = _mm256_set1_epi32(42);
    float a1[8];
    __m256 v2 = _mm256_broadcast_ss(&a1[0]);

    typedef int v8si __attribute__ ((vector_size (32)));
    v8si zero = {};
    v8si iota_1 = {0, 1, 2, 3, 4, 5, 6, 7};
}
