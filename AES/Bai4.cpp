#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>

uint32_t XorRcon(uint32_t sw, uint8_t roundIndex) {
    const std::vector<uint8_t> RC = {
        0x00,
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
    };

    if (roundIndex < 1 || roundIndex >= RC.size()) {
        std::cerr << "Invalid round index!" << std::endl;
        return sw;
    }

    uint32_t rcon = static_cast<uint32_t>(RC[roundIndex]) << 24;

    return sw ^ rcon;
}

int main() {
    uint32_t sw = 0x3CA6CB52;

    uint8_t roundIndex = 1;

    uint32_t xcsw = XorRcon(sw, roundIndex);

    std::cout << "Input: sw = " << std::hex << std::uppercase << sw << std::endl;
    std::cout << "Rcon[" << static_cast<int>(roundIndex) << "] = "
              << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
              << static_cast<int>(1 << (roundIndex - 1)) << "000000" << std::endl;
    std::cout << "Output: xcsw = XorRcon(sw, RC[" << static_cast<int>(roundIndex)
              << "]) = " << std::hex << std::uppercase << xcsw << std::endl;

    return 0;
}