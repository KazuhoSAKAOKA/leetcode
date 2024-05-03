// leetcode_Q0165.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:

    static pair<int, size_t> get_version(const string& value, size_t offset) {
        if (value.size() <= offset) {
            return make_pair(0, offset);
        }
        const auto pos = value.find_first_of('.', offset);

        string s;
        if (pos == string::npos) {
            s = value.substr(offset);
        }
        else {
            s = value.substr(offset, pos - offset);
        }
        return make_pair(std::stoi(s), min(value.size(), pos));
    }


    int compareVersion(string version1, string version2) {
        size_t index1 = 0;
        size_t index2 = 0;
        for (;;) {
            const auto [part_1, offset1] = get_version(version1, index1);
            const auto [part_2, offset2] = get_version(version2, index2);

            if (part_1 != part_2) {
                return part_1 < part_2 ? -1 : 0;
            }
            if (version1.size()<= offset1 && version2.size() <= offset2) {
                break;
            }
            index1 = offset1 + 1;
            index2 = offset2 + 1;
        }
        return 0;
    }
};

void test(string&& version1, string&& version2) {
    cout << Solution().compareVersion(version1, version2) << endl;
}

int main()
{
    test("1.01", "1.001");
    test("1.0", "1.0.0");
    test("0.1", "1.1");
    test("1.1", "0.1");

    test("1.2.3.4.5.6", "1.00002.00003.00004.0005.00006");
    test("1.2.3.4.5.6", "1.00002.00003.00004.0005.00007");

}