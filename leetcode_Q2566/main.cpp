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

    static int get_remapped(const string& numv, char replace_digit) {
        string v;
        char source = 0;
        size_t index = 0;

        for (auto&& c : numv) {
            if (source == 0) {
                if (c == replace_digit) {
                    v += c;
                }
                else {
                    source = c;
                    v += replace_digit;
                }
            }
            else {
                if (c != source) {
                    v += c;
                }else{
                    v += replace_digit;
                }
            }
        }
        return stoi(v);
    }
    int minMaxDifference(int num) {
        const auto original = to_string(num);
        const auto max_value = get_remapped(original, '9');
        const auto min_value = get_remapped(original, '0');
        return max_value - min_value;
    }
};
void test(int num) {
    cout << Solution().minMaxDifference(num) << endl;
}
int main() {
    test(11891);
    test(90);
    return 0;
}