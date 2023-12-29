// leetcode_Q0049.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> map;

        for (auto&& str : strs) {
            string key(str);
            sort(begin(key), end(key));
            map[key].emplace_back(str);
        }

        vector<vector<string>> ret;
        for (auto& [k, innerList] : map) {
            ret.emplace_back(innerList);
        }

        return ret;
    }
};


void test(vector<string>&& strs)
{
    const auto ret = Solution().groupAnagrams(strs);
    for (auto&& list : ret) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }

    cout << endl;

}

int main()
{
    test({ "eat","tea","tan","ate","nat","bat" });
    test({});
    test({"a"});
}

