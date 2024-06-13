// leetcode_Q2037.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int rec(const vector<int>& students, int index, const vector<int>& seats, vector<bool>& used_seats) {
        if (index == students.size()) {
            return 0;
        }
        int min_value = INT_MAX;

        for (int i = 0; i < seats.size(); i++) {
            if (!used_seats[i]) {
                used_seats[i] = true;
                const auto dist = abs(students[index] - seats[i]);
                const auto v = rec(students, index + 1, seats, used_seats);
                min_value = min(min_value, v + dist);
                used_seats[i] = false;
            }
        }
        return min_value;
    }
    static int tle(const vector<int>& seats, const vector<int>& students) {
        vector<bool> used_seats(seats.size(), false);
        return rec(students, 0, seats, used_seats);
    }

    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        sort(begin(seats), end(seats));
        sort(begin(students), end(students));

        int total = 0;

        for (int i = 0; i < students.size(); i++) {
            total += abs(seats[i] - students[i]);
        }

        return total;
    }
};

void test(vector<int>&& seats, vector<int>&& students) {
    cout << Solution().minMovesToSeat(seats, students) << endl;
}

int main()
{
    test(get_list_int("[3,1,5]"), get_list_int("[2,7,4]"));
    test(get_list_int("[4,1,5,9]"), get_list_int("[1,3,2,6]"));
    test(get_list_int("[2,2,6,6]"), get_list_int("[1,3,2,6]"));
}