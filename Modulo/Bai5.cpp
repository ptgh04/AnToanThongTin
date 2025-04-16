#include <iostream>
#include <vector>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long modInverse(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    
    if (m == 1) return 0;
    
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    
    return (x < 0) ? x + m0 : x;
}

long long powerMod(long long a, long long k, long long n) {
    a %= n;
    long long result = 1;
    
    while (k > 0) {
        if (k & 1) result = (result * a) % n;
        a = (a * a) % n;
        k >>= 1;
    }
    
    return result;
}

vector<pair<long long, int>> primeFactors(long long n) {
    vector<pair<long long, int>> factors;
    
    if (n % 2 == 0) {
        int count = 0;
        while (n % 2 == 0) {
            n /= 2;
            count++;
        }
        factors.push_back({2, count});
    }
    
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            factors.push_back({i, count});
        }
    }
    
    if (n > 2) factors.push_back({n, 1});
    
    return factors;
}

long long powerModWithCRT(long long a, long long k, long long n) {
    if (n == 1) return 0;
    
    if (k == 0) return 1;
    
    vector<pair<long long, int>> factors = primeFactors(n);
    
    if (factors.size() == 1) {
        long long p = factors[0].first;
        int e = factors[0].second;
        long long p_e = 1;
        for (int i = 0; i < e; i++) p_e *= p;
        
        if (a % p == 0) {
            if (k >= e) return 0;
            return powerMod(a, k, p_e);
        }
        
        long long phi_p_e = p_e - p_e / p;
        return powerMod(a, k % phi_p_e, p_e);
    }
    
    vector<long long> moduli;
    vector<long long> remainders;
    
    for (auto &factor : factors) {
        long long p = factor.first;
        int e = factor.second;

        long long p_e = 1;
        for (int i = 0; i < e; i++) p_e *= p;
        
        long long remainder;
        if (a % p == 0) {
            if (k >= e) remainder = 0;
            else remainder = powerMod(a, k, p_e);
        } else {
            long long phi_p_e = p_e - p_e / p;
            remainder = powerMod(a, k % phi_p_e, p_e);
        }
        
        moduli.push_back(p_e);
        remainders.push_back(remainder);
    }
    
    long long N = 1;
    for (long long mod : moduli) N *= mod;
    
    long long result = 0;
    for (int i = 0; i < moduli.size(); i++) {
        long long m = moduli[i];
        long long r = remainders[i];
        long long N_i = N / m;
        result = (result + r * modInverse(N_i, m) * N_i) % N;
    }
    
    return result;
}

int main() {
    long long a, k, n;
    
    cin >> a;
    cin >> k;
    cin >> n;
    
    long long b = powerModWithCRT(a, k, n);
    cout << "Ket qua: " << a << "^" << k << " mod " << n << " = " << b << endl;
    
    return 0;
}