#include <bits/stdc++.h>

using namespace std;

string encryptSimpleSubstitute(string s, string k) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = k[s[i] - 'a'];
        }
        else if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = k[s[i] - 'A'];
        }
    }
    return s;
}

int main() {
    string s;
    cin >> s;
    string k;
    cin >> k;
    cout << encryptSimpleSubstitute(s, k);
}