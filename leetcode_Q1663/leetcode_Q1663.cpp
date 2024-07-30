// leetcode_Q1663.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <optional>
#include <functional>
using namespace std;

class Solution {
public:

    static bool check(const string& s) {
        const auto first_b = s.find_first_of('b');
        if (first_b == string::npos) { return true; }
        const auto last_a = s.find_last_of('a');
        if (last_a == string::npos) { return true; }
        return last_a < first_b;
    }

    static int rec(const string& s, int index, string& current, vector<unordered_map<string,int>>& memo) {
        if (s.size() == index) {
            if (check(current)) {
                return 0;
            }
            else {
                return INT_MAX - size(s);
            }
        }
        const auto it = memo[index].find(current);
        if (it != cend(memo[index])) {
            return it->second;
        }
        int min_value = INT_MAX;
        min_value = min(min_value, rec(s, index + 1, current, memo) + 1);
        current += s[index];
        min_value = min(min_value, rec(s, index + 1, current, memo));
        current.pop_back();
        memo[index][current] = min_value;
        return min_value;
    }

    static int tle(const string& s) {
        string work;
        vector<unordered_map<string, int>> memo(s.size());
        return rec(s, 0, work,memo);
    }


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
		void build(IT begin, IT end, function<int(char)> get_val) {
			size_t index = 0;
			for (auto it = begin; it != end; ++it) {
				data_[data_.size() - 1][index++] = get_val(*it);
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

	template <typename T = int>
	struct seqment_tree_sum_query : public segment_tree<T, std::function<T(T, T)>> {
		seqment_tree_sum_query(size_t n) :segment_tree(n, [](T a, T b) {return a + b; }, 0) {}
		template <typename Container>
		seqment_tree_sum_query(Container source) : segment_tree(source, [](T a, T b) {return a + b; }, 0) {}
	};



    int minimumDeletions(string s) {
		/*
        vector<int> before_bs(s.size());
        vector<int> after_as(s.size());

        int count_a = 0;
        int count_b = 0;
        for (int i = 0; i < s.size(); i++) {
            before_bs[i] = count_b;
            after_as[s.size() - i - 1] = count_a;
            if (s[i] == 'b') {
                count_b++;
            }
            if (s[s.size() - i - 1] == 'a') {
                count_a++;
            }
        }
		seqment_tree_sum_query<> st_a(s.size());
		seqment_tree_sum_query<> st_b(s.size());
		st_a.build(cbegin(s), cend(s), [](char c) { return c == 'a' ? 1 : 0; });
		st_b.build(cbegin(s), cend(s), [](char c) { return c == 'b' ? 1 : 0; });
		*/

		vector<vector<int>> dp(s.size(), vector<int>(2));
		if (s[0] == 'a') {
			dp[0][0] = 0;
			dp[0][1] = 1;
		}
		else {
			dp[0][0] = 1;
			dp[0][1] = 0;
		}
		for (int i = 1; i < s.size(); i++) {
			if (s[i] == 'a') {
				dp[i][0] = dp[i - 1][0];
				dp[i][1] = min(dp[i - 1][0], dp[i - 1][1] + 1);
			}
			else {
				dp[i][0] = dp[i - 1][0] + 1;
				dp[i][1] = min(dp[i - 1][0], dp[i-1][1]);
			}
		}

        return min(dp[s.size()-1][0], dp[s.size() - 1][1]);
    }
};

void test(string&& s) {
    cout << Solution().minimumDeletions(s) << endl;
}

int main()
{
    test("ababaaaabbbbbaaababbbbbbaaabbaababbabbbbaabbbbaabbabbabaabbbababaa");
    test("aababbab");
    test("bbaaaaabb");
    return 0;
}
