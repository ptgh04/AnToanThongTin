#include <iostream>
#include <cmath>
using namespace std;

long long mod_pow(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m;

    while (b > 0) {
        if (b & 1)
            result = (result * a) % m;

        b = b >> 1;
        // a = a^2
        a = (a * a) % m;
    }

    return result;
}

int main() {
    long long q = 6947;
    long long a = 5;
    long long xA = 395;
    long long xB = 338;


    long long yA = mod_pow(a, xA, q);

    long long yB = mod_pow(a, xB, q);

    long long K_A = mod_pow(yB, xA, q);

    long long K_B = mod_pow(yA, xB, q);

    cout << "a) Cách An tính:" << endl;
    cout << "   Khóa công khai yA = a^xA mod q = 5^395 mod 6947 = " << yA << endl;
    cout << "   Khóa phiên K = yB^xA mod q = " << yB << "^395 mod 6947 = " << K_A << endl;

    cout << "\nb) Cách Ba tính:" << endl;
    cout << "   Khóa công khai yB = a^xB mod q = 5^338 mod 6947 = " << yB << endl;
    cout << "   Khóa phiên K = yA^xB mod q = " << yA << "^338 mod 6947 = " << K_B << endl;

    cout << "\nKiểm tra: K_A == K_B? " << (K_A == K_B ? "Đúng" : "Sai") << endl;

    return 0;
}