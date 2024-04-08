// leetcode_Q1700.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;


class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        set<int> indexes;
        for (int i = 0; i < students.size(); i++) {
            indexes.insert(i);
        }
        int sandwiches_index = 0;
        bool exist = true;
        while (exist) {
            exist = false;
            for (auto it = begin(indexes); it != end(indexes);) {
                if (students[*it] == sandwiches[sandwiches_index]) {
                    sandwiches_index++;
                    it = indexes.erase(it);
                    exist = true;
                }
                else {
                    ++it;
                }
            }
        }
        return static_cast<int>(indexes.size());
    }
};

void test(vector<int>&& students, vector<int>&& sandwiches) {
    cout << Solution().countStudents(students, sandwiches) << endl;
}

int main()
{
    test({ 1,1,0,0, }, { 0,1,0,1, });
    test({ 1,1,1,0,0,1, }, { 1,0,0,0,1,1, });
}