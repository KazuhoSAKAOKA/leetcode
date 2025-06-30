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
    vector<string> partitionString(string s) {
        vector<string> ans;
        unordered_set<string> segments;
        string current_segment = "";
        for (int i = 0; i < size(s); i++) {
            current_segment += s[i];
            if (segments.find(current_segment) == cend(segments)) {
                ans.emplace_back(current_segment);
                segments.insert(current_segment);
                current_segment.clear();
            }
        }
        return ans;
    }
};
static void test(string&& s) {
    output(Solution().partitionString(s));
}
static void run() {
    test("abbccccd");
    test("aaaa");
    test("");
}
}
namespace problem2 {
class Solution {
public:

	template <typename T, typename Q>
	struct segment_tree {
		T inf_;
		std::vector<std::vector<T>> data_;
		Q query_;

		segment_tree(size_t n, Q query, T inf) :query_(query), inf_(inf) {
			allocate_buffer(n);
		}
		template<typename Container>
		segment_tree(Container& source, Q query, T inf) : query_(query), inf_(inf) {
			const size_t n = source.size();
			allocate_buffer(n);
			build(cbegin(source), cend(source));
		}

		void allocate_buffer(size_t n) {
			size_t count = 1;
			for (;;) {
				data_.emplace_back(std::vector<T>(count, inf_));
				if (n <= count) {
					break;
				}
				count *= 2;
			}
		}

		template<typename IT>
		void build(IT begin, IT end) {
			size_t index = 0;
			for (auto it = begin; it != end; ++it) {
				data_[data_.size() - 1][index++] = *it;
			}
			for (size_t depth_index = data_.size() - 1; depth_index > 0; depth_index--) {
				const auto& source = data_[depth_index];
				auto& destination = data_[depth_index - 1];
				for (size_t i = 0; i < destination.size(); i++) {
					destination[i] = query_(source[i * 2], source[i * 2 + 1]);
				}
			}
		}

		void update(size_t index, T value) {
			data_[data_.size() - 1][index] = value;
			for (size_t depth_index = data_.size() - 1; depth_index > 0; --depth_index) {
				index /= 2;
				data_[depth_index - 1][index] = query_(data_[depth_index][index * 2], data_[depth_index][index * 2 + 1]);
			}
		}

		T query(size_t a, size_t b) {
			return query(a, b, 0, 0, 0, data_.back().size());
		}

		T query(size_t a, size_t b, size_t depth_index, size_t index, size_t l, size_t r) {
			if (r <= a || b <= l) {
				return inf_;
			}
			if (a <= l && r <= b) {
				return data_[depth_index][index];
			}
			const auto left = query(a, b, depth_index + 1, index * 2, l, (l + r) / 2);
			const auto right = query(a, b, depth_index + 1, index * 2 + 1, (l + r) / 2, r);
			return query_(left, right);
		}


	};

	template <typename T = long long>
	struct seqment_tree_range_maximum_query : public segment_tree<T, std::function<T(T, T)>> {
		seqment_tree_range_maximum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
		template <typename Container>
		seqment_tree_range_maximum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
	};

    static int get_lcp(const string& a, const string& b) {
        const int cklen = min(size(a), size(b));
        for (int i = 0; i < cklen; i++) {
            if (a[i] != b[i]) {
                return i;
            }
        }
        return cklen;
    }

    vector<int> longestCommonPrefix(vector<string>& words) {
        const auto n = size(words);
		if (n == 1) {
			return { 0 };
		}
		if (n == 2) {
			return { 0, 0 };
		}

		seqment_tree_range_maximum_query<int> st(n - 1);
        for (int i = 0; i < n - 1; i++) {
			const int lcp = get_lcp(words[i], words[i + 1]);
			st.update(i, lcp);
        }

		vector<int> ans(n);

		for (int i = 0; i < n; i++) {
			int current_lcp = INT_MIN;
			int remain_max = INT_MIN;
			if (i == 0) {
				remain_max = st.query(i + 1, n);
			}
			else if (i == n - 1) {
				remain_max = st.query(0, n - 2);
			}
			else {
				current_lcp = get_lcp(words[i - 1], words[i + 1]);
				remain_max = max(st.query(0, i - 1), st.query(i + 1, n));
			}
			ans[i] = max(current_lcp, remain_max);
		}

        return ans;
    }
};
static void test(vector<string>&& words) {
    output(Solution().longestCommonPrefix(words));
}
static void run() {
	test(get_list_str(R"(["aaa","bbbb","bbbb"])"));
	test(get_list_str(R"(["fec","fef","acaa","adfa","afc","fdbda"])"));
	test(get_list_str(R"(["jump","run","run","jump","run"])"));
    test(get_list_str(R"(["dog","racer","car"])"));
}
}
namespace problem3 {
class Solution {
public:
	using memo_key_t = pair<int, int>;
	using memo_t = map<pair<int, int>, int>;

