
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <stack>
#include <queue>
#include <cmath>
#include <deque>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


namespace problem1 {

class Solution {
public:
	bool canAliceWin(vector<int>& nums) {
		int single_sums = 0;
		int double_sums = 0;
		for (auto&& num : nums) {
			if (num < 10) {
				single_sums += num;
			}
			else if (num < 100) {
				double_sums += num;
			}
		}
		return single_sums != double_sums;
	}
};

void test(vector<int>&& nums) {
	cout << Solution().canAliceWin(nums) << endl;
}
void run() {
	test(get_list_int("[1,2,3,4,10]"));
	test(get_list_int("[1,2,3,4,5,14]"));
	test(get_list_int("[5,5,5,25]"));
}
}
namespace problem2 {
class Solution {
public:



	static bool is_special(int value) {
		const int limit = value / 2;
		int exist = false;
		for (int i = 2; i <= limit; i++) {
			if (value % i == 0) {
				if (exist) { return false; }
				exist = true;
			}
		}
		return exist;
	}

	static int tle(int l, int r) {
		int count = 0;
		for (int i = l; i <= r; i++) {
			if (!is_special(i)) {
				count++;
			}
		}
		return count;
	}

	static vector<bool> eratosthenes(int N) {
		vector<bool> isprime(N + 1, true);
		isprime[0] = isprime[1] = false;
		for (int p = 2; p <= N; ++p) {
			if (!isprime[p]) continue;
			for (int q = p * 2; q <= N; q += p) {
				isprime[q] = false;
			}
		}
		return isprime;
	}


	int nonSpecialCount(int l, int r) {
		const int n = sqrt(r);
		const auto primes = eratosthenes(n);
		auto count = r - l + 1;
		const int b = static_cast<int>(sqrt(l));
		for (int i = b; i <= n; i++) {
			if (primes[i]){
				const auto c = i * i;
				if (l <= c && c <= r) {
					count--;
				}
			}
		}
		return count;
	}
};

void test(int l, int r) {
	cout << Solution().nonSpecialCount(l, r) << endl;
}

void run() {
	test(5, 7);
	test(1, 4);
	test(4, 16);
	test(3823, 97303);
}
}
namespace problem3 {
class Solution {
public:
	static inline bool isdominant(const pair<int,int>& k) {
		return k.second >= (k.first * k.first);
	}
	static int tle(const string& s) {
		int count = 0;
		map<pair<int, int>, int> before;
		for (int i = 0; i < s.size(); i++) {
			map<pair<int, int>, int> current;
			int zero_cnt = 0;
			int one_cnt = 0;
			if (s[i] == '1') {
				current[{0, 1}]++;
				count++;
				one_cnt = 1;
			}
			else {
				current[{1, 0}]++;
				zero_cnt = 1;
			}

			for (auto&& [k, v] : before) {
				const auto temp = make_pair(k.first + zero_cnt, k.second + one_cnt);
				current[temp] += v;
				if (isdominant(temp)) {
					count += v;
				}
			}
			before = current;
		}
		return count;
	}
	static int give_up(const string& s) {
		const int n = size(s);
		int result = 0;
		const int sqrtn = static_cast<int>(sqrt(n));
		for (int k = 1; k <= sqrtn; k++) {
			deque<int> zeros;
			int leftmost_zero = -1;
			int ones = 0;

			for (int r = 0; r < n; r++) {
				if (s[r] == '0') {
					zeros.push_back(r);
					while (size(zeros) > k) {
						ones -= (zeros.front() - leftmost_zero - 1);
						leftmost_zero = zeros.front();
						zeros.pop_front();
					}
				}
				else {
					ones++;
				}
				if (size(zeros) == k && ones >= k * k) {
					result += min(zeros.front() - leftmost_zero, ones - k * k + 1);
				}
			}
		}

		int i = 0;
		while (i < n) {
			if (s[i] == '0') {
				i++;
				continue;
			}
			int sz = 0;
			while (i < n && s[i] == '1') {
				sz++;
				i++;
			}
			result += (sz * (sz + 1)) / 2;
		}
		return result;
	}
	int numberOfSubstrings(string s) {
		return give_up(s);
	}


};
void test(string&& s) {
	cout << Solution().numberOfSubstrings(s) << endl;
}
void run() {
	test("00011");
	test("101101");
}
}
namespace problem4 {

struct union_find {

