// leetcode_Q0085.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

class Solution {
public:
    
    static int get_max_area(const vector<vector<int>>& hist, int start_y, int x) {
        int max_area = 0;
        stack<int> st;
        const int base = start_y - 1;
        st.push(base);
        int current_y = start_y;

        while(current_y < hist.size() && hist[current_y][x] != 0) {
            while (st.top() != base && hist[st.top()][x] >= hist[current_y][x]) {
                const auto width = hist[st.top()][x];
                st.pop();
                const auto pos = st.top();
                const auto height = current_y - pos - 1;
                max_area = max(max_area, width * height);
            }
            st.push(current_y);
            current_y++;
        }
        while (st.top() != base) {
            const auto width = hist[st.top()][x];
            st.pop();
            const auto pos = st.top();
            const auto height = current_y - pos - 1;
            max_area = max(max_area, width * height);
        }
        return max_area;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        const auto h = matrix.size();
        const auto w = matrix.front().size();
        vector<vector<int>> hist(h, vector<int>(w, 0));
        for(int i = 0; i< h; i++){
            hist[i][w - 1] = matrix[i][w - 1] == '1' ? 1 : 0;
            for (int j = static_cast<int>(w - 2); j >= 0; j--) {
                hist[i][j] = matrix[i][j] == '1' ? (1 + hist[i][j + 1]) : 0;
            }
        }

        int max_size = 0;

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.front().size(); j++) {
                max_size = max(max_size, get_max_area(hist, i, j));
            }
        }
        return max_size;
    }
    /*
    using rectangle = pair<int, int>;
    using memo_t = unordered_map<rectangle, rectangle>;
    static rectangle get_size(const vector<vector<char>>& matrix, int i, int j, memo_t& memo) {
        if (matrix.size() == i) {
            return 0;
        }
        if (matrix.front().size() == j) {
            return 0;
        }
        const auto key = rectangle(i, j);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        int value = 0;
        if (matrix[i][j] == '1') {
            value 

        }
        memo[key] = value;
        return value;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int max_size = 0;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.front().size(); j++) {
                if (matrix[i][j] == '1') {
                    max_size = max(max_size, 1);
                    for (int k = i + 1; k < matrix.size(); k++) {
                        if (matrix[i][j] != '1') { break; }
                        for (int l = j + 1; j < matrix.front().size(); l++) {
                            if (matrix[i][j] != '1') { break; }
                        }
                    }
                }
            }
        }
        
    }    */

};

void test(vector<vector<char>>&& matrix) {
    cout << Solution().maximalRectangle(matrix) << endl;
}

int main()
{
    test({ {'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'} });
    test({ {'0'} });
    test({ {'1'} });
}