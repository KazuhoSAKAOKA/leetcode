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

    static int get_max(const string snum) {
        int index = -1;
        for (int i = 0; i < size(snum); i++) {
            if (snum[i] != '9') {
                index = i;
                break;
            }
        }
        if (index < 0) {
            return stoi(snum);
        }
        
        const char target_char = snum[index];
        string temp;
        for (auto&& c : snum) {
            if (c == target_char) {
                temp += '9';
            }
            else {
                temp += c;
            }
        }
        return stoi(temp);
    }
    static int get_min(const string snum) {
        if (all_of(next(cbegin(snum)), cend(snum), [&](char c) { return c == *cbegin(snum); })) {
            return stoi(string(size(snum), '1'));
        }
        if (snum[0] == '1') {
            int index = -1;
            for (int i = 0; i < size(snum); i++) {
                if (snum[i] != '1' && snum[i] != '0') {
                    index = i;
                    break;
                }
            }
            if (index < 0) {
                return stoi(snum);
            }
            const char target_char = snum[index];
            string temp;
            for (auto&& c : snum) {
                if (c == target_char) {
                    temp += '0';
                }
                else {
                    temp += c;
                }
            }
            return stoi(temp);

        }
        else {
            const char target_char = snum[0];
            string temp;
            for (auto&& c : snum) {
                if (c == target_char) {
                    temp += '1';
                }
                else {
                    temp += c;
                }
            }
            return stoi(temp);
        }
    }


    int maxDiff(int num) {
        const auto snum = to_string(num);
        return get_max(snum) - get_min(snum);
    }
};
void test(int num) {
    cout << Solution().maxDiff(num) << endl;
}
int main() {
    test(1101057);
    test(123456);
    test(555);
    test(9);
	return 0;
}