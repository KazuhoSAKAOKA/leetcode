// weekly_contest_384.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

namespace problem1{

class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {
        vector<vector<int>> ans(matrix);

        for (int i = 0; i < matrix.front().size(); i++) {
            vector<int> targets;
            int max_value = -1;
            for (int j = 0; j < matrix.size(); j++) {
                if (matrix[j][i] == -1) {
                    targets.emplace_back(j);
                }
                else {
                    max_value = max(max_value, matrix[j][i]);
                }
            }
            for (auto&& index : targets) {
				ans[index][i] = max_value;
			}
        }
        return ans;
    }
};

void test(vector<vector<int>>&& matrix){
    const auto ans = Solution().modifiedMatrix(matrix);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}


void run() {
    test({ {1,2,-1},{4,-1,6},{7,8,9} });
    test({ {3,-1},{5,2} });
}

}


namespace problem2{
class Solution {
public:

    static bool is_match_pattern(const vector<int>& nums, int index, const vector<int>& pattern) {
        for (int k = 0; k < pattern.size(); k++) {
            switch (pattern[k])
            {
            case 1:
                if (!(nums[index + k + 1] > nums[index + k])) {
                    return false;
                }
                break;
            case 0:
                if (!(nums[index + k + 1] == nums[index + k])) {
                    return false;
                }
                break;
            case -1:
                if (!(nums[index + k + 1] < nums[index + k])) {
                    return false;
                }
                break;

            default:
                break;
            }
        }
        return true;
    }

    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        int count = 0;

        for (auto i = 0; i < nums.size() - pattern.size(); i++) {
            if (is_match_pattern(nums, i, pattern)) {
				count++;
			}
        }
        return count;
    }
};

void test(vector<int>&& nums, vector<int>&& pattern) {
    cout << Solution().countMatchingSubarrays(nums, pattern) << endl;
}

void run() {
    test({ 1,2,3,4,5,6 }, { 1,1 });
    test({ 1,4,4,1,3,5,5,3 }, { 1,0,-1 });
}

}


namespace problem3 {

class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        map<char, size_t> char_count_map;
        vector<size_t> word_length_list;
        for (auto&& word : words) {
            word_length_list.emplace_back(word.size());
            for (auto&& c : word) {
                char_count_map[c]++;
            }
		}

        size_t odd_count = 0;
        size_t pair_count = 0;
        for (auto& [_, count] : char_count_map) {
            if (count % 2 == 1) {
				odd_count++;
			}
            pair_count += count / 2;
		}
        sort(begin(word_length_list), end(word_length_list));

        size_t count = 0;
        for (auto& word_length : word_length_list) {
            size_t required_pair_size = word_length / 2;
            if (pair_count < required_pair_size) { break; }

            if (word_length % 2 == 1) {
                if (odd_count == 0) {
                    if (pair_count < required_pair_size + 1) {
                        continue;
                    }
                    pair_count--;
                    odd_count = 1;
                }
                else {
                    odd_count--;
                }
            }
            pair_count -= required_pair_size;
            count++;
        }

        return static_cast<int>(count);
    }
};

void test(vector<string>&& words) {
    cout << Solution().maxPalindromesAfterOperations(words) << endl;
}

void run() {
    test({"bwma", "a"});
    test({ "a","a","caa"});
    test({ "abbb","ba","aa" });
    test({ "abc","ab" });
    test({ "cd","ef","a" });
}


}

int main()
{
//    problem1::run();
//    problem2::run();
    problem3::run();

}

