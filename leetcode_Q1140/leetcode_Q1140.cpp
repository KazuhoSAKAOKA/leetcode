// leetcode_Q1140.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
	struct game_state {
		const vector<int>* p_sums;
		int m_;
		int index_;
		int turn_ = 0;
		int alice_score_ = 0;
		int bob_score_ = 0;
		vector<int> get_legal_actions() const {
			vector<int> actions;
			for (int i = 1; i <= min(m_ * 2, static_cast<int>(size(*p_sums) - 1) - index_); i++) {
				actions.push_back(i);
			}
			return actions;
		}
		bool is_done() const {
			return size(*p_sums) - 1 <= index_;
		}
		int get_score() const {
			if (turn_ % 2 == 0) {
				return alice_score_ - bob_score_;
			}
			else {
				return bob_score_ - alice_score_;
			}
		}
		game_state transit(int action) const {
			const auto new_m = max(action, m_);
			const auto new_index = index_ + action;
			const auto score = (*p_sums)[new_index] - (*p_sums)[index_];
			if (turn_ % 2 == 0) {
				return game_state{ p_sums, new_m, new_index, turn_ + 1, alice_score_ + score, bob_score_ };
			}
			else {
				return game_state{ p_sums, new_m, new_index, turn_ + 1, alice_score_, bob_score_ + score };
			}
		}
	};

	using memo_key_t = tuple<int, int, int>;
	using memo_t = map<memo_key_t, int>;

	static int alpha_beta_score(
		const game_state& state,
		int alpha_score,
		int beta_score,
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

	static int alpha_beta(
		const game_state& state,
		int depth,
		memo_t& memo) {

		const auto key = memo_key_t(state.turn_, state.index_, state.m_);
		const auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}

		auto best_action = -1;
		auto alpha_score = std::numeric_limits<int>::min() + 1;
		constexpr auto beta_score = std::numeric_limits<int>::max() - 1;
		const auto legal_actions = state.get_legal_actions();
		for (auto&& action : legal_actions) {
			auto next_state = state.transit(action);
			auto score = -alpha_beta_score(next_state, -beta_score, -alpha_score, depth);
			if (score > alpha_score) {
				best_action = action;
				alpha_score = score;
			}
		}
		memo[key] = best_action;
		return best_action;
	}

	static int use_alpha_beta(const vector<int>& piles) {

		vector<int> sums(size(piles) + 1);
		for (int i = 0; i < size(piles); i++) {
			sums[i + 1] = sums[i] + piles[i];
		}

		game_state init_state{ &sums, 1, 0, 0, 0, 0, };
		game_state current_state(init_state);
		memo_t memo;
		while (!current_state.is_done()) {
			const auto selected_action = alpha_beta(current_state, INT_MAX, memo);
			current_state = current_state.transit(selected_action);
			cout << current_state.turn_ << ":" << "select action=" << selected_action << ",alice=" << current_state.alice_score_ << ",bob=" << current_state.bob_score_ << endl;
		}
		return current_state.alice_score_;
	}

#pragma region model answer
	static int ma_stoneGameII(vector<int>& piles) {
		vector<vector<int>> memo(piles.size(), vector<int>(piles.size()));
		vector<int> suffixSum = piles;
		for (int i = suffixSum.size() - 2; i >= 0; --i)
			suffixSum[i] += suffixSum[i + 1];
		return maxStones(suffixSum, 1, 0, memo);
	}

	static int maxStones(vector<int>& suffixSum, int maxTillNow, int currIndex,
		vector<vector<int>>& memo) {
		if (currIndex + 2 * maxTillNow >= suffixSum.size())
			return suffixSum[currIndex];
		if (memo[currIndex][maxTillNow] > 0) return memo[currIndex][maxTillNow];
		int res = INT_MAX;

		for (int i = 1; i <= 2 * maxTillNow; ++i) {
			res = min(res, maxStones(suffixSum, max(i, maxTillNow),
				currIndex + i, memo));
		}
		memo[currIndex][maxTillNow] = suffixSum[currIndex] - res;
		return memo[currIndex][maxTillNow];
	}
#pragma endregion
	using memo_t2 = vector<vector<int>>;

	void rec(const vector<int>& sums, int index, int m,int& current_score, int& oppnent_score, memo_t2& memo) {
		if (size(sums) - 1 == index) {
			current_score = 0;
			oppnent_score = 0;
			return;
		}

		const auto remain_score = sums.back() - sums[index];
		if (memo[index][m] != 0) {
			current_score = memo[index][m];
			oppnent_score = remain_score - current_score;
			return;
		}
		int max_score = 0;
		int select_case_opp_score = 0;
		for (int i = 1; i <= min(m * 2, static_cast<int>(size(sums)) - index - 1); i++) {
			const int current_get_score = sums[index + i] - sums[index];
			int my_score = 0;
			int oppnent_score = 0;
			rec(sums, index + i, max(i, m), oppnent_score, my_score, memo);
			const int state_score = current_get_score + my_score;
			if (max_score < state_score) {
				max_score = state_score;
				select_case_opp_score = oppnent_score;
			}
			else if (max_score == state_score) {
				cout << "test" << endl;
			}
		}
		memo[index][m] = max_score;
		current_score = max_score;
		oppnent_score = select_case_opp_score;
		return;
	}


    int stoneGameII(vector<int>& piles) {
		if (size(piles) == 1) { return piles.front(); }
		vector<int> sums(size(piles) + 1);
		for (int i = 0; i < size(piles); i++) {
			sums[i + 1] = sums[i] + piles[i];
		}
		memo_t2 memo(size(piles), vector<int>(size(piles)));
		
		int alice_score = 0;
		int bob_score = 0;
		rec(sums, 0, 1, alice_score, bob_score, memo);

		return alice_score;
    }
};

void test(vector<int>&& piles) {
    cout << Solution().stoneGameII(piles) << endl;
}
int main()
{
	test(get_list_int("[1]"));
	test(get_list_int("[8270,7145,575,5156,5126,2905,8793,7817,5532,5726,7071,7730,5200,5369,5763,7148,8287,9449,7567,4850,1385,2135,1737,9511,8065,7063,8023,7729,7084,8407]"));
	test(get_list_int("[2,7,9,4,4]"));
    test(get_list_int("[1,2,3,4,5,100]"));
    return 0;
}