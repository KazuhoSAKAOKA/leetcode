#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int numberOfWays(string corridor) {
        constexpr long long MODULO = 1e9 + 7;
        vector<long long> border_candidates;
        enum class state_t {
            seats,
            plants,
        };
        state_t cur_state = state_t::seats;
        bool exist_seats = false;
        int current_seats = 0;
        int plant_streak = 0;
        for (auto&& c : corridor) {
            if (c == 'P') {
                if (cur_state == state_t::plants) {
                    plant_streak++;
                }
            }
            else {
                if (cur_state == state_t::seats) {
                    current_seats++;
                    if (current_seats == 2) {
                        current_seats = 0;
                        plant_streak = 0;
                        cur_state = state_t::plants;
                        exist_seats = true;
                    }
                }
                else {
                    if (plant_streak > 0) {
                        border_candidates.emplace_back(plant_streak);

                    }
                    current_seats = 1;
                    plant_streak = 0;
                    cur_state = state_t::seats;
                }
            }
        }
        if (cur_state == state_t::seats && current_seats > 0 || !exist_seats) {
            return 0;
        }


        long long ans = 1;

        for (auto&& b : border_candidates) {
            ans *= b + 1;
            ans %= MODULO;
        }
        return static_cast<long long>(ans);
    }
};

static void test(string&& corridor) {
    cout << Solution().numberOfWays(corridor) << endl;
}

int main()
{
    test("P");
    test("SSPPSPS");
    test("PPSPSP");
    test("S");
    return 0;
}