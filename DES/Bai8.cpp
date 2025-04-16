#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <sstream>

const int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
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
        result += input[table[i] - 1];
    }
    return result;
}

int main() {
    std::string B_hex = "DC6044A9";
    std::cout << "Input B (hex): " << B_hex << std::endl;

    std::string B_binary = hexToBinary(B_hex);
    std::cout << "B (binary): " << B_binary << std::endl;

    if (B_binary.length() != 32) {
        std::cout << "Warning: Binary representation is not 32 bits. Actual length: " << B_binary.length() << std::endl;
        if (B_binary.length() < 32) {
            B_binary = std::string(32 - B_binary.length(), '0') + B_binary;
        } else {
            B_binary = B_binary.substr(B_binary.length() - 32);
        }
        std::cout << "Adjusted B (binary): " << B_binary << std::endl;
    }

    std::string F_binary = applyPermutation(B_binary, P, 32);

    std::string F_hex = binaryToHex(F_binary);

    std::cout << "P-box applied to B (binary): " << F_binary << std::endl;
    std::cout << "F = P(B) (hex): " << F_hex << std::endl;

    return 0;
}