// leetcode_Q0860.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int fives = 0;
        int tens = 0;
        for (auto&& bill : bills) {
            switch (bill) {
            case 5:
                fives++;
                break;
            case 10:
                if (fives == 0) {
                    return false;
                }
                fives--;
                tens++;
                break;
            case 20:
                if (fives == 0) {
                    return false;
                }
                if (tens == 0) {
                    if (fives >= 3) {
                        fives -= 3;
                        break;
                    }
                    return false;
                }
                fives--;
                tens--;
                break;
            default:
                break;

            }
        }
        return true;
    }
};

void test(vector<int>&& bills) {
    cout << Solution().lemonadeChange(bills) << endl;
}
int main()
{
    test(get_list_int("[5,5,5,5,20,20,5,5,20,5]"));
    test(get_list_int("[5,5,10,20,5,5,5,5,5,5,5,5,5,10,5,5,20,5,20,5]"));
    test(get_list_int("[5,5,5,10,20]"));
    test(get_list_int("[5,5,10,10,20]"));
    return 0;
}