#include <bits/stdc++.h>

using namespace std;

string encryptPlayfair(const string& plaintext, const string& key) {
    char matrix[5][5];
    vector<bool> used(26, false);
    used['J' - 'A'] = true;
    string keyMatrixStr;

    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (!used[c - 'A']) {
            keyMatrixStr += c;
            used[c - 'A'] = true;
        }
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (!used[c - 'A']) {
            keyMatrixStr += c;
            used[c - 'A'] = true;
        }
    }

    for (int i = 0; i < 25; ++i) {
        matrix[i / 5][i % 5] = keyMatrixStr[i];
    }

    string processed;
    for (char c : plaintext) {
        if (isalpha(c)) {
            processed += toupper(c == 'J' ? 'I' : c);
        }
    }

    string result;
    for (size_t i = 0; i < processed.length(); i += 2) {
        char a = processed[i];
        char b = (i + 1 < processed.length()) ? processed[i + 1] : 'X';
        if (a == b) {
            b = 'X';
            i--;
        }

        int row1, col1, row2, col2;
        for (int r = 0; r < 5; ++r) {
            for (int c = 0; c < 5; ++c) {
                if (matrix[r][c] == a) {
                    row1 = r;
                    col1 = c;
                }
                if (matrix[r][c] == b) {
                    row2 = r;
                    col2 = c;
                }
            }
        }

        if (row1 == row2) {
            result += matrix[row1][(col1 + 1) % 5];
            result += matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            result += matrix[(row1 + 1) % 5][col1];
            result += matrix[(row2 + 1) % 5][col2];
        } else {
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }
    }

    return result;
}

int main() {
    string s;
    cin >> s;
    string k;
    cin >> k;
    cout << encryptPlayfair(s, k);
}