#include <cstdint>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

std::vector<uint8_t> hexStringToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

std::string bytesToHexString(const std::vector<uint8_t>& bytes) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    for (const auto& byte : bytes) {
        ss << std::setw(2) << static_cast<int>(byte);
    }
    return ss.str();
}

uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    uint8_t hi_bit_set;
    for (int i = 0; i < 8; i++) {
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1B;
        b >>= 1;
    }
    return p;
}

std::vector<uint8_t> mixColumns(const std::vector<uint8_t>& state) {
    std::vector<uint8_t> result(state.size());

    for (int col = 0; col < 4; col++) {
        uint8_t s0 = state[col * 4 + 0];
        uint8_t s1 = state[col * 4 + 1];
        uint8_t s2 = state[col * 4 + 2];
        uint8_t s3 = state[col * 4 + 3];

        result[col * 4 + 0] = gmul(0x02, s0) ^ gmul(0x03, s1) ^ s2 ^ s3;
        result[col * 4 + 1] = s0 ^ gmul(0x02, s1) ^ gmul(0x03, s2) ^ s3;
        result[col * 4 + 2] = s0 ^ s1 ^ gmul(0x02, s2) ^ gmul(0x03, s3);
        result[col * 4 + 3] = gmul(0x03, s0) ^ s1 ^ s2 ^ gmul(0x02, s3);
    }

    return result;
}

int main() {
    std::string stateHex = "D85357A0690480507373DBC409DF0245";

    std::vector<uint8_t> stateBytes = hexStringToBytes(stateHex);

    std::vector<uint8_t> resultBytes = mixColumns(stateBytes);

    std::string resultHex = bytesToHexString(resultBytes);

    std::cout << "Input:" << std::endl;
    std::cout << "state = " << stateHex << std::endl;
    std::cout << "\nOutput:" << std::endl;
    std::cout << "state = MixColumns(state) = " << resultHex << std::endl;

    return 0;
}