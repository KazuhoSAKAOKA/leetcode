#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

using point_t = pair<long long, long long>;

static inline point_t operator +(const point_t& p1, const point_t& p2) {
    return point_t{ p1.first + p2.first, p1.second + p2.second };
}
static inline point_t operator -(const point_t& p1, const point_t& p2) {
    return point_t{ p1.first - p2.first, p1.second - p2.second, };
}
static inline point_t operator * (const point_t& p, long long scaler) {
    return point_t{ p.first * scaler, p.second * scaler, };
}

const vector<point_t> dirs{
    {0,1},{1,0},{0,-1},{-1,0},
};

const vector<string> dir_name{
    "East","North","West","South",
};

class Robot {
    point_t rectangle_;
    int dir_ = 0;
    point_t current_;

    long long get_distance_to_wall() const {
        switch (dir_) {
        case 0:
            return rectangle_.second - current_.second - 1;
        case 1:
            return rectangle_.first - current_.first - 1;
        case 2:
            return current_.second;
        case 3:
            return current_.first;
        }
        throw runtime_error("failed.");
    }

public:
    Robot(int width, int height) : rectangle_(height, width), current_(0,0){
    }

    void step(int num) {
        auto remain_steps = static_cast<long long>(num) % (2LL * (rectangle_.first + rectangle_.second - 2LL));
        if (num > 0 && remain_steps == 0 && current_ == point_t{ 0, 0 }) {
            dir_ = 3;
            return;
        }
        while (remain_steps > 0) {
            const auto dist = get_distance_to_wall();
            if (dist < remain_steps) {
                remain_steps -= dist;
                current_ = current_ + (dirs[dir_] * dist);
                dir_++;
                dir_ %= 4;
            }
            else {
                current_ = current_ + (dirs[dir_] * remain_steps);
                remain_steps = 0;
            }
        }
    }

    vector<int> getPos() {
        return { static_cast<int>(current_.second), static_cast<int>(current_.first) };
    }

    string getDir() {
        return dir_name[dir_];
    }
};


static void test1() {
    Robot r(6, 3);
    r.step(2);
    r.step(2);
    output(r.getPos());
    cout << r.getDir() << endl;
    r.step(2);
    r.step(1);
    r.step(4);
    output(r.getPos());
    cout << r.getDir() << endl;
}
static void test2() {
    Robot r(8, 11);
    r.step(18);
    output(r.getPos());
    cout << r.getDir() << endl;
    r.step(24);
    output(r.getPos());
    cout << r.getDir() << endl;
    r.step(44);
    r.step(36);
    output(r.getPos());
    cout << r.getDir() << endl;
}
static void test3() {
    Robot r(5, 6);
    r.step(4);
    output(r.getPos());
    cout << r.getDir() << endl;
    r.step(5);
    output(r.getPos());
    cout << r.getDir() << endl;
    r.step(4);
    output(r.getPos());
    cout << r.getDir() << endl;
    r.step(5);
    output(r.getPos());
    cout << r.getDir() << endl;
}
static void test4() {
    Robot r(97, 98);
    output(r.getPos());
    cout << r.getDir() << endl;
    r.step(66392);
    r.step(83376);
    r.step(71796);
    r.step(57514);
    r.step(36284);
    r.step(69866);
    r.step(31652);
    r.step(32038);
    output(r.getPos());
    cout << r.getDir() << endl;
}

int main() {
    test4();
    return 0;
}