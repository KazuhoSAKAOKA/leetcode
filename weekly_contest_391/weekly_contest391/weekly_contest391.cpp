// weekly_contest391.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numbers>
#include <queue>

using namespace std;


namespace problem1 {

class Solution {
public:

    static int sum_digits(int x) {
        int sum = 0;
        while (x > 0) {
            const auto d = x % 10;
            sum += d;
            x /= 10;
        }
        return sum;
    }

    int sumOfTheDigitsOfHarshadNumber(int x) {
        if (x == 0) {
            return -1;
        }
        const auto sum_of_digits = sum_digits(x);
        if (x % sum_of_digits == 0) {
            return sum_of_digits;
        }
        return - 1;
    }
};
void test(int x) {
    cout << Solution().sumOfTheDigitsOfHarshadNumber(x) << endl;
}

void run() {
    test(18);
    test(23);
    test(100);
}
}


namespace problem2 {

class Solution {
public:
    using memo_key_t = tuple<int, int, int>;
    using memo_t = map<memo_key_t, int>;
    static int rec(int numBottles, int numExchange, int empty_bottles, memo_t& memo) {
        if (numBottles == 0 && empty_bottles < numExchange) {
            return 0;
        }

        const auto key = memo_key_t(numBottles, numExchange, empty_bottles);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }
        int value = 0;

        if (numBottles > 0) {
            value += numBottles;
            value += rec(0, numExchange, empty_bottles + numBottles, memo);
        }
        else if (numExchange <= empty_bottles) {
            value += rec(numBottles + 1, numExchange + 1, empty_bottles - numExchange, memo);
        }

        memo[key] = value;
        return value;
    }


    int maxBottlesDrunk(int numBottles, int numExchange) {
        memo_t memo;
        return rec(numBottles, numExchange, 0, memo);
    }
};
void test(int numBottles, int numExchange) {
    cout << Solution().maxBottlesDrunk(numBottles, numExchange) << endl;
}

void run() {
    test(13, 6);
    test(10, 3);
}
}

namespace problem3 {

class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        
        vector<int> dp(nums.size(), 0);
        dp[0] = 1;
        long long total = dp[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                dp[i] = 1;
            }
            else {
                dp[i] = dp[i - 1] + 1;
            }
            total += dp[i];
        }
        return total;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().countAlternatingSubarrays(nums) << endl;
}

void run() {
    test({ 0,1,1,1, });
    test({ 1,0,1,0 });
}
}


namespace problem4 {

class Solution {
public:


    /*
    static int get_min_manhattan_distances(vector<vector<int>>& points, int ignore) {
        int max_dist = 0;
        for (int i = 0; i < points.size() - 1; i++) {
            if (i == ignore) { continue; }
            for (int j = i + 1; j < points.size(); j++) {
                if (j == ignore) { continue; }
                const auto dist = get_manhattan_distance(points[i], points[j]);
                max_dist = max(max_dist, dist);
            }
        }
        return max_dist;
    }

    struct dist_and_indexes {
        int dist;
        int i;
        int j;
        bool operator <(const dist_and_indexes& b) const { return this->dist < b.dist; }
    };
    using pq_t = priority_queue<dist_and_indexes>;
    static int get_min_manhattan_distances(const vector<dist_and_indexes>& list, int ignore) {
        int i = 0;
        while (list[i].i == ignore || list[i].j == ignore) {
            i++;
        }
        return list[i].dist;
    }
    int minimumDistance(vector<vector<int>>& points) {
        vector<dist_and_indexes> list;
        for (int i = 0; i < points.size() - 1; i++) {
            for (int j = i + 1; j < points.size(); j++) {
                const auto dist = get_manhattan_distance(points[i], points[j]);
                list.emplace_back(dist_and_indexes{ dist, i, j });
            }
        }

        sort(begin(list), end(list), [](const auto& a, const auto& b) {return a.dist > b.dist; });

        int min_value = INT_MAX;
        for (int i = 0; i < points.size(); i++) {
            min_value = min(min_value, get_min_manhattan_distances(list, i));
        }
        return min_value;
    }
    */


    int minimumDistance(vector<vector<int>>& points) {
        using cp = pair<int, int>;
        multiset<cp> sd_set;
        for (int i = 0; i < points.size(); i++) {
            sd_set.insert(cp(points[i][0] - points[i][1], points[i][0] + points[i][1]));
        }

        int min_value = INT_MAX;
        for (int i = 0; i < points.size(); i++) {
            cp current = cp(points[i][0] - points[i][1], points[i][0] + points[i][1]);
            sd_set.erase(sd_set.find(current));
            const auto el_x = minmax_element(cbegin(sd_set), cend(sd_set), [](const auto& a, const auto& b) { return a.first < b.first; });
            const auto el_y = minmax_element(cbegin(sd_set), cend(sd_set), [](const auto& a, const auto& b) { return a.second < b.second; });
            min_value = min(min_value, max(el_x.second->first - el_x.first->first, el_y.second->second - el_y.first->second));
            sd_set.insert(current);
        }
        return min_value;
    }
};
void test(vector<vector<int>>&& points) {
    cout << Solution().minimumDistance(points) << endl;
}

void run() {
    test({ {3,2,},{3,9,},{7,10,},{4,4,},{8,10,},{2,7 } });
    test({ {3,10,},{5,15,},{10,2,},{4,4,}, });
    test({ {1,1,},{1,1,},{1,1,}, });
}
}

int main()
{
//	problem1::run();
//  problem2::run();
//    problem3::run();
    problem4::run();
}