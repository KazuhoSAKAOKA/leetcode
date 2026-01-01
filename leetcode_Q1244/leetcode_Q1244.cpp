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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Leaderboard {
    map<int, int> player_score_map;
    multiset<int, greater<int>> score_set;
public:
    Leaderboard() {
    }
    
    void addScore(int playerId, int score) {
        auto it = player_score_map.find(playerId);
        if(it == cend(player_score_map)){
            player_score_map.insert({playerId, score});
            score_set.insert(score);
        } else{
            score_set.erase(score_set.find(it->second));
            it->second += score;
            score_set.insert(it->second);
        } 
    }
    
    int top(int K) {
        int topk_scores = 0;
        auto it = cbegin(score_set);
        for(int i = 0; i < K && it != cend(score_set); i++, ++it){
            topk_scores += *it;
        }        
        return topk_scores;
    }
    
    void reset(int playerId) {
        auto it = player_score_map.find(playerId);
        if(it != cend(player_score_map)){
            score_set.erase(score_set.find(it->second));
            player_score_map.erase(it);
        }
    }
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */

static void test(){
    Leaderboard obj;
    obj.addScore(1,17);
    obj.addScore(2,66);
    obj.addScore(3,18);
    obj.addScore(4,37);
    obj.addScore(5,59);
    obj.addScore(6,26);
    obj.addScore(7,22);
    obj.addScore(8,54);
    obj.addScore(9,4);
    obj.addScore(10,40);
    obj.addScore(11,93);
    obj.addScore(12,91);
    obj.addScore(13,10);
    obj.addScore(14,99);
    obj.addScore(15,3);
    obj.addScore(16,18);
    obj.addScore(17,19);
    obj.addScore(18,35);
    obj.addScore(19,61);
    obj.addScore(20,52);
    obj.addScore(21,46);
    obj.addScore(22,70);
    obj.addScore(23,90);
    obj.addScore(24,14);
    obj.addScore(25,60);
    obj.addScore(26,62);
    obj.addScore(27,8);
    obj.addScore(28,89);
    obj.addScore(29,72);
    obj.addScore(30,63);
    obj.addScore(31,61);
    obj.addScore(32,32);
    obj.addScore(33,72);
    obj.addScore(34,19);
    obj.addScore(35,45);
    obj.addScore(36,97);
    obj.addScore(37,12);
    obj.addScore(38,62);
    obj.addScore(39,55);
    obj.addScore(40,98);
    obj.addScore(41,48);
    obj.addScore(42,77);
    obj.addScore(43,91);
    obj.addScore(44,49);
    obj.addScore(45,25);
    obj.addScore(46,8);
    obj.addScore(47,14);
    obj.addScore(48,8);
    obj.addScore(49,89);
    obj.addScore(50,93);
    obj.reset(1);
    obj.addScore(31,91);
    obj.reset(2);
    obj.addScore(44,26);
    obj.addScore(3,60);
    obj.addScore(40,66);
    cout << obj.top(39) << endl;
//    cout << obj.top(18) << endl;
//    cout << obj.top(32) << endl;
}


int main(){
    test();
    return 0;
}