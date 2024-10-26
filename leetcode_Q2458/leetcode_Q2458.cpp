// leetcode_Q2458.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <queue>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

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

    static int bfs(const TreeNode* root, int ignore) {
        queue<pair<const TreeNode*, int>> q;
        q.push({ root, 0 });
        int last_depth = 0;

        while (!q.empty()) {
            const auto [current, depth] = q.front();
            q.pop();
            if (current->val != ignore) {
                last_depth = depth;
                if (current->left != nullptr) {
                    q.push({current->left, depth+1});
                }
                if (current->right != nullptr) {
                    q.push({ current->right, depth + 1 });
                }
            }
        }
        return last_depth;
    }

    static vector<int> tle(TreeNode* root, vector<int>& queries) {
        vector<int> ans;
        ans.reserve(size(queries));
        for (auto&& ignore : queries) {
            ans.emplace_back(bfs(root, ignore));
        }
        return ans;
    }

    static void dfs(const TreeNode* node, int depth, vector<int>& depthlist,unordered_map<int,pair<int,int>>& num_map) {
        if (node == nullptr) {
            return;
        }
        const int begin_index = size(depthlist);
        depthlist.emplace_back(depth);

        dfs(node->left, depth + 1, depthlist, num_map);
        dfs(node->right, depth + 1, depthlist, num_map);

        const int end_index = size(depthlist);
        depthlist.emplace_back(depth);
        num_map[node->val] = { begin_index, end_index };
    }
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        vector<int> depthlist;
        unordered_map<int, pair<int, int>> num_map;
        dfs(root, 0, depthlist, num_map);

		seqment_tree_range_maximum_query<int> st(depthlist);

        vector<int> ans;
        ans.reserve(size(queries));
        for (auto&& ignore : queries) {
			const auto [l, r] = num_map[ignore];
			int max_depth = 0;
			if (l > 0) {
				max_depth = max(max_depth, st.query(0, l));
			}
			if (r < size(depthlist) - 1) {
				max_depth = max(max_depth, st.query(r + 1, size(depthlist)));
			}
            ans.emplace_back(max_depth);
        }
        return ans;
    }
};

void test(vector<optional<int>>&& values, vector<int>&& queries) {
    output(Solution().treeQueries(create_treenode2(values), queries));
}
int main()
{
    test(get_list_optional_int("[1,3,4,2,null,6,5,null,null,null,null,null,7]"), get_list_int("[4]"));
    test(get_list_optional_int("[5,8,9,2,1,3,7,4,6]"), get_list_int("[3,2,4,8]"));
    return 0;
}