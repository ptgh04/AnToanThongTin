#include <bits/stdc++.h>

using namespace std;

int extendedEuclidGCD(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

int modularInverse(int a, int n) {
    int x, y;
    int g = extendedEuclidGCD(a, n, x, y);
    if (g != 1) {
        return -1;
    }
    else {
        x = (x % n + n) % n;
        return x;
    }
}

int main() {
    int a, n;
    cin >> a >> n;
    cout << modularInverse(a, n);
}