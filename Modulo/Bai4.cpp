#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long phi(long long n) {
    long long result = n;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }

    if (n > 1)
        result -= result / n;

    return result;
}

long long powerMod(long long a, long long m, long long n) {
    a = a % n;
    long long result = 1;

    while (m > 0) {
        if (m & 1)
            result = (result * a) % n;
        m = m >> 1;
        a = (a * a) % n;
    }

    return result;
}

long long powerModWithEuler(long long a, long long m, long long n) {
    if (gcd(a, n) == 1) {
        long long phi_n = phi(n);

        return powerMod(a, m % phi_n, n);
    } else {
        return powerMod(a, m, n);
    }
}

int main() {
    long long a, m, n;
    cin >> a >> m >> n;
    cout << powerModWithEuler(a, m, n);
}