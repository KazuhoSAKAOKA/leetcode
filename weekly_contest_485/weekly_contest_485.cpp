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
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    int vowelConsonantScore(string s) {
        const set<char> vowels{'a','i','u','e','o',};
        int v = 0;
        int c = 0;
        for (auto&& x : s) {
            if (std::isalpha(x)) {
                if (vowels.count(x) == 0) {
                    c++;
                }
                else {
                    v++;
                }
            }
        }
        if (c == 0) { return 0; }
        return static_cast<int>(v / c);
    }
};
static void test(string&& s) {
    cout << Solution().vowelConsonantScore(s) << endl;
}
static void run() {
    test("cooear");
    test("axeyizou");
    test("au 123");
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
	};

    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        const auto n = size(costs);

		using seqment_tree = seqment_tree_range_maximum_query<int>;
		seqment_tree st(1e5 + 1);
		int max_capacity = 0;
		if (costs[0] < budget) {
			max_capacity = capacity[0];
			st.update(costs[0], capacity[0]);
		}
		for (int i = 1; i < n; i++) {
			if (costs[i] < budget) {
				max_capacity = max(max_capacity, capacity[i]);
				const int remain = budget - costs[i];
				if (remain > 0) {
					const auto remain_capacity = st.query(0, remain);
					max_capacity = max(max_capacity, capacity[i] + remain_capacity);
				}
				if (st.query(costs[i], costs[i] + 1) < capacity[i]) {
					st.update(costs[i], capacity[i]);
				}
			}
		}
		return max_capacity;
    }
};
static void test(vector<int>&& costs, vector<int>&& capacity, int budget) {
    cout << Solution().maxCapacity(costs, capacity, budget) << endl;
}
static void run() {
	test(get_list_int("[3,5,7,4]"), get_list_int("[2,4,3,6]"), 7);
	test(get_list_int("[4,8,5,3]"), get_list_int("[1,5,2,7]"), 8);
    test(get_list_int("[2,2,2]"), get_list_int("[3,5,4]"), 5);
}
}

namespace problem3 {
class AuctionSystem {
	map<pair<int, int>, int> user_item__amount_map;
	map<int, map<int, multiset<int, greater<int>>, greater<int>>> item_amount_user_map;

	void remove(int userId, int itemId, map<pair<int, int>, int>::const_iterator it1) {
		const auto past_amount = it1->second;
		auto& inner_userset = item_amount_user_map[itemId][past_amount];
		auto it = inner_userset.find(userId);
		if (it == cend(inner_userset)) {
			throw runtime_error("invalid data or bug");
		}
		inner_userset.erase(it);
		if (inner_userset.empty()) {
			item_amount_user_map[itemId].erase(past_amount);
		}
	}

	void update(int userId, int itemId, int bidAmount) {
		const auto key = make_pair(userId, itemId);
		auto it1 = user_item__amount_map.find(key);
		if (it1 != cend(user_item__amount_map)) {
			remove(userId, itemId, it1);
			it1->second = bidAmount;
		}
		else {
			user_item__amount_map.insert({ key, bidAmount });
		}

		item_amount_user_map[itemId][bidAmount].insert(userId);
	}

public:
	AuctionSystem() {
	}



	void addBid(int userId, int itemId, int bidAmount) {
		update(userId, itemId, bidAmount);
	}

	void updateBid(int userId, int itemId, int newAmount) {
		update(userId, itemId, newAmount);
	}

	void removeBid(int userId, int itemId) {
		const auto key = make_pair(userId, itemId);
		auto it1 = user_item__amount_map.find(key);
		if (it1 != cend(user_item__amount_map)) {
			remove(userId, itemId, it1);
			user_item__amount_map.erase(it1);
		}
	}

	int getHighestBidder(int itemId) {
		const auto it1 = item_amount_user_map.find(itemId);
		if (it1 == cend(item_amount_user_map)) { return -1; }
		const auto& amount_user_map = it1->second;
		if (amount_user_map.empty()) { return -1; }
		const auto& user_set = cbegin(amount_user_map)->second;
		return *cbegin(user_set);
	}
};
	
static void testcase1() {
	AuctionSystem as;
	//["AuctionSystem","getHighestBidder","getHighestBidder","addBid","removeBid","getHighestBidder","addBid", "addBid",   "removeBid","removeBid","addBid","addBid","addBid",   "addBid"]
	//[[],             [10],              [6],               [6,9,73],[6,9],      [1],               [18,11,58],[9,12,50],[9,12],     [18,11],    [7,4,70],[1,16,57],[1,13,100],[6,9,97]]
	cout << as.getHighestBidder(10);
	cout << as.getHighestBidder(6);
	as.addBid(6, 9, 73);
	as.removeBid(6, 9);
	cout << as.getHighestBidder(1);
	as.addBid(18, 11, 58);
	as.addBid(9, 12, 50);
	as.removeBid(9, 12);
	as.removeBid(18, 11);
	as.addBid(7, 4, 70);
	as.addBid(1, 16, 57);
	as.addBid(1, 13, 100);
	as.addBid(6, 9, 97);
}

static void run() {
	testcase1();
}
}

namespace problem4 {
class Solution {
public:


	string lexSmallestAfterDeletion(string s) {
		//vector<deque<int>> appears(26);
		//for (int i = 0; i < size(s); i++) {
		//	appears[s[i] - 'a'].push_back(i);
		//}

		//string ans;

		//auto find_smallest = [&]() {
		//	int smallest = 26;
		//	for (int i = 0; i < 26; i++) {
		//		if (size(appears[i]) > 1) {
		//			smallest = min(smallest, i);
		//		}
		//	}
		//	};

		//for (;;) {
		//	auto selected_char = find_smallest
		//}


		//return ans;
		vector<int> cnt(26, 0);
		for (char c : s) cnt[c - 'a']++;

		vector<bool> used(26, false);
		string st;

		for (char c : s) {
			int x = c - 'a';
			cnt[x]--;

			if (used[x]) { continue; }

			while (!st.empty()) {
				char t = st.back();
				int y = t - 'a';
				if (t > c && cnt[y] > 0) {
					used[y] = false;
					st.pop_back();
				}
				else {
					break;
				}
			}

			st.push_back(c);
			used[x] = true;
		}

		return st;

	}
};
static void test(string&& s) {
	cout << Solution().lexSmallestAfterDeletion(s) << endl;
}
static void run() {
	test("aaccb");
	test("z");
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