// leetcode_Q1598.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth = 0;

        for (auto&& op : logs) {
            if (op == "../") {
                depth = max(0, depth - 1);
            }
            else if (op == "./") {

            }
            else {
                depth++;
            }
        }
        return depth;
    }
};

void test(vector<string>&& logs) {
    cout << Solution().minOperations(logs) << endl;
}
int main()
{
    test(get_list_str(R"(["d1/","d2/","../","d21/","./"])"));
    test(get_list_str(R"(["d1/","d2/","./","d3/","../","d31/"])"));
    test(get_list_str(R"(["d1/","../","../","../"])"));
    return 0;
}