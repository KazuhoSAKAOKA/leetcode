// weekly_contest_381.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <set>

using namespace std;
namespace test1 {

class Solution {
public:
    int minimumPushes(string word) {
        int total = 0;
        int n = static_cast<int>(word.size());
        int i = 1;
        while (n > 0) {
            int v = min(8, n);
            total += v * i;
            n -= v;
            i++;
        }
        return total;
    }
};


void test(string&& word) {
    cout << Solution().minimumPushes(word) << endl;
}

}

namespace test2{
class Solution {
public:

    static int get_shortcuts(int i, int j, int x_index, int y_index)
    {
        const int cost1 = abs(i - x_index);
        const int cost2 = abs(j - y_index);
        return cost1 + cost2 + 1;
    }

    vector<int> countOfPairs(int n, int x, int y) {
        vector<int> ans(n, 0);

        const int xi = min(x, y) - 1;
        const int yi = max(x, y) - 1;

        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int length = min(j - i, get_shortcuts(i, j, xi, yi));
                ans[length - 1] += 2;
            }
        }
        return ans;
    }
};

void test(int n, int x, int y) {
    const auto ans = Solution().countOfPairs(n, x, y);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

}


namespace test3 {

    class Solution {
    public:
        int minimumPushes(string word) {
            unordered_map<char, int> count_map;
            for (auto&& c : word) {
                count_map[c]++;
            }

            vector<pair<int, int>> counts_list;
            for (auto&& kv : count_map) {
                counts_list.emplace_back(make_pair(kv.first, kv.second));
            }
            sort(begin(counts_list), end(counts_list), [](auto l, auto r) {return r.second < l.second; });


            int total = 0;
            int multiple = 1;
            int index = 0;
            for (auto&& count : counts_list) {
                const int costs = count_map[count.first] * multiple;
                total += costs;
                if (++index % 8 == 0) {
                    multiple++;
                }
            }
            return total;
        }
    };


    void test(string&& word) {
        cout << Solution().minimumPushes(word) << endl;
    }

}


namespace test4 {
class Solution {
public:

    static int get_shortcuts(int i, int j, int x_index, int y_index)
    {
        const int cost1 = abs(i - x_index);
        const int cost2 = abs(j - y_index);
        return cost1 + cost2 + 1;
    }

    vector<int> countOfPairs(int n, int x, int y) {
        vector<int> ans(n, 0);
        
        for (int i = 0; i < n; i++) {
            ans[i] = (n - 1 - i) * 2;
        }

        return ans;
    }
};

void test(int n, int x, int y) {
    const auto ans = Solution().countOfPairs(n, x, y);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

}


int main()
{
    //test1::test("abcde");
    //test1::test("xycdefghij");


    //test2::test(3, 1, 3);
    //test2::test(5, 2, 4);
    //test2::test(4, 1, 1);
    //test2::test(100, 1, 1);
    //test3::test("abcde");
    //test3::test("xycdefghij");
    //test3::test("aabbccddeeffgghhiiiiii");
    test4::test(6, 1, 1);

    test4::test(3, 1, 3);
    //test4::test(5, 2, 4);
    //test4::test(4, 1, 1);
    //test4::test(10000, 1, 1);

}

