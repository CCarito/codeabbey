#include <stdio.h>

long long powerMod(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base %= modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }

        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}

long long modInverse(long long a, long long modulus) {
    long long m0 = modulus;
    long long y = 0, x = 1;

    if (modulus == 1) {
        return 0;
    }

    while (a > 1) {
        long long q = a / modulus;
        long long t = modulus;

        modulus = a % modulus;
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

int main() {
    int encryptedWordCount;
    scanf("%d", &encryptedWordCount);

    long long n, p, pe;
    scanf("%lld %lld %lld", &n, &p, &pe);

    for (int i = 0; i < encryptedWordCount; i++) {
        long long pk, c;
        scanf("%lld %lld", &pk, &c);

        long long k = modInverse(powerMod(pk, pe, n), n);
        long long m = (c * modInverse(powerMod(pk, k, n), n)) % n;

        // Convert m back to word
        long long A = m / (31 * 31 * 31);
        m %= (31 * 31 * 31);
        long long B = m / (31 * 31);
        m %= (31 * 31);
        long long C = m / 31;
        long long D = m % 31;

        printf("%c%c%c%c ", A + 'a', B + 'a', C + 'a', D + 'a');
    }

    return 0;
}
