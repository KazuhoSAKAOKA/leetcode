// leetcode_Q2053.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        unordered_map<string, size_t> exists;
        set<size_t> indexes;

        for (int i = 0; i < size(arr); i++) {
            const auto& v = arr[i];
            const auto it = exists.find(v);
            if (it == cend(exists)) {
                indexes.insert(i);
                exists.insert({v, i});
            }
            else {
                indexes.erase(it->second);
            }
        }
        int index = 0;
        auto it = cbegin(indexes);
        while (index < k - 1 && it != cend(indexes)) {
            ++index;
            ++it;
        }

        return it == cend(indexes) ? "" : arr[*it];
    }
};

void test(vector<string>&& arr, int k) {
    cout << Solution().kthDistinct(arr, k) << endl;
}
int main()
{
    test(get_list_str(R"(["d","b","c","b","c","a"])"), 2);
    test(get_list_str(R"(["aaa","aa","a"])"), 1);
    test(get_list_str(R"(["a","b","a"])"), 3);
    return 0;
}