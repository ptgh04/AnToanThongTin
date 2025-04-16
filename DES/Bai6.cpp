#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <sstream>

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

const int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
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
        if (i + 4 <= binaryStr.length()) {
            std::string chunk = binaryStr.substr(i, 4);
            int value = std::stoi(chunk, nullptr, 2);
            std::stringstream ss;
            ss << std::hex << std::uppercase << value;
            hex += ss.str();
        }
    }
    return hex;
}

std::string applyPermutation(const std::string& input, const int* table, int tableSize) {
    std::string result;
    for (int i = 0; i < tableSize; i++) {
        result += input[table[i] - 1];  // -1 because table is 1-indexed
    }
    return result;
}

std::string xorBinaryStrings(const std::string& a, const std::string& b) {
    std::string result;
    for (size_t i = 0; i < a.length() && i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

int main() {
    std::string M = "32D604E6C4504149";
    std::cout << "Original Message M: " << M << std::endl;


    std::string ER0_binary = "100011110100000001010011110000000000000001010110";
    std::string ER0_hex = binaryToHex(ER0_binary);
    std::cout << "ER0 (binary): " << ER0_binary << std::endl;
    std::cout << "ER0 (hex): " << ER0_hex << std::endl;

    std::string K1 = "101110000000100011011110001011110100011011111110";
    std::cout << "K1 (binary): " << K1 << std::endl;

    std::string A_binary = xorBinaryStrings(ER0_binary, K1);
    std::string A_hex = binaryToHex(A_binary);

    std::cout << "A = ER0 XOR K1 (binary): " << A_binary << std::endl;
    std::cout << "A = ER0 XOR K1 (hex): " << A_hex << std::endl;

    return 0;
}