#include <iostream>

#pragma GCC target("avx2")

const int n = 1e5;
int a[n], s = 0;

int main() {
    for (int t = 0; t < 100000; t++)
        for (int i = 0; i < n; i++)
            s += a[i];
    std::cout << s <<"\n";
    return 0;
}
