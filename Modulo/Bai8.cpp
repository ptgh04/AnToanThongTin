#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;

long long powerMod(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

long long discreteLog(long long a, long long b, long long n) {
    if (b == 1)
        return 0;

    long long m = ceil(sqrt(n));

    unordered_map<long long, long long> value;
    for (long long j = 0; j < m; j++) {
        long long val = powerMod(a, j, n);
        value[val] = j;
    }

    long long a_inv = powerMod(a, n - 2, n);
    long long a_to_m = 1;
    for (long long i = 0; i < m; i++) {
        a_to_m = (a_to_m * a_inv) % n;
    }

    long long cur = b;
    for (long long i = 0; i <= m; i++) {
        if (value.find(cur) != value.end()) {
            return (i * m + value[cur]) % n;
        }

        cur = (cur * a_to_m) % n;
    }

    return -1;
}

long long discreteLogarithm(long long a, long long b, long long n) {
    a %= n;
    b %= n;

    if (b == 1)
        return 0;

    long long m = ceil(sqrt(n));

    unordered_map<long long, long long> value;
    for (long long j = 0; j < m; j++) {
        long long val = powerMod(a, j, n);
        if (value.find(val) == value.end())
            value[val] = j;
    }

    long long a_m = powerMod(a, m, n);

    long long cur = b;
    for (long long i = 0; i < m; i++) {
        if (value.find(cur) != value.end()) {
            return (i * m + value[cur]) % n;
        }

        cur = (cur * a_m) % n;
    }

    return -1;
}

int main() {
    long long a = 3;
    long long b = 5;
    long long n = 19;

    long long k = -1;

    for (long long i = 0; i < n; i++) {
        if (powerMod(a, i, n) == b) {
            k = i;
            break;
        }
    }

    cout << "Input: a = " << a << "; b = " << b << "; n = " << n << endl;

    if (k != -1) {
        cout << "Output: k = " << k << endl;
        cout << "Kiểm tra: " << a << "^" << k << " mod " << n << " = " << powerMod(a, k, n) << " (bằng " << b << ")" << endl;
    } else {
        cout << "Output: Không tồn tại logarithm rời rạc của " << b << " với cơ số " << a << " modulo " << n << endl;
    }

    return 0;
}