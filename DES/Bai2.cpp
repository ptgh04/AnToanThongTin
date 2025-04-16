#include <iostream>
#include <string>
#include <vector>
using namespace std;

string leftCircularShift(const string& bits, int shiftAmount) {
    string result = bits;
    shiftAmount = shiftAmount % bits.length();

    return bits.substr(shiftAmount) + bits.substr(0, shiftAmount);
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

    for (int i = 1; i <= 16; i++) {
        C[i] = leftCircularShift(C[i-1], shifts[i-1]);
        D[i] = leftCircularShift(D[i-1], shifts[i-1]);
    }

    cout << "Initial values:" << endl;
    cout << "C0 = " << C[0] << endl;
    cout << "D0 = " << D[0] << endl;
    cout << endl;

    cout << "Results for each round:" << endl;
    for (int i = 1; i <= 16; i++) {
        cout << "Round " << i << " (shift " << shifts[i-1] << " bit" << (shifts[i-1] > 1 ? "s" : "") << "):" << endl;
        cout << "C" << i << " = " << C[i] << endl;
        cout << "D" << i << " = " << D[i] << endl;
        cout << endl;
    }

    return 0;
}