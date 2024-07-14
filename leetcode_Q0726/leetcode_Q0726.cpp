// leetcode_Q0726.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Solution {
public:

    static pair<int, int> get_multiple(const string& formula, int index) {
        if (formula.size() <= index) {
            return { 1, index };
        }
        int len = 0;
        while ((index + len) < formula.size() && isdigit(formula[index + len])) {
            len++;
        }
        if (len == 0) {
            return { 1, index };
        }
        const auto temp = formula.substr(index, len);
        const int multiple = stoi(temp);
        return { multiple, index + len };
    }

    static pair<string, int> get_atom(const string& formula, int index) {
        if (formula.size() <= index) {
            cerr << "expected alphabets";
            throw exception();
        }
        if (!isupper(formula[index])) {
            cerr << "expected upper case";
            throw exception();
        }
        int len = 1;
        while ((index + len) < formula.size() && islower(formula[index + len])) {
            len++;
        }
        const auto temp = formula.substr(index, len);
        return { temp, index + len };
    }

    static pair<map<string, int>, int> rec(const string& formula, int index) {
        if (formula.size() <= index) {
            return { map<string, int>(), index };
        }

        map<string, int> ret_map;
        int current_index = index;
        while (current_index < formula.size()) {
            if (formula[current_index] == '(') {
                const auto [child_map, ret_index] = rec(formula, current_index + 1);
                current_index = ret_index;
                const auto [multiple, ret_index2] = get_multiple(formula, current_index);
                current_index = ret_index2;
                for (auto&& [atom, count] : child_map) {
                    ret_map[atom] += count * multiple;
                }
            }
            else if (formula[current_index] == ')') {
                current_index++;
                break;
            }
            else if (isalpha(formula[current_index])) {
                const auto [atom, ret_index] = get_atom(formula, current_index);
                current_index = ret_index;
                const auto [count, ret_index2] = get_multiple(formula, current_index);
                current_index = ret_index2;
                ret_map[atom] += count;
            }
            else {
                cerr << "unexpected.";
                throw exception();
            }
        }

        return { ret_map, current_index };
    }


    string countOfAtoms(string formula) {
        const auto [freq_map,_] = rec(formula, 0);

        string ans;
        for (auto&& [atom, count] : freq_map) {
            ans.append(atom);
            if (count > 1) {
                ans.append(to_string(count));
            }
        }
        return ans;
    }
};

void test(string&& formula) {
    cout << Solution().countOfAtoms(formula) << endl;
}
int main()
{
    test("H2O");
    test("Mg(OH)2");
    test("K4(ON(SO3)2)2");
    return 0;
}