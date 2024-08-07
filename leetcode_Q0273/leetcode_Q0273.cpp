// leetcode_Q0273.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

const unordered_map<int, string> english_map
{
    { 0, "Zero"},
    { 1, "One"},
    { 2, "Two"},
    { 3, "Three"},
    { 4, "Four"},
    { 5, "Five"},
    { 6, "Six"},
    { 7, "Seven"},
    { 8, "Eight"},
    { 9, "Nine"},
    { 10, "Ten"},
    { 11, "Eleven"},
    { 12, "Twelve"},
    { 13, "Thirteen"},
    { 14, "Fourteen"},
    { 15, "Fifteen"},
    { 16, "Sixteen"},
    { 17, "Seventeen"},
    { 18, "Eighteen"},
    { 19, "Nineteen"},
    { 20, "Twenty"},
    { 30, "Thirty"},
    { 40, "Forty"},
    { 50, "Fifty"},
    { 60, "Sixty"},
    { 70, "Seventy"},
    { 80, "Eighty"},
    { 90, "Ninety"},
    { 100, "Hundred"},
    { 1000, "Thousand"},
    { 1000000, "Million"},
    { 1000000000, "Billion"},
};

class Solution {
public:

    static vector<int> conv(int value, int mother) {
        int current = value;
        vector<int> temp;
        while (current > 0) {
            const auto c = current % mother;
            temp.push_back(c);
            current /= mother;
        }
        return vector<int>(crbegin(temp), crend(temp));
    }

    static void append_to(string& ans, const vector<int>& engs, int index) {
        const int& value = engs[index];
        if (value == 0) {
            return;
        }
        const auto digits = conv(value, 10);
        const auto eng_col = engs.size() - index - 1;

        int digit_index = 0;
        if (size(digits) == 3) {
            if (!ans.empty()) {
                ans.append(" ");
            }            ans.append(english_map.at(digits[digit_index]));
            ans.append(" ");
            ans.append(english_map.at(100));
            digit_index++;
        }
        if (size(digits) > 1) {

            if (digits[digit_index] == 1) {
                if (!ans.empty()) {
                    ans.append(" ");
                }
                ans.append(english_map.at(value % 100));
                if (eng_col > 0) {
                    if (!ans.empty()) {
                        ans.append(" ");
                    }
                    ans.append(english_map.at(static_cast<int>(pow(10, eng_col * 3))));
                }
                return;
            }
            else {
                if (digits[digit_index] != 0) {
                    if (!ans.empty()) {
                        ans.append(" ");
                    }
                    ans.append(english_map.at(digits[digit_index] * 10));
                }
                digit_index++;
            }
        }
        if (digits[digit_index] != 0) {
            if (!ans.empty()) {
                ans.append(" ");
            }
            ans.append(english_map.at(digits[digit_index]));
        }

        if (eng_col > 0) {
            if (!ans.empty()) {
                ans.append(" ");
            }
            ans.append(english_map.at(static_cast<int>(pow(10, eng_col * 3))));
        }
    }

    string numberToWords(int num) {
        //edge
        if (num == 0) {
            return english_map.at(0);
        }
        string ans;
        const auto engs = conv(num, 1000);
        for (int i = 0; i< size(engs); i++){
            append_to(ans, engs, i);
        }

        return ans;
    }
};

void test(int num) {
    cout << Solution().numberToWords(num) << endl;
}
int main()
{
    test(123);
    test(12345);
    test(1234567);
    test(1000);
    test(1001);
    return 0;
}