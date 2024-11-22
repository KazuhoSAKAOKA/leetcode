// leetcode_Q1072.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <bitset>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    using bits = bitset<300>;
    static bits create_colbits(const vector<vector<int>>& matrix, int col) {
        bits b;
        for (int i = 0; i < size(matrix); i++) {
            if (matrix[i][col] != 0) {
                b.set(i, true);
            }
        }
        return b;
    }

    static int rec(const vector<bits>& cols, int index, const bits& target, bits current_state) {
        if (index == size(cols)) {
            return current_state.count();
        }
        auto current_bits = cols[index];
        bits normal = ~(target ^ current_bits);
        bits normal_state = current_state & normal;
        int count = 0;

        count = max(count, rec(cols, index + 1, target, normal_state));

        current_bits.flip();
        bits flipped = ~(target ^ current_bits);
        bits flipped_state = current_state & flipped;
        count = max(count, rec(cols, index + 1, target, flipped_state));
        return count;
    }

    static int tle(const vector<vector<int>>& matrix) {
        const bits target = create_colbits(matrix, 0);
        vector<bits> cols;
        cols.reserve(size(matrix.front()));
        for (int i = 1; i < size(matrix.front()); i++) {
            cols.emplace_back(create_colbits(matrix, i));
        }
        bits first_state;
        for (int i = 0; i < size(matrix); i++) {
            first_state.set(i, true);
        }
        const auto ans = rec(cols, 0, target, first_state);
        return ans;
    }

    static int rec2(const vector<vector<int>>& matrix, int colindex, const bits& current_state) {
        if (colindex == size(matrix.front())) {
            return current_state.count();
        }
        int count = 0;

        bits no_flip(current_state);
        for (int i = 0; i < size(matrix); i++) {
            if (current_state.test(i)) {
                if (matrix[i][0] != matrix[i][colindex]) {
                    no_flip.reset(i);
                }
            }
        }
        count = max(count, rec2(matrix, colindex + 1, no_flip));
        bits flipped(current_state);
        for (int i = 0; i < size(matrix); i++) {
            if (current_state.test(i)) {
                if (matrix[i][0] == matrix[i][colindex]) {
                    flipped.reset(i);
                }
            }
        }
        count = max(count, rec2(matrix, colindex + 1, flipped));
        return count;
    }

    static int tle2(const vector<vector<int>>& matrix) {
        bits first_state;
        for (int i = 0; i < size(matrix); i++) {
            first_state.set(i, true);
        }
        const auto ans = rec2(matrix, 1, first_state);
        return ans;
    }
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        unordered_map<string, int> freq_map;

        for (auto&& current_row : matrix) {
            string p;
            for (int col = 0; col < size(current_row); col++) {
                if (current_row[0] == current_row[col]) {
                    p += '1';
                }
                else {
                    p += '0';
                }
            }
            freq_map[p]++;
        }

        int max_freq = 0;
        for (auto&& [key, freq] : freq_map) {
            max_freq = max(max_freq, freq);
        }
        return max_freq;
    }
};

void test(vector<vector<int>>&& matrix) {
    cout << Solution().maxEqualRowsAfterFlips(matrix) << endl;
}
int main()
{
    test(get_matrix_int("[[1,0,0,0,1,1,1,0,1,1,1],[1,0,0,0,1,0,0,0,1,0,0],[1,0,0,0,1,1,1,0,1,1,1],[1,0,0,0,1,0,0,0,1,0,0],[1,1,1,0,1,1,1,0,1,1,1]]"));
    test(get_matrix_int("[[0,1],[1,1]]"));
    test(get_matrix_int("[[0,1],[1,0]]"));
    test(get_matrix_int("[[0,0,0],[0,0,1],[1,1,0]]"));
    return 0;
}