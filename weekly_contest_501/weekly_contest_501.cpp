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

namespace problem1 {
class Solution {
public:
	vector<int> concatWithReverse(vector<int>& nums) {
		vector<int> ans;
		ans.reserve(size(nums) * 2);
		for (auto&& num : nums) {
			ans.emplace_back(num);
		}
		for (auto it = crbegin(nums); it != crend(nums);++it) {
			ans.emplace_back(*it);
		}
		return ans;
	}
};

static void test(vector<int>&& nums) {
	output(Solution().concatWithReverse(nums));
}
static void run() {
	test(get_list_int("[1,2,3]"));
	test(get_list_int("[1]"));
}
}

namespace problem2 {
class Solution {
public:

	struct trie_tree {
		struct node {
			vector<size_t> keys_;
			bool ended_ = false;
			std::unordered_map<char, node*> nodes_;
		};
		node root_;

		void add(const std::string& s, size_t key) {
			node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
					current = (itnew->second);
				}
			}
			current->ended_ = true;
			current->keys_.push_back(key);
		}

		vector<size_t> query(const std::string& s) const {
			const node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					return {};
				}
			}
			vector<size_t> keys(current->keys_);
			return keys;
		}


	};

	vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries) {
		map<string, size_t> mp;
		string work;
		auto check = [&]() {
			while (!work.empty() && work.back() == '-') {
				work.pop_back();
			}
			mp[work]++;
			work = "";
			};

		for (auto&& chunk : chunks) {
			for (auto&& c : chunk) {
				if (c == ' ') {
					check();
				}
				else if (c == '-') {
					if (work.empty()) {
					}
					else {
						if (work.back() == '-') {
							check();
						}
						else {
							work += c;
						}
					}
				}
				else {
					work += c;
				}
			}
		}
		if (!work.empty()) {
			check();
		}


		vector<int> ans(size(queries), 0);

		for (size_t i = 0; i < size(queries); i++) {
			auto it = mp.find(queries[i]);
			if (it != cend(mp)) {
				ans[i] = it->second;
			}
		}


		return ans;
	}
};
static void test(vector<string>&& chunks, vector<string>&& queries) {
	output(Solution().countWordOccurrences(chunks, queries));
}
static void run() {
	test(get_list_str(R"(["h-t x- "])"), get_list_str(R"(["h-t","nigc","z","x"])"));
	test(get_list_str(R"(["hello wor","ld hello"])"), get_list_str(R"(["hello","world","wor"])"));
	test(get_list_str(R"(["a--b a-","-c"])"), get_list_str(R"(["a","b","c"])"));
	test(get_list_str(R"(["hello"])"), get_list_str(R"(["hello","ell"])"));
}
}

namespace problem3 {
class Solution {
public:

	long long tle(vector<int>& nums) {
		map<long long, size_t> freq_map;
		for (auto&& num : nums) {
			freq_map[num]++;
		}

		for (auto it = begin(freq_map); it != cend(freq_map);) {
			for (auto it1 = next(it); it1 != end(freq_map);) {
				if (it1->first % it->first == 0) {
					it->second += it1->second;
					it1 = freq_map.erase(it1);
				}
				else {
					++it1;
				}
			}
			++it;
		}
		long long ans = 0LL;
		for (auto&& [num, count] : freq_map) {
			ans += num * count;
		}
		return ans;
	}

	static vector<long long> divisor(long long n) {
		vector<long long> ret;
		for (long long i = 1; i * i <= n; i++) {
			if (n % i == 0) {
				ret.push_back(i);
				if (i * i != n) { ret.push_back(n / i); }
			}
		}
		sort(ret.begin(), ret.end());
		return ret;
	}

