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
#include <bitset>
#include <optional>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
	vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
		auto compare1 = [&](int a, int b)->bool {
			if (servers[a] != servers[b]) {
				return servers[a] > servers[b];
			}
			return a > b;
			};
		priority_queue<int, vector<int>, decltype(compare1)> pqserver(compare1);
		for (int i = 0; i < size(servers); i++) {
			pqserver.push(i);
		}
		auto compare2 = [&](const pair<long long, int>& a, const pair<long long, int>& b)->bool {
			return a.first > b.first;
			};
		priority_queue<pair<long long,int>, vector<pair<long long, int>>, decltype(compare2)> pq_time(compare2);


		vector<int> ans;
		const long long n = size(tasks);
		ans.reserve(n);
		long long index = 0;
		long long t = 0;
		while (index < n) {
			while (
				pqserver.empty() || 
				(!pq_time.empty() && pq_time.top().first <= t)) {
				auto [past, server] = pq_time.top();
				t = max(t, past);
				pqserver.push(server);
				pq_time.pop();
			}

			auto selected = pqserver.top();
			pq_time.push({ t + tasks[index], selected });
			ans.push_back(selected);
			pqserver.pop();
			index++;
			t = max(t, index);
		}

		return ans;
	}
};

namespace problem1 {
static void test(vector<int>&& servers, vector<int>&& tasks) {
	output(Solution().assignTasks(servers, tasks));
}
static void run() {
	test(get_list_int("[3,3,2]"), get_list_int("[1,2,3,2,1,2]"));
	test(get_list_int("[5,1,4,3,2]"), get_list_int("[2,1,2,4,5,2,1]"));
}
}


int main() {
	problem1::run();
	return 0;
}
