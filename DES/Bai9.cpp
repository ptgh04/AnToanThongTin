#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <sstream>

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

std::string xorBinaryStrings(const std::string& a, const std::string& b) {
    std::string result;
    for (size_t i = 0; i < a.length() && i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

std::string xorHexStrings(const std::string& hex1, const std::string& hex2) {
    std::string bin1 = hexToBinary(hex1);
    std::string bin2 = hexToBinary(hex2);

    while (bin1.length() < bin2.length()) bin1 = '0' + bin1;
    while (bin2.length() < bin1.length()) bin2 = '0' + bin2;

    std::string result_bin = xorBinaryStrings(bin1, bin2);

    return binaryToHex(result_bin);
}

int main() {
    std::string L0 = "FA231EC0";
    std::string R0 = "1A09800B";
    std::string F = "088D8C1F";

    std::cout << "Given values:" << std::endl;
    std::cout << "L0 = " << L0 << std::endl;
    std::cout << "R0 = " << R0 << std::endl;
    std::cout << "F = " << F << std::endl;

    std::string L1 = R0;

    std::string R1 = xorHexStrings(L0, F);

    std::cout << "\nFirst round results:" << std::endl;
    std::cout << "L1 = R0 = " << L1 << std::endl;
    std::cout << "R1 = L0 XOR F = " << R1 << std::endl;

    std::string L0_binary = hexToBinary(L0);
    std::string F_binary = hexToBinary(F);
    std::string R1_binary = xorBinaryStrings(L0_binary, F_binary);

    std::cout << "\nBinary verification:" << std::endl;
    std::cout << "L0 (binary): " << L0_binary << std::endl;
    std::cout << "F (binary): " << F_binary << std::endl;
    std::cout << "R1 = L0 XOR F (binary): " << R1_binary << std::endl;

    return 0;
}