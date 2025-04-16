#include <bits/stdc++.h>

using namespace std;

string encryptVigenereRepeated(string s, string k) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] += k[i % k.size()] - 'a';
            if (s[i] > 'z') {
                s[i] -= 26;
            }
        }
        else if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += k[i % k.size()] - 'A';
            if (s[i] > 'Z') {
                s[i] -= 26;
            }
        }
    }
    return s;
}

int main() {
    string s;
    cin >> s;
    string k;
    cin >> k;
    cout << encryptVigenereRepeated(s, k);
}
