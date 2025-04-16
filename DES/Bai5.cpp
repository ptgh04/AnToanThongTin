#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>


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

    std::string R0_binary = "00011010000010011000000000001011";

    std::string R0_hex = binaryToHex(R0_binary);

    std::cout << "R0 (hex): " << R0_hex << std::endl;
    std::cout << "R0 (binary): " << R0_binary << std::endl;

    std::string ER0_binary = applyPermutation(R0_binary, E, 48);
    std::string ER0_hex = binaryToHex(ER0_binary);

    std::cout << "E[R0] (binary): " << ER0_binary << std::endl;
    std::cout << "E[R0] (hex): " << ER0_hex << std::endl;

    return 0;
}