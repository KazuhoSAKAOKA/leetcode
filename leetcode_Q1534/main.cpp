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
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int count = 0;
        const auto n = size(arr);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                const auto diffa = abs(arr[i] - arr[j]);
                if (diffa <= a) {
                    for (int k = j + 1; k < n; k++) {
                        const auto diffb = abs(arr[j] - arr[k]);
                        const auto diffc = abs(arr[i] - arr[k]);
                        if (diffb <= b && diffc <= c) {
                            count++;
                        }
                    }
                }
            }
        }
       
        return count;
    }
};
int main() {
	return 0;
}