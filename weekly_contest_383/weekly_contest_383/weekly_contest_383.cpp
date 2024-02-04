// weekly_contest_383.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include <map>

using namespace std;


namespace problem1 {

class Solution {
public:
    int returnToBoundaryCount(vector<int>& nums) {
        int position = nums[0];
        int count = 0;
        for (int i = 1; i < nums.size(); i++) {
            position += nums[i];
            if (position == 0) { count++; }
        }
        return count;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().returnToBoundaryCount(nums) << endl;
}

void run() {
    test({ 2,3,-5 });
    test({ 3,2,-3,-4 });
//    test({});
//    test({});
}
}

namespace problem2 {

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int count = 1;

        while (count * k < word.size()) {
            const int current_offset = count * k;
            const auto substr1 = word.substr(current_offset, word.size() - current_offset);
            const auto substr2 = word.substr(0, word.size() - current_offset);
            if (substr1 == substr2) {
                break;
            }

            count++;
        }

        return count;
    }
};

void test(string&& word, int k) {
    cout << Solution().minimumTimeToInitialState(word, k) << endl;
}

void run() {
    test("abacaba", 3);
    test("abacaba", 4);
    test("abcbabcd", 2);
    test("aaaaab", 5);
}
}


namespace problem3 {

class Solution {
public:
    static bool is_valid(const vector<vector<int>>& image, int threshold, int v_index, int h_index) {
        return
            (abs(image[v_index + 0][h_index + 0] - image[v_index + 1][h_index + 0]) <= threshold) &&
            (abs(image[v_index + 0][h_index + 0] - image[v_index + 0][h_index + 1]) <= threshold) &&
            (abs(image[v_index + 1][h_index + 0] - image[v_index + 2][h_index + 0]) <= threshold) &&
            (abs(image[v_index + 1][h_index + 0] - image[v_index + 1][h_index + 1]) <= threshold) &&
            (abs(image[v_index + 2][h_index + 0] - image[v_index + 2][h_index + 1]) <= threshold) &&
            (abs(image[v_index + 0][h_index + 1] - image[v_index + 1][h_index + 1]) <= threshold) &&
            (abs(image[v_index + 0][h_index + 1] - image[v_index + 0][h_index + 2]) <= threshold) &&
            (abs(image[v_index + 1][h_index + 1] - image[v_index + 2][h_index + 1]) <= threshold) &&
            (abs(image[v_index + 1][h_index + 1] - image[v_index + 1][h_index + 2]) <= threshold) &&
            (abs(image[v_index + 2][h_index + 1] - image[v_index + 2][h_index + 2]) <= threshold) &&
            (abs(image[v_index + 0][h_index + 2] - image[v_index + 1][h_index + 2]) <= threshold) &&
            (abs(image[v_index + 1][h_index + 2] - image[v_index + 2][h_index + 2]) <= threshold)
            ;
    }

    int get_average(const vector<vector<int>>& sums, int v_index, int h_index) {
        const int large_i = v_index + 3;
        const int large_j = h_index + 3;
        const int small_i = v_index;
        const int small_j = h_index;
        const auto total = sums[large_i][large_j] + sums[small_i][h_index] - sums[large_i][h_index] - sums[small_i][large_j];
        return total / 9;
    }

    int get_subgrid_avg(const map<int, map<int, int>>& subgrids, const vector<vector<int>>& image,  int i, int j) {
        int total = 0;
        int count = 0;
        
        const int starti = max(0, i - 2);

        const int startj = max(0, j - 2);

        for (int ii = starti; ii <= i; ii++) {
            auto it1 = subgrids.find(ii);
            if (it1 != cend(subgrids)) {
                for (int jj = startj; jj <= j; jj++) {
                    auto it2 = it1->second.find(jj);
                    if (it2 != cend(it1->second)) {
                        count++;
                        total += it2->second;
                    }
                }
            }
        }

        if (count == 0) { return image[i][j]; }
        return total / count;
    }


    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        const size_t height = image.size();
        const size_t width = image.front().size();

        vector<vector<int>> sums(height + 1, vector<int>(width + 1, 0));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                sums[i + 1][j + 1] = sums[i + 1][j] + image[i][j];
            }
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                sums[i + 1][j + 1] += sums[i][j + 1];
            }
        }
        map<int, map<int, int>> subgrids;
        for (int i = 0; i <= height - 3; i++) {
            for (int j = 0; j <= width - 3; j++) {
                if (is_valid(image, threshold, i, j)) {
                    subgrids[i][j] = get_average(sums, i, j);
                }
            }
        }

        vector<vector<int>> ans(height, vector<int>(width, 0));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                ans[i][j] = get_subgrid_avg(subgrids, image, i, j);
            }
        }

        return ans;
    }
};

void test(vector<vector<int>>&& image, int threshold) {
    const auto ans = Solution().resultGrid(image, threshold);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}

void run() {
    test({ {5,6,7,10 }, { 8,9,10,10 }, { 11,12,13,10 }}, 3);
    test({ {10,20,30},{15,25,35},{20,30,40},{25,35,45} }, 12);
    test({ {5,6,7, }, { 8,9,10, }, { 11,12,13, } }, 1);
}
}
int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
}
