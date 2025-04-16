#include <iostream>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long mod_inverse(long long e, long long phi) {
    long long x = 1, y = 0;
    long long x1 = 0, y1 = 1;
    long long phi_original = phi;

    while (phi > 0) {
        long long q = e / phi;
        long long temp = e % phi;
        e = phi;
        phi = temp;

        long long temp2 = x - q * x1;
        x = x1;
        x1 = temp2;

        temp2 = y - q * y1;
        y = y1;
        y1 = temp2;
    }

    if (x < 0)
        x += phi_original;

    return x;
}

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

int main() {
    long long p = 43;
    long long q = 47;
    long long e = 67;
    long long M = 59;

    long long n = p * q;
    cout << "a) Khóa công khai của An: PU = {e, n} = {" << e << ", " << n << "}" << endl;

    long long phi = (p - 1) * (q - 1);
    cout << "   Phi(n) = (p-1)(q-1) = " << phi << endl;

    cout << "   GCD(e, phi) = " << gcd(e, phi) << endl;

    long long d = mod_inverse(e, phi);

    cout << "b) Khóa riêng của An: PR = {d, n} = {" << d << ", " << n << "}" << endl;
    cout << "   Kiểm tra: (d * e) % phi = (" << d << " * " << e << ") % " << phi << " = " << ((d * e) % phi) << endl;

    long long C = mod_pow(M, d, n);
    cout << "c) Mã hóa thông điệp M = " << M << ": C = M^e mod n = " << M << "^" << d << " mod " << n << " = " << C << endl;

    long long M_decrypted = mod_pow(C, d, n);
    cout << "d) Giải mã bản mã C = " << C << ": M = C^d mod n = " << C << "^" << d << " mod " << n << " = " << M_decrypted << endl;

    cout << "e) Việc mã hóa ở câu c) thực hiện nhiệm vụ bảo mật (không phải chữ ký số)" << endl;
    cout << "   Vì đã sử dụng khóa công khai (e) để mã hóa thông điệp, chỉ người có khóa riêng mới giải mã được" << endl;

    return 0;
}