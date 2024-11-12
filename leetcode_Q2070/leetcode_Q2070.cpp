// leetcode_Q2070.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

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
class Solution {
public:
	vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
		map<int, int, std::greater<int>> work_map;
		work_map[0] = 0;
		for (auto&& item : items) {
			work_map[item.front()] = max(work_map[item.front()], item.back());
		}

		seqment_tree_range_maximum_query st(size(work_map));
		int index = size(work_map) - 1;
		for (auto&& [k, v] : work_map) {
			st.update(index, v);
			v = index;
			index--;
		}


		vector<int> ans;
		ans.reserve(size(queries));
		for (auto&& query : queries){
			auto it = work_map.lower_bound(query);
			if (it == cend(work_map)) {
				ans.emplace_back(0);
			}
			else {
				auto beauty = st.query(0, it->second + 1);
				ans.emplace_back(beauty);
			}
		}
		return ans;
    }
};

void test(vector<vector<int>>&& items, vector<int>&& queries) {
	output(Solution().maximumBeauty(items, queries));
}
int main()
{
    test(get_matrix_int("[[1,2],[3,2],[2,4],[5,6],[3,5]]"), get_list_int("[1,2,3,4,5,6]"));
    test(get_matrix_int("[[1,2],[1,2],[1,3],[1,4]]"), get_list_int("[1]"));
	test(get_matrix_int("[[10,1000]]"), get_list_int("[5]"));
	return 0;
}