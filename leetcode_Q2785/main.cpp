#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
class Solution {
public:

    static bool is_vowel(char c) {
        return
            c == 'A' ||
            c == 'I' ||
            c == 'U' ||
            c == 'E' ||
            c == 'O' ||
            c == 'a' ||
            c == 'i' ||
            c == 'u' ||
            c == 'e' ||
            c == 'o';
    }

    string sortVowels(string s) {
        vector<char> vowels;
        for (auto&& c : s) {
            if (is_vowel(c)) {
                vowels.emplace_back(c);
            }
        }
        if (vowels.empty()) { return s; }
        sort(begin(vowels), end(vowels));
        int index = 0;

        for (int i = 0; i < size(s); i++) {
            if (is_vowel(s[i])) {
                s[i] = vowels[index++];
            }
        }
        return s;
    }
};
static void test(string&& s) {
    cout << Solution().sortVowels(s) << endl;
}
int main() {
    test("lEetcOde");
    test("lYmpH");
    return 0;
}