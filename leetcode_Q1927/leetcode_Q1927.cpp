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
using namespace std;

class Solution {
public:
    bool sumGame(string num) {
        const auto n = size(num);
        long long left_questions = 0;
        long long right_questions = 0;
        long long left_total = 0;
        long long right_total = 0;
        for (size_t i = 0; i < n / 2; i++) {
            if (num[i] == '?') {
                left_questions++;
            }
            else {
                left_total += static_cast<long long>(num[i] - '0');
            }
            if (num[i + n / 2] == '?') {
                right_questions++;
            }
            else {
                right_total += static_cast<long long>(num[i + n / 2] - '0');
            }
        }
        // Aliceが最後の手番であれば勝つ
        if ((left_questions + right_questions) % 2 != 0){
            return true;
        }
        // 行動がなければ最初の状態で決まる
        if ((left_questions + right_questions) == 0) {
            return left_total != right_total;
        }
        // 片方をもう一方より上回ることができれば勝つ
        long long op_count;
        long long diff;
        if (left_questions < right_questions) {
            op_count = right_questions - left_questions;
            diff = left_total - right_total;
        }
        else {
            op_count = left_questions - right_questions;
            diff = right_total - left_total;
        }
        if (diff < 0) {
            return true;
        }
        if ((op_count / 2) * 9 < diff) {
            return true;
        }
        if ((op_count / 2) * 9 > diff) {
            return true;
        }

        return false;

    }
};
static void test(string&& num) {
    cout << Solution().sumGame(num) << endl;
}

int main() {
    //test("5023");
    test("25??");
    //test("?3295???");
    return 0;
}
