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
    int maxDifference(string s, int k) {
		const auto n = size(s);
		vector<vector<int>> prefix_sum(5, vector<int>(n + 1));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 5; j++) {
				prefix_sum[j][i + 1] = prefix_sum[j][i];
			}
			prefix_sum[s[i] - '0'][i + 1]++;
		}
		int max_diff = INT_MIN;

		for (int i = 0; i < n; i++) {
			for (int j = i + k - 1; j < n; j++) {
				int odd_freq_max = INT_MIN;
				int even_freq_min = INT_MAX;
				for (int l = 0; l < 5; l++) {
					const auto freq = prefix_sum[l][j + 1] - prefix_sum[l][i];
					if (freq > 0) {
						if (freq % 2 == 0) {
							even_freq_min = min(even_freq_min, freq);
						}
						else {
							odd_freq_max = max(odd_freq_max, freq);
						}
					}
				}
				if (odd_freq_max != INT_MIN && even_freq_min != INT_MAX) {
					max_diff = max(max_diff, odd_freq_max - even_freq_min);
				}
			}
		}
		return max_diff;
    }
};

void test(string&& s, int k) {
	cout << Solution().maxDifference(s, k) << endl;
}
int main() {
	test("12233", 4);
	test("1122211", 3);
	test("110", 3);
	return 0;
}