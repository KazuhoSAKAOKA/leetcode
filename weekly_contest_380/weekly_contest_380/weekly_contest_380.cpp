// weekly_contest_380.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    int maxFrequencyElements(vector<int>& nums) {
        map<int, int> map;
        int max_freq = 0;

        for (int i = 0; i < nums.size(); i++) {
            map[nums[i]]++;
            max_freq = max(max_freq, map[nums[i]]);
        }
        int total_freq = 0;
        for (auto&& pair : map) {
            if (pair.second == max_freq) {
                total_freq += pair.second;
            }
        }

        return total_freq;
    }
};

void test1(vector<int>&& nums) {
    cout << Solution1().maxFrequencyElements(nums) << endl;
}

void run1() {
    test1({ 1,2,2,3,1,4 });
    test1({ 1,2,3,4,5 });
}

class Solution2 {
public:

    static bool equalsubstr(const string& s, const string& target, int n) {
        if (s.size() < n + target.size()) { return false; }
        string sub = s.substr(n, target.size());
        return sub.compare(target) == 0;
    }

    static bool isBeafutiful(const string& s, const string& a, const string& b, int k, int i) {
        if (i < 0 || (s.size() - a.size()) < i) { return false; }
        if (!equalsubstr(s, a, i)) { return false; }
        if (b.size() < s.size()) {
            for (int j = 0; j <= s.size() - b.size(); j++) {
                if (abs(i - j) <= k) {
                    if (equalsubstr(s, b, j)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }


    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> ans;
        if (a.size() < s.size()) {
            for (int i = 0; i <= (s.size() - a.size()); i++) {
                if (isBeafutiful(s, a, b, k, i)) {
                    ans.emplace_back(i);
                }
            }
        }
        return ans;
    }
};

void test2(string&& s, string&& a, string&& b, int k) {
    const auto ans = Solution2().beautifulIndices(s, a, b, k);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

void run2(){
    test2("bavgoc", "ba", "c", 6);


    test2("lahhnlwx", "hhnlw", "ty", 6);

    test2("wl", "xljigt", "wl", 2);

    test2("isawsquirrelnearmysquirrelhouseohmy", "my", "squirrel", 15);
    test2("abcd", "a", "a", 4);
}


class Solution3 {
public:
    long long findMaximumNumber(long long k, int x) {

    }
};


void test3(long long k, int x) {
    cout << Solution3().findMaximumNumber(k, x) << endl;
}

void run3() {
    test3(9, 1);
    test3(7, 2);
}

int main()
{
    run3();
}
