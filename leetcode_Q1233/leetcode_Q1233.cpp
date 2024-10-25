// leetcode_Q1233.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    static bool is_subfolder(const string& current, const string& target) {
        if (size(target) < size(current)) {
            return false;
        }
        const auto temp = target.substr(0, size(current));
        if (temp != current) {
            return false;
        }
        if (size(target) == size(current)) {
            throw exception();
        }
        if (target[size(current)] == '/') {
            return true;
        }
        else {
            return false;
        }
    }

    vector<string> removeSubfolders(vector<string>& folder) {
        sort(begin(folder), end(folder));


        vector<string> ans;

        int index = 1;
        string current = folder.front();
        ans.emplace_back(current);
        while (index < size(folder)) {
            if (!is_subfolder(current, folder[index])) {
                current = folder[index];
                ans.emplace_back(folder[index]);
            }
            index++;
        }


        return ans;

    }
};

void test(vector<string>&& folder) {
    output(Solution().removeSubfolders(folder));
}

int main()
{
    test(get_list_str(R"(["/a","/a/b","/c/d","/c/d/e","/c/f"])"));
    test(get_list_str(R"(["/a","/a/b/c","/a/b/d"])"));
    test(get_list_str(R"(["/a/b/c","/a/b/ca","/a/b/d"])"));
    return 0;
}