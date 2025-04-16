#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

std::string hexToBinary(const std::string& hexStr) {
    std::string binary;
    for (char c : hexStr) {
        int value;
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10;
        } else {
            continue;
        }

        std::bitset<4> bits(value);
        binary += bits.to_string();
    }
    return binary;
}

std::string binaryToHex(const std::string& binaryStr) {
    std::string hex;
    for (size_t i = 0; i < binaryStr.length(); i += 4) {
        std::string chunk = binaryStr.substr(i, 4);
        int value = std::stoi(chunk, nullptr, 2);
        std::stringstream ss;
        ss << std::hex << std::uppercase << value;
        hex += ss.str();
    }
    return hex;
}

std::string applyPermutation(const std::string& input, const int* table, int tableSize) {
    std::string result;
    for (int i = 0; i < tableSize; i++) {
        result += input[table[i] - 1];
    }
    return result;
}

int main() {
    std::string M = "32D604E6C4504149";
    std::cout << "Original Message M: " << M << std::endl;

    std::string M_binary = hexToBinary(M);
    std::cout << "M in binary: " << M_binary << std::endl;

    std::string IP_result = applyPermutation(M_binary, IP, 64);
    std::cout << "After IP: " << IP_result << std::endl;

    std::string L0_binary = IP_result.substr(0, 32);
    std::string R0_binary = IP_result.substr(32, 32);

    std::string L0_hex = binaryToHex(L0_binary);
    std::string R0_hex = binaryToHex(R0_binary);

    std::cout << "L0 (binary): " << L0_binary << std::endl;
    std::cout << "L0 (hex): " << L0_hex << std::endl;

    std::cout << "R0 (binary): " << R0_binary << std::endl;
    std::cout << "R0 (hex): " << R0_hex << std::endl;

    return 0;
}