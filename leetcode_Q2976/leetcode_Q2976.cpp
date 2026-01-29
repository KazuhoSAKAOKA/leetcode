// leetcode_Q2976.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <minmax.h>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

constexpr long long INF = LLONG_MAX;
constexpr size_t SIZE = 'z' - 'a' + 1;

class Solution {
public:
	struct path {
		int cost_;
		char to_;
	};

	static vector<long long> djikstra(const vector<vector<path>>& graph, char s) {
		vector<long long> costs(SIZE, INF);
		struct point {
			long long cost;
			char pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, vector<point>, greater<point>> p_queue;
		p_queue.push(point{ 0, s });
		costs[s] = 0;
		while (!p_queue.empty()) {
			const point current = p_queue.top();
			p_queue.pop();
			if (costs[current.pos] < current.cost) { continue; }
			for (auto&& p : graph[static_cast<size_t>(current.pos)]) {
				if (costs[p.to_] > p.cost_ + current.cost) {
					costs[p.to_] = p.cost_ + current.cost;
					p_queue.push(point{ costs[p.to_] , p.to_ });
				}
			}
		}
		return costs;
	}

    long long minimumCost_past(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {

		vector<vector<path>> graph(SIZE);
		for (int i = 0; i < original.size(); i++) {
			graph[original[i] - 'a'].push_back({cost[i], static_cast<char>(changed[i] - 'a') });
		}

		vector<vector<long long>> min_costs;
		min_costs.reserve(SIZE);
		for (int i = 0; i < SIZE; i++) {
			min_costs.emplace_back(djikstra(graph, static_cast<char>(i)));
		}

        long long total = 0;
        for (size_t i = 0; i < source.size(); i++) {
            const auto cost = min_costs[source[i] - 'a'][target[i] - 'a'];
            if (cost == INF) { return -1; }
            total += cost;
        }
        return total;
    }

	long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
		constexpr long long INFINITE = LLONG_MAX;
		vector<vector<long long>> dist(26, vector<long long>(26, INFINITE));
		for (int i = 0; i < original.size(); i++) {
			const auto u = original[i] - 'a';
			const auto v = changed[i] - 'a';
			dist[u][v] = min(dist[u][v], static_cast<long long>(cost[i]));
		}
		for (int i = 0; i < 26; i++) {
			dist[i][i] = 0LL;
		}
		for (int k = 0; k < 26; k++) {
			for (int i = 0; i < 26; i++) {
				for (int j = 0; j < 26; j++) {
					if (dist[i][k] != INFINITE && dist[k][j] != INFINITE) {
						dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
					}
				}
			}
		}

		long long total = 0;
		for (size_t i = 0; i < source.size(); i++) {
			const auto cost = dist[source[i] - 'a'][target[i] - 'a'];
			if (cost == INFINITE) { return -1; }
			total += cost;
		}
		return total;
	}

};

void test(string&& source, string&& target, vector<char>&& original, vector<char>&& changed, vector<int>&& cost) {
    cout << Solution().minimumCost(source, target, original, changed, cost) << endl;
}


int main()
{
    test("abcd", "acbe", get_list_char(R"(["a","b","c","c","e","d"])"), get_list_char(R"(["b","c","b","e","b","e"])"), get_list_int("[2,5,5,1,2,20]"));
    test("aaaa", "bbbb", get_list_char(R"(["a","c"])"), get_list_char(R"(["c","b"])"), get_list_int("[1,2]"));
    test("abcd", "abce", get_list_char(R"(["a"])"), get_list_char(R"(["e"])"), get_list_int("[10000]"));

    return 0;
}