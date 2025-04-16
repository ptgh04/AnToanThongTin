#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long modInverse(long long a, long long m) {
    if (gcd(a, m) != 1)
        return -1;

    long long m0 = m;
    long long y = 0, x = 1;

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

int main() {
    long long a = 37;
    long long b = 97;
    long long x = 581;
    long long y = 364;
    long long n = 127;

    long long ax = (a * x) % n;
    long long by = (b * y) % n;

    long long A1 = (ax + by) % n;
    if (A1 < 0) A1 += n;

    long long A2 = (ax - by) % n;
    if (A2 < 0) A2 += n;

    long long A3 = (ax * by) % n;

    long long A4 = modInverse(by, n);

    long long A5 = -1;
    if (A4 != -1) {
        A5 = (ax * A4) % n;
    }

    cout << "Input: a = " << a << "; b = " << b << "; x = " << x
         << "; y = " << y << "; n = " << n << endl;
    cout << "ax mod n = " << ax << endl;
    cout << "by mod n = " << by << endl;
    cout << "Output:" << endl;
    cout << "A1 = (ax + by) mod n = " << A1 << endl;
    cout << "A2 = (ax - by) mod n = " << A2 << endl;
    cout << "A3 = (ax * by) mod n = " << A3 << endl;

    if (A4 != -1) {
        cout << "A4 = (by)^(-1) mod n = " << A4 << endl;
        cout << "A5 = (ax / by) mod n = " << A5 << endl;
    } else {
        cout << "A4 = (by)^(-1) mod n = Không tồn tại (gcd(by, n) != 1)" << endl;
        cout << "A5 = (ax / by) mod n = Không tồn tại (vì A4 không tồn tại)" << endl;
    }

    return 0;
}