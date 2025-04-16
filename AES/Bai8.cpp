#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <cstdint>

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

std::vector<uint8_t> shiftRows(const std::vector<uint8_t>& state) {
    uint8_t matrix[4][4];
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            matrix[row][col] = state[col * 4 + row];
        }
    }


    uint8_t temp;

    temp = matrix[1][0];
    matrix[1][0] = matrix[1][1];
    matrix[1][1] = matrix[1][2];
    matrix[1][2] = matrix[1][3];
    matrix[1][3] = temp;

    temp = matrix[2][0];
    matrix[2][0] = matrix[2][2];
    matrix[2][2] = temp;
    temp = matrix[2][1];
    matrix[2][1] = matrix[2][3];
    matrix[2][3] = temp;

    temp = matrix[3][3];
    matrix[3][3] = matrix[3][2];
    matrix[3][2] = matrix[3][1];
    matrix[3][1] = matrix[3][0];
    matrix[3][0] = temp;

    std::vector<uint8_t> result(16);
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            result[col * 4 + row] = matrix[row][col];
        }
    }

    return result;
}

int main() {
    std::string stateHex = "D8DFDB50695302C473045745097380A0";

    std::vector<uint8_t> stateBytes = hexStringToBytes(stateHex);

    std::vector<uint8_t> resultBytes = shiftRows(stateBytes);

    std::string resultHex = bytesToHexString(resultBytes);

    std::cout << "Input:" << std::endl;
    std::cout << "state = " << stateHex << std::endl;
    std::cout << "\nOutput:" << std::endl;
    std::cout << "state = ShiftRows(state) = " << resultHex << std::endl;

    return 0;
}