#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


const vector<int> PC2 = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

string leftCircularShift(const string& bits, int shiftAmount) {
    string result = bits;
    shiftAmount = shiftAmount % bits.length();

    return bits.substr(shiftAmount) + bits.substr(0, shiftAmount);
}

string permute(const string& input, const vector<int>& permTable) {
    string output = "";
    for (int i = 0; i < permTable.size(); i++) {
        output += input[permTable[i] - 1];
    }
    return output;
}

std::string binaryToHex(const std::string& binaryStr) {
    std::string hex;
    for (size_t i = 0; i < binaryStr.length(); i += 4) {
        std::string chunk = binaryStr.substr(i, 4);
        int value = std::stoi(chunk, nullptr, 2);
        std::stringstream ss;
        ss << std::hex << std::uppercase << value;
        hex += ss.str();
    }
    return hex;
}

int main() {
    string C0 = "0100000111010110001010011011";
    string D0 = "0111001110011010011101100111";

    if (C0.length() != 28 || D0.length() != 28) {
        cout << "Error: C0 and D0 must be 28 bits each." << endl;
        return 1;
    }

    vector<int> shifts = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    vector<string> C(17);
    vector<string> D(17);

    C[0] = C0;
    D[0] = D0;


    vector<string> K(17);

    for (int i = 1; i <= 16; i++) {
        C[i] = leftCircularShift(C[i-1], shifts[i-1]);
        D[i] = leftCircularShift(D[i-1], shifts[i-1]);

        string CiDi = C[i] + D[i];

        K[i] = permute(CiDi, PC2);
        K[i] = binaryToHex(K[i]);
    }

    cout << "Initial values:" << endl;
    cout << "C0 = " << C[0] << endl;
    cout << "D0 = " << D[0] << endl;
    cout << endl;

    cout << "Results for each round:" << endl;
    for (int i = 1; i <= 16; i++) {
        cout << "Round " << i << " (shift " << shifts[i-1] << " bit" << (shifts[i-1] > 1 ? "s" : "") << "):" << endl;
        cout << "K" << i << " = " << K[i] << " (length: " << K[i].length() << ")" << endl;
        cout << endl;
    }

    return 0;
}