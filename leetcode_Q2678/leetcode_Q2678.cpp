// leetcode_Q2678.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    int countSeniors(vector<string>& details) {
        int count = 0;
        for (auto&& detail : details) {
            const auto age_part = detail.substr(11, 2);
            const auto age = stoi(age_part);
            if (60 < age) {
                count++;
            }
        }
        return count;
    }
};

void test(vector<string>&& details) {
    cout << Solution().countSeniors(details) << endl;
}

int main()
{
    test(get_list_str(R"(["7868190130M7522","5303914400F9211","9273338290F4010"])"));
    test(get_list_str(R"(["1313579440F2036","2921522980M5644"])"));
    return 0;
}