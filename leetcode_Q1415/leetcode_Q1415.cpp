#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const vector<char> happys{ 'a','b','c' };
class Solution {
public:

    static bool rec(int n, int k, string& current, int& current_count, string& ans) {
        if (size(current) == n) {
            current_count++;
            if (k == current_count) {
                ans = current;
                return true;
            }
            else {
                return false;
            }
        }

        for (auto&& c : happys) {
            if (current.empty()) {
                current += c;
            }
            else {
                if (c == current.back()) {
                    continue;
                }
                current += c;
            }
            if (rec(n, k, current, current_count, ans)) {
                return true;
            }
            current.pop_back();
        }
        return false;
    }


    string getHappyString(int n, int k) {
        string current;
        string ans;
        int current_count = 0;
        rec(n, k, current, current_count, ans);
        return ans;
    }
};

void test(int n, int k) {
    cout << Solution().getHappyString(n, k) << endl;
}
int main()
{
    test(1, 3);
    test(1, 4);
    test(3, 9);
    return 0;
}