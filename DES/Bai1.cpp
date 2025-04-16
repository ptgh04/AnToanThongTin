#include <iostream>
#include <bitset>
using namespace std;

const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

string hex_to_binary(const string& hex) {
    string binary = "";
    for (char c : hex) {
        int value;
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10;
        } else {
            continue;
        }

        binary += bitset<4>(value).to_string();
    }
    return binary;
}

string applyPC1(const string& keyBin) {
    string pc1_result = "";
    for (int i = 0; i < 56; ++i) {
        pc1_result += keyBin[PC1[i] - 1];
    }
    return pc1_result;
}

int main() {
    string key_hex = "B35F59255E3BCB54";

    string key = hex_to_binary(key_hex);

    string pc1_result = applyPC1(key);

    string C0 = pc1_result.substr(0, 28);
    string D0 = pc1_result.substr(28, 28);

    cout << "K = " << key_hex << endl;
    cout << "C0 = " << C0 << endl;
    cout << "D0 = " << D0 << endl;

    return 0;
}
