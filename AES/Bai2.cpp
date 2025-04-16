#include <iostream>
#include <iomanip>
#include <cstdint>

uint32_t RotWord(uint32_t word) {
    return ((word << 8) | (word >> 24));
}

void printHex(const std::string& label, uint32_t word) {
    std::cout << label << " = " << std::hex << std::uppercase
              << std::setfill('0') << std::setw(8) << word << std::endl;
}

int main() {
    uint32_t w3 = 0x486DC559;

    uint32_t rw = RotWord(w3);

    printHex("Input: w3 ", w3);
    printHex("Output: rw = RotWord(w3)", rw);

    return 0;
}