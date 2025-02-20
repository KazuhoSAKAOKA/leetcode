// leetcode_Q1980.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    static int get_num(const string& numstr) {
        int num = 0;
        int index = 0;
        for (auto it = crbegin(numstr); it != crend(numstr); ++it) {
            if (*it == '1') {
                num |= (1 << index);
            }
            index++;
        }
        return num;
    }

    static string get_str(int num, size_t len) {
        string ans(len, '0');
        for (int i = 0; i < len; i++) {
            if (((1 << i) & num) != 0) {
                ans[len - i - 1] = '1';
            }
        }
        return ans;
    }

    string findDifferentBinaryString(vector<string>& nums) {
        unordered_set<int> exists;
        for (auto&& num : nums) {
            exists.insert(get_num(num));
        }
        for (int i = 0; i < 0xffff; i++) {
            if (exists.count(i) == 0) {
                return get_str(i, size(nums));
            }
        }
        throw exception();
    }
};

int main()
{

    return 0;
}