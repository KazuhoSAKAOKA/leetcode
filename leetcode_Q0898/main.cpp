#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    static int naive(const vector<int>& arr) {
        int value = 0;
        set<int> exists;
        const auto n = size(arr);
        for (int i = 0; i < n; i++) {
            int work = 0;
            for (int j = i; j < n; j++) {
                work |= arr[j];
                exists.insert(work);
            }
        }
        return static_cast<int>(size(exists));
    }

    int subarrayBitwiseORs(vector<int>& arr) {
        const auto n = size(arr);
        set<int> alls;
        set<int> prev{ arr[0] };
        alls.insert(cbegin(prev), cend(prev));
        for (int i = 1; i < n; i++) {
            set<int> current{ arr[i] };
            for (auto&& v : prev) {
                current.insert(v | arr[i]);
            }
            swap(prev, current);
            alls.insert(cbegin(prev), cend(prev));
        }
        return static_cast<int>(size(alls));
    }
};
static void test(vector<int>&& arr) {
    cout << Solution().subarrayBitwiseORs(arr) << endl;
}
int main() {
    test(get_list_int("[1,2,4]"));
    test(get_list_int("[0]"));
    test(get_list_int("[1,1,2]"));
    return 0;
}