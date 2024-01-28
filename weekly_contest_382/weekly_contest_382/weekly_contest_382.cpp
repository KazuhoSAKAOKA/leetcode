// weekly_contest_382.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

#include <vector>
#include <algorithm>
#include <map>



using namespace std;


namespace test1 {

class Solution {
public:
    int countKeyChanges(string s) {
        if (s.empty()) { return 0; }
        int count = 0;

        char before = s[0];
        for (int i = 1; i < s.size(); i++) {
            const auto diff = abs(s[i] - before);
            if (diff != 0 && diff != 32) {
                count++;
            }
            before = s[i];
        }
        return count;
    }
};

void test(string&& s) {
    cout << Solution().countKeyChanges(s) << endl;
}


void test() {
    test("aAbBcC");
    test("AaAaAaaA");
}

}



namespace test2 {

class Solution {
public:

    //static bool judge(const vector<int>& current) {
    //    const auto size = current.size();
    //    if (size % 2 != 1) { return false; }
    //    int64_t value = current[0];
    //    for (int i = 0; i < current.size() / 2; i++)
    //    {
    //        if (current[i * 2] != value || current[i * 2 + 1] != value)
    //        {
    //            return false;
    //        }
    //        value = value * value;
    //    }
    //    return current[current.size() - 1] == value;
    //}


    //static int subset_len(const vector<int>& nums, int index, int n, vector<int>& current)
    //{
    //    if (n == current.size()) {
    //        if (judge(current)) {
    //            return static_cast<int>(current.size());
    //        }
    //        return 0;
    //    }


    //    int max_value = 0;
    //    for (int i = index; i < nums.size(); i++)
    //    {
    //        current.emplace_back(nums[i]);
    //        max_value = max(max_value, subset_len(nums, i + 1, n, current));
    //        current.pop_back();
    //    }
    //    return max_value;

    //}

    //static bool judge(const map<int, size_t>& nums_map, const vector<int64_t>& current) {
    //    int64_t value = current.back();
    //    return nums_map.find(value * value) != cend(nums_map);
    //}
    //using memo_key_type = tuple<int, int, int, int>;
    //using memo_type = map<memo_key_type, int>;

    //static int subset_len(const map<int, size_t>& nums_map, map<int, size_t>::const_iterator map_it, int n, vector<int64_t>& current, memo_type& memo)
    //{
    //    if (cend(nums_map) == map_it) { return 0; }
    //    if (n == current.size() * 2 + 1) {
    //        if (judge(nums_map, current)) {
    //            return static_cast<int>(current.size() * 2 + 1);
    //        }
    //        return 0;
    //    }

    //    const auto key = memo_key_type(n, map_it->first, current.size(), current.empty() ? 0 : current.back());
    //    const auto memo_it = memo.find(key);
    //    if (memo_it != cend(memo)) {
    //        return memo_it->second;
    //    }

    //    int max_value = 0;
    //    for (map<int, size_t>::const_iterator it = map_it; it != cend(nums_map); ++it)
    //    {
    //        if (it->second < 2) { continue; }
    //        if (!current.empty() && it->first != current.back() * current.back()) { continue; }
    //        current.emplace_back(it->first);
    //        max_value = max(max_value, subset_len(nums_map, next(it), n, current, memo));
    //        current.pop_back();
    //    }
    //    memo[key] = max_value;
    //    return max_value;
    //}



    int maximumLength(vector<int>& nums) {
        if (nums.size() == 0) { return 0; }
        map<int, int> count_map;
        for (auto&& value : nums) {
            count_map[value]++;
        }
        map<int, int> dp;
        int max_value = count_map[1] % 2 == 0 ? (count_map[1] - 1) : count_map[1];

        auto it = cbegin(count_map);
        if (it->first == 1) { ++it; }
        for (; it != cend(count_map);++it) {
            auto& [key, count] = *it;
            const int before = sqrt(key);
            max_value = max(max_value, dp[before] * 2 + 1);
            if (count > 1) {
                dp[key] = dp[before] + 1;
            }
        }
        return max_value;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().maximumLength(nums) << endl;
}


void test() {
    test({ 1,1,1,1,1,1,1,1,1,1,2,4,8,16,32,64,128,256,512,1024 });
    test({ 449,659,363,362673936,262144,434281,19044,138,615,490,449,131769,138,262144,362673936,434281,240100,240100,363,201601,19044,615,131769,512,378225,659,201601,378225,490,512 });
    test({ 14,14,196,196,38416, });
    test({ 5,4,1,2,2 });
    test({ 1,3,2,4 });
}

}


int main()
{
    //test1::test();
    test2::test();
}