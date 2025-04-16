#include <iostream>
#include <iomanip>
#include <cstdint>

uint32_t XORbit(uint32_t a, uint32_t b) {
    return a ^ b;
}

void printWord(const std::string& label, uint32_t word) {
    std::cout << label << " = " << std::hex << std::uppercase
              << std::setw(8) << std::setfill('0') << word << std::endl;
}

int main() {
    uint32_t xcsw = 0x3DA6CB52;
    uint32_t w0 = 0x6704C20E;
    uint32_t w1 = 0x086B3F53;
    uint32_t w2 = 0x7AE5721F;
    uint32_t w3 = 0x486DC559;

    uint32_t w4 = XORbit(xcsw, w0);
    uint32_t w5 = XORbit(w4, w1);
    uint32_t w6 = XORbit(w5, w2);
    uint32_t w7 = XORbit(w6, w3);

    std::cout << "Inputs:" << std::endl;
    std::cout << "xcsw = " << std::hex << std::uppercase << xcsw << std::endl;
    printWord("w0", w0);
    printWord("w1", w1);
    printWord("w2", w2);
    printWord("w3", w3);

    std::cout << "\nOutputs:" << std::endl;
    std::cout << "w4 = XORbit(xcsw, w0) = " << std::hex << std::uppercase << w4 << std::endl;
    std::cout << "w5 = XORbit(w4, w1) = " << std::hex << std::uppercase << w5 << std::endl;
    std::cout << "w6 = XORbit(w5, w2) = " << std::hex << std::uppercase << w6 << std::endl;
    std::cout << "w7 = XORbit(w6, w3) = " << std::hex << std::uppercase << w7 << std::endl;

    return 0;
}