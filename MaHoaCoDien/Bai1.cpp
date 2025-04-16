#include <bits/stdc++.h>

using namespace std;

string encryptCaesar(string s, int k) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] += k;
            if (s[i] > 'z') {
                s[i] -= 26;
            }
        }
        else if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += k;
            if (s[i] > 'Z') {
                s[i] -= 26;
            }
        }
    }
    return s;
}

int main()
{
    string s;
    cin >> s;
    int k;
    cin >> k;
    cout << encryptCaesar(s, k);
}
