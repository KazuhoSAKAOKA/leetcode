// leetcode_Q0093.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
public:

    void backtrack(const string& s, int index, vector<int>& nums, vector<string>& list) {
        if (nums.size() == 4 && s.size() == index) {
            string ip;
            for (int i = 0; i < 3; i++) {
                ip += to_string(nums[i]);
                ip += ".";
            }
            ip += to_string(nums[3]);
            list.emplace_back(ip);
        }
        if (nums.size() == 4 || s.size() == index) {
            return;
        }

        int len = min(3, static_cast<int>(s.size()) - index);
        for (int i = 0; i < len; i++) {
            const auto sub_str = s.substr(index, i + 1);
            if (i > 0 && sub_str[0] == '0') { break; }
            const auto num = stoi(sub_str);
            if (num == 0 && i > 0) { break; }
            if (255 < num) { break; }
            nums.emplace_back(num);
            backtrack(s, index + i + 1, nums, list);
            nums.pop_back();
        }
    }


    vector<string> restoreIpAddresses(string s) {
        vector<string> ipAddresses;
        vector<int> nums;
        nums.reserve(4);
        backtrack(s, 0, nums, ipAddresses);
        return ipAddresses;
    }
};

void test(string&& s) {
    const auto list = Solution().restoreIpAddresses(s);
    for (auto&& value : list) {
        cout << "[" << value << "],";
    }
    cout << endl;
}

int main()
{
    test("25525511135");
    test("0000");
    test("101023");
}

