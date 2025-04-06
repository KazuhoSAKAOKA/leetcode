#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
    class Solution {
    public:
        static bool sorted(const vector<int>& nums) {
            for (int i = 0; i < size(nums) - 1; i++) {
                if (nums[i] > nums[i + 1]) {
                    return false;
                }
            }
            return true;
        }
        int minimumPairRemoval(vector<int>& nums) {

            int op_count = 0;
            while (!sorted(nums)) {
                int min_sum = INT_MAX;
                int min_index = -1;
                for (int i = 0; i < size(nums) - 1; i++) {
                    if (nums[i] + nums[i + 1] < min_sum) {
                        min_sum = nums[i] + nums[i + 1];
                        min_index = i;
                    }
                }
                auto it = next(begin(nums), min_index);
                *it = min_sum;
                nums.erase(next(it));
                op_count++;
            }
            return op_count;
        }
    };
    void test(vector<int>&& nums) {

    }
static void run() {
}
}
namespace problem2 {
class Router {
    using TIMESTAMP = int;
    using SOURCE = int;
    using DESTINATION = int;
    queue<tuple<SOURCE,DESTINATION,TIMESTAMP>> buffer_;
    unordered_map<DESTINATION, map<TIMESTAMP, unordered_set<SOURCE>>> time_map_;
    size_t memory_limit_;
    size_t count_;
    void erase(const tuple<SOURCE, DESTINATION, TIMESTAMP>& key) {
        const auto& [s, d, t] = key;

        auto it = time_map_.find(d);
        if (it != cend(time_map_)) {
            auto& inner_map = it->second;
            auto it2 = inner_map.find(t);
            if (it2 != cend(inner_map)) {
                auto& inner_map2 = it2->second;
                inner_map2.erase(s);
                if (inner_map2.empty()) {
                    inner_map.erase(it2);
                }
            }
            if (inner_map.empty()) {
                time_map_.erase(it);
            }
        }
        count_--;
    }

    bool exists(int source, int destination, int timestamp) const {
        auto it = time_map_.find(destination);
        if (it == cend(time_map_)) { return false; }
        auto it2 = it->second.find(timestamp);
        if (it2 == cend(it->second)) { return false; }
        return it2->second.find(source) != cend(it2->second);
    }

public:
    Router(int memoryLimit) : memory_limit_(memoryLimit), count_(0){
    }

    bool addPacket(int source, int destination, int timestamp) {
        if (exists(source, destination, timestamp)) {
            return false;
        }
        const tuple<SOURCE, DESTINATION, TIMESTAMP> key = { static_cast<SOURCE>(source), static_cast<DESTINATION>(destination), static_cast<TIMESTAMP>(timestamp) };
        buffer_.push(key);
        time_map_[destination][timestamp].insert(source);
        count_++;
        if (count_ > memory_limit_) {
            erase(buffer_.front());
            buffer_.pop();
        }
        return true;
    }

    vector<int> forwardPacket() {
        if (buffer_.empty()) {
            return {};
        }
        const auto& t = buffer_.front();
        vector<int> packet{ get<0>(t), get<1>(t), get<2>(t) };
        erase(t);
        buffer_.pop();
        return packet;
    }

    int getCount(int destination, int startTime, int endTime) {
        int count = 0;
        auto it_outer = time_map_.find(destination);
        if (it_outer != cend(time_map_)) {
            const auto& inner_map = it_outer->second;
            auto it_begin = inner_map.lower_bound(startTime);
            auto it_end = inner_map.upper_bound(endTime);
            for (auto it = it_begin; it != it_end; ++it) {
                count += size(it->second);
            }
        }
        return count;
    }
};


static void run() {
}
}
namespace problem3 {
class Solution {
public:
    static int rec(const vector<int>& nums, int k, int limit, int index, int cur_val, int cur_prod, int cur_count) {
        if (index == size(nums)) {
            if (cur_val == k && cur_count > 0) {
                return cur_prod;
            }
            return -1;
        }

        int max_val = -1;
        max_val = max(max_val, rec(nums, k, limit, index + 1, cur_val, cur_prod, cur_count));
        if (nums[index] * cur_prod <= limit) {
            int next_val;
            if (cur_count % 2 == 0) {
                next_val = cur_val + nums[index];
            }
            else {
                next_val = cur_val - nums[index];
            }
            max_val = max(max_val, rec(nums, k, limit, index + 1, next_val, cur_prod * nums[index], cur_count + 1));
        }
        return max_val;
    }

    int maxProduct(vector<int>& nums, int k, int limit) {
        return rec(nums, k, limit, 0, 0, 1, 0);
    }
};
static void test(vector<int>&& nums, int k, int limit) {
    cout << Solution().maxProduct(nums, k, limit) << endl;
}
static void run() {
    test(get_list_int("[10,10,9,0]"), 1, 20);
    test(get_list_int("[0]"), 0, 10);
}
}
namespace problem4 {
static void run() {
}
}

int main()
{
    problem1::run();
    problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}