	std::vector<size_t> parents_;
	std::vector<size_t> sizes_;

	union_find(size_t n) : parents_(n, 0), sizes_(n, 1) {
		for (size_t i = 0; i < n; i++) {
			parents_[i] = i;
		}
	}

	size_t root(size_t x) {
		if (x == parents_[x]) { return x; }
		parents_[x] = root(parents_[x]);
		return parents_[x];
	}

	bool same(size_t x, size_t y) {
		return root(x) == root(y);
	}

	void unite(size_t x, size_t y) {
		const auto rootx = root(x);
		const auto rooty = root(y);
		if (rootx == rooty) { return; }
		if (sizes_[rootx] < sizes_[rooty]) {
			parents_[rootx] = rooty;
			sizes_[rooty] += sizes_[rootx];
		}
		else {
			parents_[rooty] = rootx;
			sizes_[rootx] += sizes_[rooty];
		}
	}

	size_t size(size_t x) {
		return sizes_[root(x)];
	}
};
class Solution {
public:

	static bool intersect_or_touch(const vector<int>& c1, const vector<int>& c2) {
		const long long dist2 = static_cast<long long>(c1[0] - c2[0]) * static_cast<long long>(c1[0] - c2[0]) + static_cast<long long>(c1[1] - c2[1]) * static_cast<long long>(c1[1] - c2[1]);
		return dist2 <= static_cast<long long>(c1[2] + c2[2]) * static_cast<long long>(c1[2] + c2[2]);
	}

	bool canReachCorner(int X, int Y, vector<vector<int>>& circles) {
		union_find uf(circles.size() + 4);
		for (int i = 0; i < circles.size() - 1; i++) {
			for (int j = i + 1; j < circles.size(); j++) {
				if (intersect_or_touch(circles[i], circles[j])) {
					uf.unite(i, j);
				}
			}
		}
		const int left_edge = circles.size();
		const int upper_edge = left_edge + 1;
		const int right_edge = upper_edge + 1;
		const int lower_edge = right_edge + 1;
		for (int i = 0; i < circles.size(); i++) {
			const auto& c = circles[i];
			if (c[0] <= c[2]) {
				uf.unite(left_edge, i);
			}
			if (abs(Y - c[1]) <= c[2]) {
				uf.unite(upper_edge, i);
			}
			if (abs(X - c[0]) <= c[2]) {
				uf.unite(right_edge, i);
			}
			if (c[1] <= c[2]) {
				uf.unite(lower_edge, i);
			}
		}

		if (uf.same(left_edge, right_edge) || uf.same(left_edge, lower_edge) || uf.same(right_edge, upper_edge) || uf.same(upper_edge, lower_edge)) {
			return false;
		}
		return true;
	}
};
void test(int X, int Y, vector<vector<int>>&& circles) {
	cout << Solution().canReachCorner(X, Y, circles) << endl;
}
void run() {
	test(1327, 130581, get_matrix_int("[[1196,113906,6],[329,14800,324],[1058,128057,64],[656,95310,556],[1253,67521,29],[972,28739,335],[688,30299,160],[243,94739,95]]"));
	test(6, 13, get_matrix_int("[[1,5,1],[1,5,1],[5,7,1],[3,7,2],[5,5,1],[2,10,1],[2,1,1]]"));
	test(3, 4, get_matrix_int("[[2,1,1]]"));
	test(3, 3, get_matrix_int("[[1,1,2]]"));
	test(3, 3, get_matrix_int("[[2,1,1],[1,2,1]]"));
}
}


int main()
{
	//problem1::run();
	//problem2::run();
	problem3::run();
	//problem4::run();
	return 0;
}