def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True


def find_prime_chain(hash_value):
    prime_chain = ""
    current_number = 2
    while len(prime_chain) < 48:
        if is_prime(current_number):
            prime_chain += str(current_number)
            current_hash = calculate_hash(prime_chain)
            if current_hash == hash_value:
                return prime_chain
        current_number += 1
    return ""


def calculate_hash(number):
    hash_value = 0
    for digit in number:
        hash_value = (hash_value * 13 + int(digit)) % 100000007
    return hash_value


# Read the number of hash values
num_hashes = int(input())

# Process each hash value
for _ in range(num_hashes):
    hash_value = int(input())
    prime_chain_number = find_prime_chain(hash_value)
    print(prime_chain_number, end=" ")
