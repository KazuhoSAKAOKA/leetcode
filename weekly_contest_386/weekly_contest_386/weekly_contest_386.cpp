// weekly_contest_386.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>

using namespace std;


namespace problem1 {

class Solution {
public:
    bool isPossibleToSplit(vector<int>& nums) {
        unordered_map<int, size_t> counts;
        for (auto&& value : nums) {
            counts[value]++;
        }

        for (auto&& [v, count] : counts) {
            if (2 < count) {
                return false;
            }
        }

        return true;
    }
};


void test(vector<int>&& nums) {
    cout << Solution().isPossibleToSplit(nums) << endl;
}

void run() {
    test({ 1,1,2,2,3,4 });
    test({ 1,1,1,1 });
}


}


namespace problem2 {

class Solution {
public:


    static long long get_max_square(const vector<int>& bottom_left1, const vector<int>& top_right1, const vector<int>& bottom_left2, const vector<int>& top_right2) {
        const int left = max(bottom_left1[0], bottom_left2[0]);
        const int bottom = max(bottom_left1[1], bottom_left2[1]);

        const int right = min(top_right1[0], top_right2[0]);
        const int top = min(top_right1[1], top_right2[1]);

        if (right <= left || top <= bottom) { return 0LL; }
        const long long len = static_cast<long long>(min(right - left, top - bottom));
        return len * len;
    }

    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        long long max_value = 0LL;

        for (int i = 0; i < bottomLeft.size() - 1; i++) {
            for (int j = i + 1; j < bottomLeft.size(); j++) {
                max_value = max(max_value, get_max_square(bottomLeft[i], topRight[i], bottomLeft[j], topRight[j]));
            }
        }
        return max_value;
    }
};

void test(vector<vector<int>>&& bottomLeft, vector<vector<int>>&& topRight) {
    cout << Solution().largestSquareArea(bottomLeft, topRight) << endl;
}

void run() {
    test({ {1,1},{2,2},{3,1} }, { {3,3},{4,4},{6,6} });
    test({ {1,1},{2,2},{1,2} }, { {3,3},{4,4},{3,4} });
    test({ {1,1},{3,3},{3,1} }, { {2,2},{4,4},{4,2} });
}


}


namespace problem3 {

class Solution {
public:

    static void rec(const vector<int>& nums, const vector<int>& changeIndices, int second_index, vector<bool>& marked, int marked_count, int remain, int& min_seconds) {

        if (marked_count == nums.size()) {
            min_seconds = min(min_seconds, second_index);
            return;
        }

        if (changeIndices.size() <= second_index) {
            return;
        }

        const int index = changeIndices[second_index] - 1;

        if (!marked[index] && nums[index] + 1 <= remain) {
            marked[index] = true;
            rec(nums, changeIndices, second_index + 1, marked, marked_count + 1, remain - nums[index], min_seconds);
            marked[index] = false;
        }
        rec(nums, changeIndices, second_index + 1, marked, marked_count, remain + 1, min_seconds);
    }

    static int tle(vector<int>& nums, vector<int>& changeIndices) {

        int min_seconds = INT_MAX;

        vector<bool> marked(nums.size(), false);
        rec(nums, changeIndices, 0, marked, 0, 1, min_seconds);

        if (min_seconds == INT_MAX) {
            return -1;
        }
        else {
            return min_seconds;
        }

    }

    static bool can_mark(const vector<int>& nums, const vector<int>& changeIndices, int sec) {
        struct time_and_index{
            int time;
            int num_index;
        };
        vector<time_and_index> last_indexs(nums.size(), {-1, -1});
        for (int i = 0; i <= sec; i++) {
            last_indexs[changeIndices[i] - 1].time = i;
            last_indexs[changeIndices[i] - 1].num_index = changeIndices[i] - 1;
        }
        if (any_of(cbegin(last_indexs), cend(last_indexs), [](const auto& a) { return a.time < 0; })) {
            return false;
        }
        sort(begin(last_indexs), end(last_indexs), [](const auto& a, const auto& b) { return a.time < b.time; });
        int used_resource = 0;
        for (int i = 0; i < nums.size(); i++) {
            const auto allow_resource = last_indexs[i].time + 1 - used_resource;
            if (allow_resource < nums[last_indexs[i].num_index] + 1) { return false; }
            used_resource += nums[last_indexs[i].num_index] + 1;
        }
        return true;
    }

    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        
        int lo = 0;
        int hi = changeIndices.size() - 1;
        while(lo < hi){
            const int mid = lo + (hi - lo) / 2;
            if (can_mark(nums, changeIndices, mid)) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        return can_mark(nums, changeIndices, lo) ? lo + 1 : -1;
    }
};
void test(vector<int>&& nums, vector<int>&& changeIndices) {
    cout << Solution().earliestSecondToMarkIndices(nums, changeIndices) << endl;
}

void run() {
    test({ 3,0,5,2,0,2 }, { 3,3,1,5,6,2,4,2,4,4,4,1,3,6,5,1,5,5,1,2,5 });
    test({ 0,2,3,0 }, { 2,4,1,3,3,3,3,3,3,2,1 });
    test({ 8,7,1,0,7,3,9,1,8,6,2,1,5 }, { 10,3,1,5,11,4,5,4,5,6,5,6,8,2,9,6,5,8,1,1,10,8,13,12,4,13,13,4,3,5,12,10,7,12,2,11,1,11,3,7,9,1,8,3,2 });
    test({ 2,2,0 }, { 2,2,2,2,3,2,2,1 });
    test({ 1,3 }, { 1,1,1,2,1,1,1 });
    test({ 0,1 }, { 2,2,2 });
}


}



int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
}