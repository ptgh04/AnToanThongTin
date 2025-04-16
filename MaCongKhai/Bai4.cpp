#include <iostream>
#include <cmath>
using namespace std;

long long mod_pow(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;
        base = (base * base) % modulus;
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

        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

int main() {
    long long q = 6827;
    long long a = 5;
    long long xA = 307;
    long long k = 919;
    long long M = 474;

    long long yA = mod_pow(a, xA, q);
    cout << "a) Khóa công khai của An: PU = {q, a, yA} = {" << q << ", " << a << ", " << yA << "}" << endl;

    long long C1 = mod_pow(a, k, q);

    long long yA_k = mod_pow(yA, k, q);
    long long C2 = (M * yA_k) % q;

    cout << "b) Ba mã hóa bản tin M = " << M << " với k = " << k << endl;
    cout << "   C1 = a^k mod q = " << a << "^" << k << " mod " << q << " = " << C1 << endl;
    cout << "   C2 = M * (yA^k) mod q = " << M << " * (" << yA << "^" << k << " mod " << q << ") mod " << q << " = " << C2 << endl;
    cout << "   Bản mã là (C1, C2) = (" << C1 << ", " << C2 << ")" << endl;

    long long C1_xA = mod_pow(C1, xA, q);
    long long K_inv = mod_inverse(C1_xA, q);

    long long M_decrypted = (C2 * K_inv) % q;

    cout << "c) Cách An giải mã bản mã (C1, C2) = (" << C1 << ", " << C2 << ")" << endl;
    cout << "   Tính K = (C1^xA) mod q = " << C1 << "^" << xA << " mod " << q << " = " << C1_xA << endl;
    cout << "   Tính K^-1 mod q = " << K_inv << endl;
    cout << "   M = C2 * K^-1 mod q = " << C2 << " * " << K_inv << " mod " << q << " = " << M_decrypted << endl;

    return 0;
}