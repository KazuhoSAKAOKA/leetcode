// leetcode_Q0089.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:


    static int GetValue(const vector<int>& values) {
        int total = 0;
        for (auto&& value : values) {
            total = total << 1 + value;
        }
    }

    vector<int> grayCode(int n) {
        vector<int> ret;
        const auto nn = pow(2, n);
        for (auto i = 0; i < nn; i++) {
            const auto value = i ^ (i >> 1);
            ret.emplace_back(value);
        }
        return ret;
    }
};


void test(int n) {
    const auto ret = Solution().grayCode(n);
    for (auto&& value : ret) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(2);
    test(1);
}

