#include <iostream>
#include <vector>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

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

bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

vector<long long> primeFactors(long long n) {
    vector<long long> factors;

    if (n % 2 == 0) {
        factors.push_back(2);
        while (n % 2 == 0)
            n /= 2;
    }

    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        factors.push_back(n);

    return factors;
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

bool isPrimitiveRoot(long long a, long long n) {
    if (gcd(a, n) != 1)
        return false;

    if (!isPrime(n)) {
        if (n == 2 || n == 4) {
            return (n == 2 && a == 1) || (n == 4 && a == 3);
        }

        if (n % 2 == 0) {
            long long temp = n / 2;
            long long p = 0;
            for (int i = 3; i * i <= temp; i += 2) {
                if (temp % i == 0) {
                    p = i;
                    break;
                }
            }
            if (p == 0 && temp > 1)
                p = temp;

            if (p == 0 || temp % (p * p) == 0)
                return false;
        } else {
            long long p = 0;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    p = i;
                    break;
                }
            }
            if (p == 0)
                p = n;

            long long temp = n;
            while (temp % p == 0)
                temp /= p;

            if (temp != 1)
                return false;
        }
    }

    long long phi_n = phi(n);

    vector<long long> factors = primeFactors(phi_n);

    for (long long factor : factors) {
        if (powerMod(a, phi_n / factor, n) == 1)
            return false;
    }

    return true;
}

int main() {
    long long a = 5;
    long long n = 463;

    cout << "Input: a = " << a << "; n = " << n << endl;

    if (isPrime(n)) {
        bool result = isPrimitiveRoot(a, n);
        cout << "Output: a " << (result ? "là" : "không là") << " căn nguyên thủy của n" << endl;
    } else {
        cout << "Output: a không là căn nguyên thủy của n (vì n = " << n << " không phải là số nguyên tố)" << endl;
    }

    return 0;
}