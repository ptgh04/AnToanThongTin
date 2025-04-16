#include <bits/stdc++.h>

using namespace std;

long long modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        long long q = a / m;
        long long t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

long long chineseRemainderTheorem(const vector<long long>& num, const vector<long long>& rem) {
    long long M = 1;
    for (long long n : num) {
        M *= n;
    }

    long long result = 0;
    for (int i = 0; i < num.size(); i++) {
        long long Mi = M / num[i];
        long long Yi = modInverse(Mi, num[i]);

        result = (result + rem[i] * Mi * Yi) % M;
    }

    return result;
}

int main() {
    long long m1 = 17, m2 = 19, m3 = 11;
    long long a1 = 5, a2 = 16, a3 = 3;

    vector<long long> modulos = {m1, m2, m3};
    vector<long long> remainders = {a1, a2, a3};

    long long x = chineseRemainderTheorem(modulos, remainders);

    cout << "Input: m1 = " << m1 << "; m2 = " << m2 << "; m3 = " << m3
         << "; a1 = " << a1 << "; a2 = " << a2 << "; a3 = " << a3 << endl;
    cout << "Output: x = " << x << endl;

    cout << "\nKiểm tra kết quả:" << endl;
    cout << "x mod " << m1 << " = " << x % m1 << " (phải bằng " << a1 << ")" << endl;
    cout << "x mod " << m2 << " = " << x % m2 << " (phải bằng " << a2 << ")" << endl;
    cout << "x mod " << m3 << " = " << x % m3 << " (phải bằng " << a3 << ")" << endl;

    return 0;
}