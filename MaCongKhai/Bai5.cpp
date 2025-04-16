#include <iostream>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long mod_pow(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m;

    while (b > 0) {
        if (b & 1)
            result = (result * a) % m;

        b = b >> 1;
        a = (a * a) % m;
    }

    return result;
}

long long mod_inverse(long long a, long long m) {
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

int main() {
    long long p = 47;
    long long q = 23;
    long long h = 25;
    long long xA = 2;
    long long k = 3;
    long long H_M = 13;

    long long exp = (p - 1) / q;
    long long g = mod_pow(h, exp, p);
    cout << "g = h^((p-1)/q) mod p = " << h << "^" << exp << " mod " << p << " = " << g << endl;

    long long yA = mod_pow(g, xA, p);
    cout << "a) Khóa công khai của An: yA = g^xA mod p = " << g << "^" << xA << " mod " << p << " = " << yA << endl;

    long long r = mod_pow(g, k, p) % q;

    long long k_inv = mod_inverse(k, q);
    long long s = (k_inv * (H_M + xA * r)) % q;

    cout << "b) Chữ ký số của An cho bản tin M: (r, s) = (" << r << ", " << s << ")" << endl;
    cout << "   Các bước tính chữ ký:" << endl;
    cout << "   - r = (g^k mod p) mod q = (" << g << "^" << k << " mod " << p << ") mod " << q << " = " << r << endl;
    cout << "   - k^(-1) mod q = " << k_inv << endl;
    cout << "   - s = (k^(-1) * (H(M) + xA*r)) mod q = (" << k_inv << " * (" << H_M << " + " << xA << "*" << r << ")) mod " << q << " = " << s << endl;

    long long w = mod_inverse(s, q);
    cout << "c) Ba xác minh chữ ký số:" << endl;
    cout << "   - w = s^(-1) mod q = " << s << "^(-1) mod " << q << " = " << w << endl;

    long long u1 = (H_M * w) % q;
    cout << "   - u1 = (H(M) * w) mod q = (" << H_M << " * " << w << ") mod " << q << " = " << u1 << endl;

    long long u2 = (r * w) % q;
    cout << "   - u2 = (r * w) mod q = (" << r << " * " << w << ") mod " << q << " = " << u2 << endl;

    long long g_u1 = mod_pow(g, u1, p);
    long long yA_u2 = mod_pow(yA, u2, p);
    long long v = ((g_u1 * yA_u2) % p) % q;
    cout << "   - v = ((g^u1 * yA^u2) mod p) mod q = ((" << g << "^" << u1 << " * " << yA << "^" << u2 << ") mod " << p << ") mod " << q << " = " << v << endl;

    cout << "   - Kiểm tra: v == r? " << (v == r ? "Đúng, chữ ký hợp lệ!" : "Sai, chữ ký không hợp lệ!") << endl;

    return 0;
}