	static int rec(const vector<int>& nums, int index, int remain, memo_t& memo) {
		if (remain == 1) {
			int current_xor = 0;
			for (int i = index; i < size(nums); i++) {
				current_xor = current_xor ^ nums[i];
			}
			return current_xor;
		}
		else {
			const auto key = make_pair(index, remain);
			const auto it = memo.find(key);
			if (it != cend(memo)) {
				return it->second;
			}
			const int stop = size(nums) - index - (remain - 1);
			int min_value = INT_MAX;
			int current_xor = 0;
			for (int i = 0; i < stop; i++) {
				current_xor = current_xor ^ nums[index + i];
				const auto r1 = rec(nums, index + i + 1, remain - 1, memo);
				min_value = min(min_value, max(r1, current_xor));
			}
			memo[key] = min_value;
			return min_value;
		}
	}

	int minXor(vector<int>& nums, int k) {
		memo_t memo;
		return rec(nums, 0, k, memo);
	}
};
static void test(vector<int>&& nums, int k) {
	cout << Solution().minXor(nums, k) << endl;
}
static void run() {
	test(get_list_int("[1,2,3]"), 2);
	test(get_list_int("[2,3,3,2]"), 3);
	test(get_list_int("[1,1,2,3,1]"), 2);
}
}
namespace problem4 {
class Solution {
public:

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

		bool is_root(size_t x) {
			return root(x) == x;
		}
	};

	static bool dfs(int n, const vector<vector<int>>& graph, int current, int from, vector<bool>& visited) {
		for (auto&& next : graph[current]) {
			if (next != from) {
				if (visited[next]) {
					return false;
				}
				visited[next] = true;
				if (!dfs(n, graph, next, current, visited)) {
					return false;
				}
			}
		}

		return true;
	}

	static bool check(int n, const vector<vector<int>>& spanning_edges) {
		vector<vector<int>> graph(n);
		for (auto&& edge : spanning_edges) {
			graph[edge[0]].emplace_back(edge[1]);
			graph[edge[1]].emplace_back(edge[0]);
		}
		vector<bool> visited(n);
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				visited[i] = true;
				if (!dfs(n, graph, i, -1, visited)) {
					return false;
				}
			}
		}
		return true;
	}

	int maxStability(int n, vector<vector<int>>& edges, int k) {
		union_find uf(n);
		vector<vector<int>> spanning_edges;
		vector<vector<int>> eligible_edges;
		int min_value = INT_MAX;
		for (auto&& edge : edges) {
			if (edge.back() == 1) {
				spanning_edges.emplace_back(edge);
				uf.unite(edge[0], edge[1]);
				min_value = min(min_value, edge[2]);
			}
			else {
				eligible_edges.emplace_back(edge);
			}
		}
		if (!spanning_edges.empty()) {
			if (!check(n, spanning_edges)) {
				return -1;
			}
		}
		int count_of_spanning_edges = static_cast<int>(size(spanning_edges));
		auto check_spanning = [&]() {
			return n - 1 == count_of_spanning_edges;
			};

		sort(begin(eligible_edges), end(eligible_edges), [](const vector<int>& a, const vector<int>& b) { return a[2] > b[2]; });
		int index = 0;
		vector<int> additionals;
		while (index < size(eligible_edges) && !check_spanning()) {
			const auto& edge = eligible_edges[index];
			const auto u = edge[0];
			const auto v = edge[1];
			if (!uf.same(u, v)) {
				uf.unite(u, v);
				count_of_spanning_edges++;
				additionals.emplace_back(edge[2]);
			}
			index++;
		}
		if (!check_spanning()) {
			return -1;
		}
		const int m = static_cast<int>(size(additionals));
		for (int i = 0; i < min(k, m); i++) {
			min_value = min(min_value, additionals[m - i - 1] * 2);
		}
		for (int i = k; i < m; i++) {
			min_value = min(min_value, additionals[m - i - 1]);
		}

		return min_value;
	}
};
static void test(int n, vector<vector<int>>&& edges, int k) {
	cout << Solution().maxStability(n, edges, k) << endl;
}
static void run() {
	test(5, get_matrix_int("[[0,1,45707,1],[2,4,13364,0],[1,2,43289,0],[0,4,53529,1],[3,4,11373,0],[0,3,41012,0],[1,4,59332,1],[2,3,63737,1],[0,2,87065,0],[1,3,5973,0]]"), 3);
	test(3, get_matrix_int("[[0,1,4,0],[1,2,3,0],[0,2,1,0]]"), 2);
	test(3, get_matrix_int("[[0,1,2,1],[1,2,3,0]]"), 1);
	test(3, get_matrix_int("[[0,1,1,1],[1,2,1,1],[2,0,1,1]]"), 0);
}
}
int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}