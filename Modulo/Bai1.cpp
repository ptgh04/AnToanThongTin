#include <bits/stdc++.h>

using namespace std;

long long powerMod(long long a, long long m, long long n) {
    if (m == 0)
        return 1;

    long long result = 1;

    a = a % n;

    while (m > 0) {
        if (m & 1)
            result = (result * a) % n;

        m = m >> 1;
        a = (a * a) % n;
    }

    return result;
}

int main() {
    long long a, m, n;
    cin >> a >> m >> n;
    cout << powerMod(a, m, n);
    return 0;
}
