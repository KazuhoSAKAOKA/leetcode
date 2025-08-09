#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
using namespace std;
class Solution {
public:

    static double mle(int n) {
        double ans = 0;

        queue<tuple<double, int, int>> q;
        q.push({ 1.0, n,n });

        while (!q.empty()) {
            auto [r, a, b] = q.front();
            q.pop();
            const double t = r * 0.25;
            if (a <= 25) {
                if (b <= 75) {
                    ans += t / 2;
                }
                else {
                    ans += t;
                }
            }
            else {
                if (b > 75) {
                    q.push({ t,a - 25,b - 75 });
                }
            }

            if (a <= 50) {
                if (b <= 50) {
                    ans += t / 2;
                }
                else {
                    ans += t;
                }
            }
            else {
                if (b > 50) {
                    q.push({ t, a - 50, b - 50 });
                }
            }

            if (a <= 75) {
                if (b <= 25) {
                    ans += t / 2;
                }
                else {
                    ans += t;
                }
            }
            else {
                if (b > 25) {
                    q.push({ t, a - 75, b - 25 });
                }
            }

            if (a <= 100) {
                if (b <= 0) {
                    ans += t / 2;
                }
                else {
                    ans += t;
                }
            }
            else {
                q.push({ t,a - 100, b });
            }
        }
        return ans;
    }
    double soupServings(int n) {
        if (n > 5000) {
            return 1.0;
        }
        map<pair<int, int>, double> before{ {{n,n},1.0 }, };
        double ans = 0.0;
        while (!before.empty()) {
            map<pair<int, int>, double> current;
            for (auto&& [k, r] : before) {
                const auto [a, b] = k;
                const double t = r * 0.25;
                if (a <= 25) {
                    if (b <= 75) {
                        ans += t / 2;
                    }
                    else {
                        ans += t;
                    }
                }
                else {
                    if (b > 75) {
                        current[{a - 25, b - 75 }] += t;
                    }
                }

                if (a <= 50) {
                    if (b <= 50) {
                        ans += t / 2;
                    }
                    else {
                        ans += t;
                    }
                }
                else {
                    if (b > 50) {
                        current[{a - 50, b - 50}] += t;
                    }
                }

                if (a <= 75) {
                    if (b <= 25) {
                        ans += t / 2;
                    }
                    else {
                        ans += t;
                    }
                }
                else {
                    if (b > 25) {
                        current[{a - 75, b - 25}] += t;
                    }
                }

                if (a <= 100) {
                    if (b <= 0) {
                        ans += t / 2;
                    }
                    else {
                        ans += t;
                    }
                }
                else {
                    current[{a - 100, b}] += t;
                }

            }
            swap(current, before);

        }
        return ans;
    }
};
static void test(int n) {
    cout << Solution().soupServings(n) << endl;
}
int main() {
    test(4800);
    test(75);
    test(0);
    test(50);
    test(100);
	return 0;
}