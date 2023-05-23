#include <stdio.h>
#include <math.h>

int is_prime(long long n) {
    if (n <= 1) {
        return 0;
    }
    if (n <= 3) {
        return 1;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    }
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
 
    if (m == 1) {
        return 0;
    }
 
    while (a > 1) {
        long long q = a / m;
        long long t = m;
 
        m = a % m;
        a = t;
        t = y;
 
        y = x - q * y;
        x = t;
    }
 
    if (x < 0) {
        x += m0;
    }
 
    return x;
}

long long decrypt_rsa(long long c, long long p, long long q) {
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 65537;
    long long d = mod_inverse(e, phi);
 
    return (long long)(powl(c, d) - 0.5) % n;
}

int main() {
    long long n, cipher;
    scanf("%lld", &n);
    scanf("%lld", &cipher);

    long long p, q;
    for (long long i = sqrt(n); i >= 2; i--) {
        if (n % i == 0 && is_prime(i)) {
            p = i;
            q = n / i;
            break;
        }
    }

    long long decrypted = decrypt_rsa(cipher, p, q);
    printf("%lld\n", decrypted);

    return 0;
}
