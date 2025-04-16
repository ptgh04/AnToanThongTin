#include <cstdint>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
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
    ss << std::hex << std::setfill('0');
    for (const auto& byte : bytes) {
        ss << std::setw(2) << static_cast<int>(byte);
    }
    return ss.str();
}

std::vector<uint32_t> extractWords(const std::vector<uint8_t>& key) {
    std::vector<uint32_t> words;

    for (size_t i = 0; i < key.size(); i += 4) {
        uint32_t word = 0;
        word = (static_cast<uint32_t>(key[i]) << 24) |
               (static_cast<uint32_t>(key[i+1]) << 16) |
               (static_cast<uint32_t>(key[i+2]) << 8) |
                static_cast<uint32_t>(key[i+3]);
        words.push_back(word);
    }

    return words;
}

int main() {
    std::string keyHex = "6704C20E086B3F537AE5721F486DC559";

    std::vector<uint8_t> keyBytes = hexStringToBytes(keyHex);

    std::vector<uint32_t> words = extractWords(keyBytes);

    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << "w" << i << " = " << std::hex << std::uppercase << words[i] << std::endl;
    }

    return 0;
}