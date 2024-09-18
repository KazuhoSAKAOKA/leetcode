// leetcode_Q0179.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    //static const string& max_str(const string& a, const string& b) {
    //    for (size_t i = 0; i < size(a); i++) {
    //        if (a[i] != b[i]) {
    //            if (a[i] < b[i]) {
    //                return b;
    //            }
    //            else {
    //                return a;
    //            }
    //        }
    //    }
    //    return a;
    //}

    static bool compare_current_problem(const string& a, const string& b) {
        return a + b > b + a;
    }

    static string rec(const vector<string>& num_strs, char current_target) {
        if (current_target == '0' - 1) {
            return "";
        }
        vector<string> candidates_upper;
        vector<string> candidates_lower;
        vector<string> candidates_eq_or_single;
        size_t eq_or_single_length = 0;
        for (auto&& num_str : num_strs) {
            if (num_str[0] == current_target) {
                if (size(num_str) == 1 || num_str[1] == current_target) {
                    candidates_eq_or_single.emplace_back(num_str);
                    eq_or_single_length += size(num_str);
                }
                else {
                    if (num_str[1] < current_target) {
                        candidates_lower.emplace_back(num_str);
                    }
                    else {
                        candidates_upper.emplace_back(num_str);
                    }
                }
            }
        }
        sort(begin(candidates_lower), end(candidates_lower), compare_current_problem);
        sort(begin(candidates_eq_or_single), end(candidates_eq_or_single), compare_current_problem);
        sort(begin(candidates_upper), end(candidates_upper), compare_current_problem);
        string work;
        for (auto&& s : candidates_upper) {
            work += s;
        }
        for (auto&& s : candidates_eq_or_single) {
            work += s;
        }
        for (auto&& s : candidates_lower) {
            work += s;
        }

        return work + rec(num_strs, current_target - 1);
    }

    
    string largestNumber(vector<int>& nums) {
        vector<string> num_strs;
        num_strs.reserve(size(nums));
        transform(cbegin(nums), cend(nums), back_inserter(num_strs), [](const auto& a) { return to_string(a); });

        auto ans = rec(num_strs, '9');
        while (size(ans) > 1 && ans[0] == '0') {
            ans = ans.substr(1);
        }
        return ans;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().largestNumber(nums) << endl;
}
int main()
{
    test(get_list_int("[34323,3432]"));
    test(get_list_int("[0,0]"));
    test(get_list_int("[1,2,3,4,5,6,7,8,9,0]"));
    test(get_list_int("[3,30,34,5,9]"));
    test(get_list_int("[10,2]"));
    test(get_list_int("[1,1,1,1,1,2,2,2,2,2]"));

    return 0;
}