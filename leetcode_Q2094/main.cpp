#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    static void rec(vector<int>& digit_freqs, int multiple, int cur_value, vector<int>& ans) {
        if (multiple == 1) {
            for (int i = 0; i <= 8; i += 2) {
                if(digit_freqs[i] > 0){
                    ans.emplace_back(cur_value + i);
                }
            }
            return;
        }
        const auto start = multiple == 100 ? 1 : 0;
        for (int i = start; i <= 9; i++) {
            if (digit_freqs[i] > 0) {
                digit_freqs[i]--;
                rec(digit_freqs, multiple / 10, cur_value + i * multiple, ans);
                digit_freqs[i]++;
            }
        }
    }

    vector<int> findEvenNumbers(vector<int>& digits) {
        vector<int> freqs(10);
        for (auto&& digit : digits) {
            freqs[digit]++;
        }
        vector<int> ans;
        rec(freqs, 100, 0, ans);
        return ans;
    }
};

int main() {
	return 0;
}