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

struct state_t {
	static vector<int>* s_ptr;
	static const vector<int>& get_nums() {
		return *s_ptr;
	}
	int turn = 0;
	int left = 0;
	int right = 0;
	int my_score = 0;
	int opp_score = 0;

	vector<int> get_legal_actions() const {
		if (left < right) {
			return { 0,1 };
		}
		else {
			return { 0, };
		}
	}

	state_t transit(int action) const {
		state_t ns(*this);
		int score;
		if (action == 0) {
			ns.left++;
			score = get_nums()[left];
		}
		else {
			score = get_nums()[right];
			ns.right--;
		}
		if (turn % 2 == 0) {
			ns.my_score += score;
		}
		else {
			ns.opp_score += score;
		}
		ns.turn++;
		return ns;
	}

	int get_score() const {
		if (turn % 2 == 0) {
			return my_score - opp_score;
		}
		else {
			return opp_score - my_score;
		}
	}

	bool is_done() const {
		return right < left;
	}
};

vector<int>* state_t::s_ptr = nullptr;

class Solution {
public:

	template <typename TState, typename TValue = long long>
	TValue alpha_beta_score(
		const TState& state,
		TValue alpha_score,
		TValue beta_score,
		int depth) {
		if (depth == 0 || state.is_done()) {
			return state.get_score();
		}
		const auto legal_actions = state.get_legal_actions();
		if (legal_actions.empty()) {
			return state.get_score();
		}
		for (auto&& action : legal_actions) {
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

    bool predictTheWinner(vector<int>& nums) {
		state_t::s_ptr = &nums;
		state_t state{
			0,0,static_cast<int>(size(nums))-1,0,0,
		};
		const auto score = alpha_beta_score<state_t, int>(state, INT_MIN / 2, 0, size(nums));

		return score >= 0;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().predictTheWinner(nums) << endl;
}

int main() {
    test(get_list_int("[1,5,2]"));
    test(get_list_int("[1,5,233,7]"));
    return 0;
}
