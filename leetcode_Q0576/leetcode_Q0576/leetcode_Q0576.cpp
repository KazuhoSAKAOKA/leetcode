
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    static const int MOD = 1000000000 + 7;
    using memo_key_type = tuple<int, int, int>;
    using memo_type = map<memo_key_type, int>;
    int rec(int m, int n, int remain, int row, int column, memo_type& memo) {
        const auto key = memo_key_type(remain, row, column);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        if (remain == 0) {
            return 0;
        }


        int64_t count = 0;
        if (row == 0) {
            count++;
        }
        else {
            count += rec(m, n, remain - 1, row - 1, column, memo);
        }

        if (row == m - 1) {
            count++;
        }
        else {
            count += rec(m, n, remain - 1, row + 1, column, memo);
        }

        if (column == 0) {
            count++;
        }
        else {
            count += rec(m, n, remain - 1, row, column - 1, memo);
        }

        if (column == n - 1) {
            count++;
        }
        else {
            count += rec(m, n, remain - 1, row, column + 1, memo);
        }

        count %= MOD;
        memo[key] = count;
        return count;
    }

    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        memo_type memo;
        return rec(m, n, maxMove, startRow, startColumn, memo);
    }
};

void test(int m, int n, int maxMove, int startRow, int startColumn) {
    cout << Solution().findPaths(m, n, maxMove, startRow, startColumn) << endl;
}


int main()
{
    test(9, 50, 23, 5, 26);
    test(2, 2, 2, 0, 0);
    test(1, 3, 3, 0, 1);
}