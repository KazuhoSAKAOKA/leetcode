// leetcode_Q70.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    const vector<int> climbs{ 1,2, };
    using memo_map = map<int, long long>;

    long long count_climb_stair(int remain, memo_map& memo)
    {
        const auto it = memo.find(remain);
        if (it != cend(memo))
        {
            return it->second;
        }

        int count = 0;
        for (auto&& s : climbs)
        {
            const auto newpos = remain - s;
            if (newpos == 0)
            {
                count++;
            }
            if (remain < 0) { continue; }
            count += count_climb_stair(newpos, memo);
        }

        memo[remain] = count;
        return count;
    }

    long long climbStairs(int n) {
        memo_map memo;
        return count_climb_stair(n, memo);
    }
};

int main()
{
    std::cout << Solution().climbStairs(2) << std::endl;
    std::cout << Solution().climbStairs(3) << std::endl;
    std::cout << Solution().climbStairs(45) << std::endl;
}

