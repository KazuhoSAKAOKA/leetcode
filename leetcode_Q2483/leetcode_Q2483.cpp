#include <iostream>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int bestClosingTime(string customers) {
        const int n = size(customers);
        const int y_count = count_if(cbegin(customers), cend(customers), [](char c) { return c == 'Y'; });
        int min_penalty = y_count;
        int ealist_hour = 0;
        int cur_penalty = y_count;
        for (int i = 0; i < n; i++) {
            if (customers[i] == 'Y') {
                cur_penalty--;
            }
            else {
                cur_penalty++;
            }
            if (cur_penalty < min_penalty) {
                min_penalty = cur_penalty;
                ealist_hour = i + 1;
            }
        }

        return ealist_hour;
    }
};

static void test(string&& customers) {
    cout << Solution().bestClosingTime(customers) << endl;
}
int main()
{
    test("YYNY");
    test("NNNNN");
    test("YYYY");
    return 0;
}