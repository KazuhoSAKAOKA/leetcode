#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> JAMMING_DOTS
{
    {-1, 0, 2, 0, 0, 0, 4, 0, 5, },//1
    { 0,-1, 0, 0, 0, 0, 0, 5, 0, },//2
    { 2, 0,-1, 0, 0, 0, 5, 0, 6, },//3
    { 0, 0, 0,-1, 0, 5, 0, 0, 0, },//4
    { 0, 0, 0, 0,-1, 0, 0, 0, 0, },//5
    { 0, 0, 0, 5, 0,-1, 0, 0, 0, },//6
    { 4, 0, 5, 0, 0, 0,-1, 0, 8, },//7
    { 0, 5, 0, 0, 0, 0, 0,-1, 0, },//8
    { 5, 0, 6, 0, 0, 0, 8, 0, 0, },//9
};

class Solution {
public:

    static bool is_allow(vector<bool>& used, int last, int current) {
        if (last < 0) { return true; }
        const auto dot = JAMMING_DOTS[last][current];
        if (dot == 0) {
            return true;
        }
        if (used[dot - 1]) {
            return true;
        }
        return false;
    }

    static int rec(int m, int n, int index, vector<bool>& used, int last) {
        if (index == n) {
            return 0;
        }

        int count = 0;
        if (m - 1 <= index) {
            for (int i = 0; i < 9; i++) {
                if (!used[i] && is_allow(used, last, i)) {
                    count++;
                }
            }
        }
        for (int i = 0; i < 9; i++) {
            if (!used[i] && is_allow(used, last, i)) {
                used[i] = true;
                count += rec(m, n, index + 1, used, i);
                used[i] = false;
            }
        }
        return count;
    }


    int numberOfPatterns(int m, int n) {
        vector<bool> used(9, false);
        return rec(m, n, 0, used, -1);
    }
};

void test(int m, int n) {
    cout << Solution().numberOfPatterns(m, n) << endl;
}
int main()
{
    test(1, 1);
    test(1, 2);
    return 0;
}