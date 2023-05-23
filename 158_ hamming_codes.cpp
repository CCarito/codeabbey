#include <iostream>
#include <vector>
#include <bitset>

std::bitset<32> encode(const std::bitset<16>& data) {
    std::bitset<32> encoded;
    int parityIndex = 0;
    int dataIndex = 0;

    for (int i = 0; i < 32; ++i) {
        if (i == (1 << parityIndex) - 1) {
            ++parityIndex;
        } else {
            encoded[i] = data[dataIndex++];
        }
    }

    for (int i = 0; i < 5; ++i) {
        int parity = 0;
        for (int j = 0; j < 32; ++j) {
            if (((j + 1) >> i) & 1) {
                parity ^= encoded[j];
            }
        }
        encoded[(1 << i) - 1] = parity;
    }

    return encoded;
}

std::bitset<16> decode(const std::bitset<32>& encoded) {
    std::bitset<16> decoded;

    for (int i = 0, dataIndex = 0; i < 32; ++i) {
        if (!((i + 1) & i)) {
            continue; // Skip parity bits
        }
        decoded[dataIndex++] = encoded[i];
    }

    return decoded;
}

int main() {
    int N1, N2;
    std::cin >> N1;

    std::vector<std::bitset<16>> encodeData(N1);
    for (int i = 0; i < N1; ++i) {
        std::string input;
        std::cin >> input;
        encodeData[i] = std::bitset<16>(input);
    }

    std::cin >> N2;

    std::vector<std::bitset<32>> decodeData(N2);
    for (int i = 0; i < N2; ++i) {
        std::string input;
        std::cin >> input;
        decodeData[i] = std::bitset<32>(input);
    }

    for (const auto& data : encodeData) {
        std::bitset<32> encoded = encode(data);
        std::cout << encoded.to_string().substr(32 - data.size() - 5) << " ";
    }
    std::cout << std::endl;

    for (const auto& data : decodeData) {
        std::bitset<16> decoded = decode(data);
        std::cout << decoded.to_string().substr(16 - 11) << " ";
    }
    std::cout << std::endl;

    return 0;
}
