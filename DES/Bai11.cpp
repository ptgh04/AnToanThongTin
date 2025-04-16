#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

using namespace std;

const int IP_INV[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

string hex_to_binary(const string& hex) {
    string binary;
    for (char c : hex) {
        int value;
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else {
            value = 10 + (toupper(c) - 'A');
        }

        for (int i = 3; i >= 0; i--) {
            binary += ((value >> i) & 1) ? '1' : '0';
        }
    }
    return binary;
}

string binary_to_hex(const string& binary) {
    string hex;
    for (size_t i = 0; i < binary.length(); i += 4) {
        int value = 0;
        for (int j = 0; j < 4; j++) {
            value = (value << 1) | (binary[i + j] - '0');
        }

        if (value < 10) {
            hex += ('0' + value);
        } else {
            hex += ('A' + value - 10);
        }
    }
    return hex;
}

string permute(const string& input, const int* table, int output_size) {
    string output(output_size, '0');
    for (int i = 0; i < output_size; i++) {
        output[i] = input[table[i] - 1];
    }
    return output;
}

int main() {
    string L16_hex = "2CD7A82B";
    string R16_hex = "2DAC07E4";

    string L16 = hex_to_binary(L16_hex);
    string R16 = hex_to_binary(R16_hex);

    string preoutput = L16 + R16;

    string ciphertext_bin = permute(preoutput, IP_INV, 64);

    string ciphertext_hex = binary_to_hex(ciphertext_bin);

    cout << "Input values:" << endl;
    cout << "L16 = " << L16_hex << " (hex)" << endl;
    cout << "R16 = " << R16_hex << " (hex)" << endl;
    cout << endl;

    cout << "L16 (binary): " << L16 << endl;
    cout << "R16 (binary): " << R16 << endl;
    cout << "Preoutput (L16||R16): " << preoutput << endl;
    cout << endl;

    cout << "After IP^-1 permutation:" << endl;
    cout << "Ciphertext (binary): " << ciphertext_bin << endl;
    cout << "Ciphertext C (hex): " << ciphertext_hex << endl;

    return 0;
}