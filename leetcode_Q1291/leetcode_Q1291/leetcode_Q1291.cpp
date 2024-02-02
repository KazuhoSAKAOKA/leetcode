// leetcode_Q1291.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:

    int to_int(const vector<int>& digits) {
        int value = 0;
        int base = 1;
        for (auto it = crbegin(digits); it != crend(digits); ++it) {
            value += *it * base;
            base *= 10;
        }
        return value;
    }

    static bool next(vector<int>& digits) {
        if (digits.back() < 9) {
            for (int i = 0; i < digits.size(); i++) {
                digits[i] = digits[i] + 1;
            }
        }
        else {
            if (digits.size() == 9) { return false; }
            for (int i = 0; i < digits.size(); i++) {
                digits[i] = i + 1;
            }
            digits.push_back(static_cast<int>(digits.size()) + 1);
        }
        return true;
    }



    vector<int> sequentialDigits(int low, int high) {
        vector<int> ans;
        const auto columns = static_cast<int>(log10(low));
        vector<int> digits;
        const auto limit = max(1, columns);
        for (int i = 0; i < limit; i++) {
            digits.emplace_back(i + 1);
        }

        while (to_int(digits) < low) {
            if (!next(digits)) {
                return ans;
            }
        }


        for (;;){
            const auto value = to_int(digits);
            if (high < value) { break; }
            ans.emplace_back(value);
            if (!next(digits)) { break; }
        }

        return ans;
    }
};

void test(int low, int high) {
    const auto ans = Solution().sequentialDigits(low, high);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(1, 300);

    test(100, 300);
    test(1000, 13000);
}