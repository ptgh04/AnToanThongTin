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

std::vector<uint8_t> addRoundKey(const std::vector<uint8_t>& state, const std::vector<uint8_t>& roundKey) {
    std::vector<uint8_t> result(state.size());

    for (size_t i = 0; i < state.size(); ++i) {
        result[i] = state[i] ^ roundKey[i];
    }

    return result;
}

int main() {
    std::string messageHex = "4AEB5D62EC3B55DBF5D5A87708E2FF1E";
    std::string keyHex = "6704C20E086B3F537AE5721F486DC559";

    std::vector<uint8_t> messageBytes = hexStringToBytes(messageHex);
    std::vector<uint8_t> keyBytes = hexStringToBytes(keyHex);

    std::vector<uint8_t> resultBytes = addRoundKey(messageBytes, keyBytes);

    std::string resultHex = bytesToHexString(resultBytes);

    std::cout << "Input:" << std::endl;
    std::cout << "M (input) = " << messageHex << std::endl;
    std::cout << "K (input) = " << keyHex << std::endl;
    std::cout << "\nOutput:" << std::endl;
    std::cout << "state = AddRoundKey(M, K) = " << resultHex << std::endl;

    return 0;
}