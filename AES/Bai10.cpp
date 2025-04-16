#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>
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

void addRoundKey(std::vector<uint8_t>& state, const std::vector<uint8_t>& roundKey) {
    for (size_t i = 0; i < state.size(); i++) {
        state[i] ^= roundKey[i];  // XOR từng byte của state với roundKey
    }
}

int main() {
    std::string stateHex = "A927DE2C0EAA869F6C27FAAE2FEF1D4C";
    std::string keyHex = "5AA2095C52C9360F282C441060418149";

    std::vector<uint8_t> state = hexStringToBytes(stateHex);
    std::vector<uint8_t> roundKey = hexStringToBytes(keyHex);

    std::cout << "Input State: " << stateHex << std::endl;
    std::cout << "Input Key: " << keyHex << std::endl;

    addRoundKey(state, roundKey);

    std::string outputHex = bytesToHexString(state);
    std::cout << "Output after AddRoundKey: " << outputHex << std::endl;

    return 0;
}