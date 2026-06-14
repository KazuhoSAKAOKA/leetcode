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
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"

using namespace std;
class Solution {
public:
    int pairSum(ListNode* head) {
        vector<int> values;
        ListNode* cur(head);
        while (cur != nullptr) {
            values.push_back(cur->val);
            cur = cur->next;
        }
        int max_val = INT_MIN;
        for (size_t i = 0; i < size(values) / 2; i++) {
            max_val = max(max_val, values[i] + values[size(values) - i - 1]);
        }
        return max_val;
    }
};

static void test(vector<int>&& values) {
    cout << Solution().pairSum(create_listnode(values)) << endl;
}

int main() {
    test(get_list_int("[5,4,2,1]"));
    test(get_list_int("[4,2,2,3]"));
    test(get_list_int("[1,100000]"));
    return 0;
}
