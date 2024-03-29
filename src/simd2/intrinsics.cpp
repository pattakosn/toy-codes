#include <iostream>
//NIKOS TODO MOVE THESE TO CMakeFile.txt parameters depending on compiler
#pragma GCC target("avx2")
#pragma GCC optimize("O3")

#include <x86intrin.h>
//#include <bits/stdc++.h>

using namespace std;

int main() {
    cout << __builtin_cpu_supports("sse") << endl;
    cout << __builtin_cpu_supports("sse2") << endl;
    cout << __builtin_cpu_supports("avx") << endl;
    cout << __builtin_cpu_supports("avx2") << endl;
    cout << __builtin_cpu_supports("avx512f") << endl;

    double a1[100], b1[100], c1[100];

// iterate in blocks of 4,
// because that's how many doubles can fit into a 256-bit register
    for (int i = 0; i < 100; i += 4) {
        // load two 256-bit segments into registers
        __m256d x = _mm256_loadu_pd(&a1[i]);
        __m256d y = _mm256_loadu_pd(&b1[i]);

        // add 4+4 64-bit numbers together
        __m256d z = _mm256_add_pd(x, y);

        // write the 256-bit result into memory, starting with c[i]
        _mm256_storeu_pd(&c1[i], z);
    }

// vector extensions
    typedef int v4si __attribute__ (( vector_size(32) ));
    // type ^   ^ typename          size in bytes ^
    v4si a = {1, 2, 3, 5};
    v4si b = {8, 13, 21, 34};

    v4si c = a + b;

    for (int i = 0; i < 4; i++)
        printf("\t%d\n", c[i]);

    c *= 2; // multiply by scalar

    for (int i = 0; i < 4; i++)
        printf("%d\n", c[i]);

    typedef double v4d __attribute__ (( vector_size(32) ));
    v4d a2[100/4], b2[100/4], c2[100/4];

    for (int i = 0; i < 100/4; i++)
        c2[i] = a2[i] + b2[i];

    return 0;
}
