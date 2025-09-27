#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
class Solution {
public:

    static double cal_area(const vector<int>& A, const vector<int>& B, const vector<int>& C) {
        return abs((B[0] - A[0]) * (C[1] - A[1]) - (C[0] - A[0]) * (B[1] - A[1])) / 2.0;
    }

    double largestTriangleArea(vector<vector<int>>& points) {
        double max_area = 0;
        for (int i = 0; i < size(points); i++) {
            for (int j = i + 1; j < size(points); j++) {
                for (int k = j + 1; k < size(points); k++) {
                    max_area = max(max_area, cal_area(points[i], points[j], points[k]));
                }
            }
        }
        return max_area;
    }
};

int main() {
	return 0;
}