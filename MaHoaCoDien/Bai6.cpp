#include <bits/stdc++.h>

using namespace std;

string encryptTransposition(string plaintext, string key) {
    int cols = key.length();
    int rows = (plaintext.length() + cols - 1) / cols;
    vector<string> matrix(rows, string(cols, '_'));

    int k = 0;
    for (int i = 0; i < rows && k < plaintext.length(); ++i) {
        for (int j = 0; j < cols && k < plaintext.length(); ++j) {
            matrix[i][j] = plaintext[k++];
        }
    }

    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < cols; ++i) {
        keyOrder.emplace_back(key[i], i);
    }
    sort(keyOrder.begin(), keyOrder.end());

    string cipher = "";
    for (int k = 0; k < cols; ++k) {
        int colIndex = keyOrder[k].second;
        for (int r = 0; r < rows; ++r) {
            cipher += matrix[r][colIndex];
        }
    }

    return cipher;
}

int main() {
    string s;
    cin >> s;
    string k;
    cin >> k;
    cout << encryptTransposition(s, k);
    return 0;
}