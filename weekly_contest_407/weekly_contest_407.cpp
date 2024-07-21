// weekly_contest_407.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"


using namespace std;

namespace problem1 {
class Solution {
public:
    int minChanges(int n, int k) {
        int count = 0;
        for (int i = 0; i < 32; i++) {
            const int b = 1 << i;

            const auto nb = n & b;
            const auto kb = k & b;
            if (nb == kb) {
                continue;
            }
            if (nb == 0 && kb != 0) {
                return -1;
            }
            count++;
        }
        return count;
    }
};
void test(int n, int k) {
    cout << Solution().minChanges(n, k) << endl;
}
void run() {
    test(13, 4);
    test(21, 21);
    test(14, 13);
}
}
namespace problem2 {

class Solution {
public:

	struct state_t {
		int turn_;
		vector<int> splited_;

		struct action {
			int index_;
			int offset_;
			int length_;
		};

		vector<action> legal_acitons_;

		state_t(const vector<int>& source, int turn) : splited_(source), turn_(turn){
			bool odd = turn % 2 == 0;
			for (int index = 0; index < source.size(); index++) {
				int temp = odd ? 1 : 2;
				while (temp <= source[index]) {
					for (int j = 0; j + temp <= source[index]; j++) {
						legal_acitons_.push_back({ index, j, temp });
					}
					temp += 2;
				}
			}
		}


		bool is_done() const {
			if (legal_acitons_.empty()) {
				return true;
			}
			return false;
		}
		int get_score()const {
			if (is_done()) {
				return -1;
			}
			return 1;
		}
		
		int get_legal_actions() const {
			return legal_acitons_.size();
		}

		state_t transit(int index) const {
			vector<int> next;
			const auto action = legal_acitons_[index];
			for (int i = 0; i < splited_.size(); i++) {
				if (i == action.index_) {
					if (action.length_ == splited_[i]) {
						continue;
					}
					if (action.offset_ == 0) {
						next.push_back(splited_[i] - action.length_);
					}
					else {
						next.push_back(action.offset_);
						const auto remain = splited_[i] - action.offset_ - action.length_;
						if (remain > 0) {
							next.push_back(remain);
						}
					}
				}
				else {
					next.push_back(splited_[i]);
				}
			}
			return state_t(next, turn_ + 1);
		}

	};

	int alpha_beta_score(
		const state_t& state,
		int alpha_score,
		int beta_score,
		int depth) {
		if (depth == 0 || state.is_done()) {
			return state.get_score();
		}
		const auto legal_actions = state.get_legal_actions();
		if (legal_actions == 0) {
			return state.get_score();
		}
		for (int action = 0; action < legal_actions; action++) {
			auto next_state = state.transit(action);
			auto score = -alpha_beta_score(next_state, -beta_score, -alpha_score, depth - 1);
			if (score > alpha_score) {
				alpha_score = score;
			}
			if (alpha_score >= beta_score) {
				return alpha_score;
			}
		}
		return alpha_score;
	}

	int alpha_beta(
		const state_t& state,
		int depth) {
		auto alpha_score = -100;
		constexpr auto beta_score = +100;
		const auto legal_actions = state.get_legal_actions();
		if (legal_actions == 0) {
			return -1;
		}
		for (int action = 0; action < legal_actions; action++) {
			auto next_state = state.transit(action);
			auto score = -alpha_beta_score(next_state, -beta_score, -alpha_score, depth);
			if (score > alpha_score) {
				alpha_score = score;
			}
		}
		return alpha_score;
	}

	static bool is_voel(char c) {
		switch (c) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			return true;
		}
		return false;
	}

    bool doesAliceWin(string s) {
		int length = 0;
		for (auto&& c : s) {
			if (is_voel(c)) {
				length++;
			}
		}

		state_t state(vector<int>{length}, 0);
		
		const int b = alpha_beta(state, 100000);
		
		if (b > 0) {
			return true;
		}
		else {
			return false;
		}
    }
};

void test(string&& s) {
    cout << Solution().doesAliceWin(s) << endl;
}

void run() {
    test("leetcoder");
	test("a");
	test("aaaa");
    test("bbcd");
}
}
namespace problem3 {

class Solution {
public:
	int maxOperations(string s) {
		int op_count = 0;
		int one_count = 0;
		bool zero_continue = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '1') {
				one_count++;
				zero_continue = false;
			}
			else {
				if (!zero_continue) {
					op_count += one_count;
					zero_continue = true;
				}
			}
		}

		return op_count;
	}
};

void test(string&& s) {
	cout << Solution().maxOperations(s) << endl;
}

void run() {
	test("110");
	test("10101");

	test("1001101");
	test("00111");
}
}
namespace problem4 {

class Solution {
public:
	long long minimumOperations(vector<int>& nums, vector<int>& target) {
		vector<int> diffs(nums.size());
		for (int i = 0; i < nums.size(); i++) {
			diffs[i] = target[i] - nums[i];
		}

		long long op_count = 0;
		bool exist = true;
		while (exist) {
			exist = false;
			int series_len = 0;
			int absolute_min = 0;
			bool positive = false;

			auto counting = [&](int index) {
				if (series_len == 0) {
					return;
					}
				op_count += static_cast<long long>(absolute_min);
				const int inc = positive ? -absolute_min : absolute_min;
				for (int j = 0; j < series_len; j++) {
					diffs[index - 1 - j] += inc;
				}
				};


			for (int i = 0; i < nums.size(); i++) {
				if (diffs[i] == 0) {
					counting(i);
					series_len = 0;
					continue;
				}
				exist = true;
				if (series_len == 0) {
					series_len++;
					positive = diffs[i] > 0;
					absolute_min = abs(diffs[i]);
					continue;
				}

				const auto current_positive = diffs[i] > 0;
				if (current_positive == positive) {
					series_len++;
					absolute_min = min(absolute_min, abs(diffs[i]));
					continue;
				}
				counting(i);
				positive = current_positive;
				absolute_min = abs(diffs[i]);
				series_len = 1;
			}
			counting(diffs.size());
		}

		return op_count;
	}
};

void test(vector<int>&& nums, vector<int>&& target) {
	cout << Solution().minimumOperations(nums, target) << endl;
}

void run() {
	test(get_list_int("[9,2,6,10,4,8,3,4,2,3]"), get_list_int("[9,5,5,1,7,9,8,7,6,5]"));
	test(get_list_int("[1,1,3,4]"), get_list_int("[4,1,3,2]"));
	test(get_list_int("[3,5,1,2]"), get_list_int("[4,6,2,4]"));
	test(get_list_int("[1,3,2]"), get_list_int("[2,1,4]"));
}
}


int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
}