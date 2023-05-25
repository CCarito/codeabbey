def minimumLength(s):
    left = 0
    right = len(s) - 1

    while left < right and s[left] == s[right]:
        # Move the pointers inward until characters differ
        while left < right and s[left] == s[left + 1]:
            left += 1
        while left < right and s[right] == s[right - 1]:
            right -= 1

        # Remove the common characters from both ends
        left += 1
        right -= 1

    return right - left + 1

# Ejemplos de uso:
print(minimumLength("ca"))         # Output: 2
print(minimumLength("cabaabac"))   # Output: 0
print(minimumLength("aabccabba"))  # Output: 3
