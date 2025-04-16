#include <bits/stdc++.h>

using namespace std;

string encryptVigenereAutokey(string s, string key) {
    string keystream = key;

    for (int i = 0; keystream.length() < s.length(); i++) {
        keystream += s[i];
    }

    string ciphertext = "";
    for (size_t i = 0; i < s.length(); ++i) {
        char p = s[i] - 'A';
        char k = keystream[i] - 'A';
        char c = (p + k) % 26 + 'A';
        ciphertext += c;
    }
    return ciphertext;
}

int main() {
    string s;
    cin >> s;
    string k;
    cin >> k;
    cout << encryptVigenereAutokey(s, k);
}