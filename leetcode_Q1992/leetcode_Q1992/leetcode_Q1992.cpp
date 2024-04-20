// leetcode_Q1992.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static vector<int> find_area(const vector<vector<int>>& land, int i, int j, vector<vector<bool>>& checked) {
        int l = j + 1;
        while (l < land.front().size()) {
            if (land[i][l] == 0) {
                break;
            }
            l++;
        }
        int k = i + 1;
        while (k < land.size()) {
            if (land[k][j] == 0) {
                break;
            }
            k++;
        }

        for (int m = i; m < k; m++) {
            for (int n = j; n < l; n++) {
                checked[m][n] = true;
            }
        }
        return { i,j,k - 1,l - 1, };

    }

    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        vector<vector<int>> ans;
        vector<vector<bool>> checked(land.size(), vector<bool>(land.front().size(), false));

        for (int i = 0; i < land.size(); i++) {
            for (int j = 0; j < land.front().size(); j++) {
                if (checked[i][j]) { continue; }
                if (land[i][j] == 1) {
                    ans.emplace_back(find_area(land, i, j, checked));
                }
            }
        }
        return ans;
    }
};

void test(vector<vector<int>>&& land) {
    const auto ans = Solution().findFarmland(land);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
    cout << "------" << endl;
}

int main()
{
    test({ {1,1,}, {0,0,} });
    test({ {1,0,0,},{0,1,1, },{0,1,1,} });
    test({ {1,1, },{1,1,} });
    test({ {0,} });
}