	long long minArraySum(vector<int>& nums) {
		map<long long, size_t> freq_map;
		for (auto&& num : nums) {
			freq_map[num]++;
		}

		long long ans = 0;
		for (auto it = rbegin(freq_map); it != rend(freq_map); ++it) {
			const auto ds = divisor(it->first);
			for (size_t i = 0; i < size(ds) - 1; i++) {
				auto it1 = freq_map.find(ds[i]);
				if (it1 != end(freq_map)) {
					it1->second += it->second;
					it->second = 0;
					break;
				}
			}
			ans += it->first * it->second;
		}

		return ans;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().minArraySum(nums) << endl;
}
static void run() {
	test(get_list_int("[3,6,2]"));
	test(get_list_int("[4,2,8,3]"));
	test(get_list_int("[7,5,9]"));
}
}

namespace problem4 {
class Solution {
public:
	vector<int> tle(int n, vector<int>& prices, vector<vector<int>>& roads) {
		constexpr long long INF = LLONG_MAX / 2;
		vector<vector<long long>> dist(n * 2, vector<long long>(n * 2, INF));

		for (size_t i = 0; i < n; i++) {
			dist[i][i + n] = prices[i];
		}

		for (auto&& edge : roads) {
			const auto u = edge[0];
			const auto v = edge[1];
			const auto c = edge[2];
			const auto m = edge[3];
			dist[u][v] = c;
			dist[v][u] = c;

			dist[u + n][v + n] = static_cast<long long>(c) * m;
			dist[v + n][u + n] = static_cast<long long>(c) * m;
		}

		for (int k = 0; k < n * 2; k++) {
			for (int i = 0; i < n * 2; i++) {
				for (int j = 0; j < n * 2; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
		vector<int> ans(n);

		for (size_t i = 0; i < n; i++) {
			ans[i] = dist[i][i + n];
		}
		return ans;
	}

	template <typename T>
	static vector<T> djikstra(const std::vector<vector<pair<long long, size_t>>>& graph, size_t s) {
		std::vector<T> costs(graph.size(), std::numeric_limits<T>::max() / 3);
		struct point {
			T cost;
			size_t pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ 0, s });
		costs[s] = 0;
		while (!p_queue.empty()) {
			const auto [current_cost, current] = p_queue.top();
			p_queue.pop();
			if (costs[current] < current_cost) { continue; }
			for (auto&& [cost, to] : graph[current]) {
				if (costs[to] > cost + current_cost) {
					costs[to] = cost + current_cost;
					p_queue.push(point{ costs[to] , to });
				}
			}
		}
		return costs;
	}

	vector<int> minCost(int n, vector<int>& prices, vector<vector<int>>& roads) {
		vector<int> ans(n);
		
		vector<vector<pair<long long, size_t>>> graph1(n);
		vector<vector<pair<long long, size_t>>> graph2(n);

		for (auto&& edge : roads) {
			const size_t u = edge[0];
			const size_t v = edge[1];
			const long long c = edge[2];
			const long long m = edge[3];
			graph1[u].push_back({ c, v });
			graph1[v].push_back({ c, u });

			graph2[u].push_back({ c * m, v });
			graph2[v].push_back({ c * m, u });
		}

		for (size_t i = 0; i < n; i++) {
			const auto dist1 = djikstra<long long>(graph1, i);
			const auto dist2 = djikstra<long long>(graph2, i);
			ans[i] = prices[i];
			for (size_t j = 0; j < n; j++) {
				if (i == j) { continue; }
				ans[i] = min(static_cast<long long>(ans[i]), dist1[j] + dist2[j] + prices[j]);
			}
		}
		return ans;
	}
};
static void test(int n, vector<int>&& prices, vector<vector<int>>&& roads) {
	output(Solution().minCost(n, prices, roads));
}
static void run() {
	test(2, get_list_int("[8,3]"), get_matrix_int("[[0,1,1,2]]"));
	test(3, get_list_int("[9,4,6]"), get_matrix_int("[[0,1,1,3],[1,2,4,2]]"));
	test(3, get_list_int("[10,11,1]"), get_matrix_int("[[0,2,1,3],[1,2,3,4],[0,1,5,2]]"));
}
}

int main() {
	//problem1::run();
	problem2::run();
	//problem3::run();
	//problem4::run();
	return 0;
}
