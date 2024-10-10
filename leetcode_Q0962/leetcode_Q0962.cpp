// leetcode_Q0962.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

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
	T get_value_direct(size_t index) const {
		return data_.back()[index];
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
struct seqment_tree_range_minimum_query : public segment_tree<T, std::function<T(T, T)>> {
	seqment_tree_range_minimum_query(size_t n) :segment_tree(n, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
	template <typename Container>
	seqment_tree_range_minimum_query(Container source) : segment_tree(source, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
};
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
		seqment_tree_range_minimum_query<int> segment_tree(static_cast<size_t>(5e5+1));
		int max_ramp = 0;
		for (int i = 0; i < size(nums); i++) {
			const auto before = segment_tree.get_value_direct(nums[i]);
			if (before > i) {
				segment_tree.update(nums[i], i);
			}
			const auto value = segment_tree.query(0, nums[i] + 1);
			if (value < i) {
				max_ramp = max(max_ramp, i - value);
			}
		}
		return max_ramp;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().maxWidthRamp(nums) << endl;
}

int main()
{
    test(get_list_int("[6,0,8,2,1,5]"));
    test(get_list_int("[9,8,1,0,1,9,4,0,4,1]"));
    return 0;
}