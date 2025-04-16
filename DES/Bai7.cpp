#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <sstream>
#include <vector>

const int S1[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};

const int S2[4][16] = {
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
};

const int S3[4][16] = {
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
    {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
};

const int S4[4][16] = {
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
};

const int S5[4][16] = {
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
};

const int S6[4][16] = {
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
};

const int S7[4][16] = {
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
    {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
    {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
    {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
};

const int S8[4][16] = {
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
    {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
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

int applySBox(const int sbox[4][16], const std::string& sixBits) {
    std::string rowBits = std::string(1, sixBits[0]) + std::string(1, sixBits[5]);
    int row = std::stoi(rowBits, nullptr, 2);

    std::string colBits = sixBits.substr(1, 4);
    int col = std::stoi(colBits, nullptr, 2);

    return sbox[row][col];
}

int main() {
    std::string A_hex = "37488DEF46A8";
    std::cout << "Input A (hex): " << A_hex << std::endl;

    std::string A_binary = hexToBinary(A_hex);
    std::cout << "A (binary): " << A_binary << std::endl;

    if (A_binary.length() != 48) {
        std::cout << "Warning: Binary representation is not 48 bits. Actual length: " << A_binary.length() << std::endl;
        if (A_binary.length() < 48) {
            A_binary = std::string(48 - A_binary.length(), '0') + A_binary;
        } else {
            A_binary = A_binary.substr(A_binary.length() - 48);
        }
        std::cout << "Adjusted A (binary): " << A_binary << std::endl;
    }

    std::vector<std::string> sixBitGroups;
    for (int i = 0; i < 8; i++) {
        sixBitGroups.push_back(A_binary.substr(i * 6, 6));
    }

    std::cout << "Six-bit groups:" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << "Group " << (i + 1) << ": " << sixBitGroups[i] << std::endl;
    }

    std::string B_binary;
    std::cout << "\nS-box substitutions:" << std::endl;

    int s1Result = applySBox(S1, sixBitGroups[0]);
    std::bitset<4> s1Bits(s1Result);
    B_binary += s1Bits.to_string();
    std::cout << "S1(" << sixBitGroups[0] << ") = " << s1Result << " = " << s1Bits.to_string() << std::endl;

    int s2Result = applySBox(S2, sixBitGroups[1]);
    std::bitset<4> s2Bits(s2Result);
    B_binary += s2Bits.to_string();
    std::cout << "S2(" << sixBitGroups[1] << ") = " << s2Result << " = " << s2Bits.to_string() << std::endl;

    int s3Result = applySBox(S3, sixBitGroups[2]);
    std::bitset<4> s3Bits(s3Result);
    B_binary += s3Bits.to_string();
    std::cout << "S3(" << sixBitGroups[2] << ") = " << s3Result << " = " << s3Bits.to_string() << std::endl;

    int s4Result = applySBox(S4, sixBitGroups[3]);
    std::bitset<4> s4Bits(s4Result);
    B_binary += s4Bits.to_string();
    std::cout << "S4(" << sixBitGroups[3] << ") = " << s4Result << " = " << s4Bits.to_string() << std::endl;

    int s5Result = applySBox(S5, sixBitGroups[4]);
    std::bitset<4> s5Bits(s5Result);
    B_binary += s5Bits.to_string();
    std::cout << "S5(" << sixBitGroups[4] << ") = " << s5Result << " = " << s5Bits.to_string() << std::endl;

    int s6Result = applySBox(S6, sixBitGroups[5]);
    std::bitset<4> s6Bits(s6Result);
    B_binary += s6Bits.to_string();
    std::cout << "S6(" << sixBitGroups[5] << ") = " << s6Result << " = " << s6Bits.to_string() << std::endl;

    int s7Result = applySBox(S7, sixBitGroups[6]);
    std::bitset<4> s7Bits(s7Result);
    B_binary += s7Bits.to_string();
    std::cout << "S7(" << sixBitGroups[6] << ") = " << s7Result << " = " << s7Bits.to_string() << std::endl;

    int s8Result = applySBox(S8, sixBitGroups[7]);
    std::bitset<4> s8Bits(s8Result);
    B_binary += s8Bits.to_string();
    std::cout << "S8(" << sixBitGroups[7] << ") = " << s8Result << " = " << s8Bits.to_string() << std::endl;

    std::string B_hex = binaryToHex(B_binary);

    std::cout << "\nFinal results:" << std::endl;
    std::cout << "B = S(A) (binary): " << B_binary << std::endl;
    std::cout << "B = S(A) (hex): " << B_hex << std::endl;

    return 0;
}