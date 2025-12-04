#include <iostream>
#include <string>

using namespace std;
class Solution {
public:
    int countCollisions(string directions) {
        enum class left_state {
            none,
            stay,
            move_to_right,
        };
        int moving_count = 0;
        left_state state = left_state::none;

        int total_count = 0;

        for (auto&& c : directions) {
            if (c == 'L') {
                if (state == left_state::none) {

                }
                else if (state == left_state::stay) {
                    total_count++;
                }
                else {
                    total_count += 2;
                    total_count += (moving_count - 1);
                    moving_count = 0;
                    state = left_state::stay;
                }
            }
            else if (c == 'R') {
                if (state == left_state::none) {
                    moving_count = 1;
                    state = left_state::move_to_right;
                }
                else if (state == left_state::stay) {
                    moving_count = 1;
                    state = left_state::move_to_right;
                }
                else {
                    moving_count++;
                }
            }
            else {
                if (state == left_state::none) {
                    state = left_state::stay;
                }
                else if (state == left_state::stay) {
                }
                else {
                    total_count += moving_count;
                    moving_count = 0;
                    state = left_state::stay;
                }
            }
        }

        return total_count;
    }
};

static void test(string&& directions) {
    cout << Solution().countCollisions(directions) << endl;
}

int main()
{
    test("RLRSLL");
    test("LLRR");
    return 0;
}