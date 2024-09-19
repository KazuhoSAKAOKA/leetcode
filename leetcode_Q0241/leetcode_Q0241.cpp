// leetcode_Q0241.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "./../utility/leetcode_testcase_helper.h"


using namespace std;

class Solution {
public:
    enum class kind {
        num = 0,
        plus = '+',
        minus = '-',
        multiple = '*',
    };

    struct element {
        kind kind_;
        int value_;
    };

    static int calculate(kind op, int left, int right) {
        switch (op) {
        case kind::plus:
            return left + right;
        case kind::minus:
            return left - right;
        case kind::multiple:
            return left * right;
        }
        throw exception();
    }

    static vector<int> evaluate_part(kind op, const vector<element>& left, const vector<element>& right) {
        const vector<int> left_values = evaluate(left);
        const vector<int> right_values = evaluate(right);
        vector<int> values;
        values.reserve(size(left_values) * size(right_values));
        for (auto&& left_value : left_values) {
            for (auto&& right_value : right_values) {
                values.emplace_back(calculate(op, left_value, right_value));
            }
        }
        return values;
    }
    static vector<int> evaluate(const vector<element>& expression) {
        if (expression.empty() || size(expression) == 2) {
            throw exception();
        }
        if (size(expression) == 1) {
            if (expression.front().kind_ != kind::num) {
                throw exception();
            }
            return { expression.front().value_, };
        }
        vector<int> values;
        size_t index = 1;
        vector<element> left{expression[0]};
        while (index < size(expression) - 1) {
            const kind op = expression[index].kind_;
            vector<element> right;
            copy(next(cbegin(expression), index + 1), cend(expression), back_inserter(right));
            const auto current = evaluate_part(op, left, right);
            values.insert(cend(values), cbegin(current), cend(current));
            left.emplace_back(expression[index]);
            left.emplace_back(expression[index + 1]);
            index += 2;
        }
        return values;
    }

    vector<int> diffWaysToCompute(string expression) {
        vector<element> expression1;
        size_t index = 0;
        const char operator_chars[] = {'+', '-', '*'};
        for(;;) {
            const size_t pos = expression.find_first_of(operator_chars, index, size(operator_chars));
            if (pos == string::npos) {
                int value = stoi(expression.substr(index));
                expression1.emplace_back(element{ kind::num, value, });
                break;
            }
            else {
                int value = stoi(expression.substr(index, pos - index));
                expression1.emplace_back(element{ kind::num, value, });
                expression1.emplace_back(element{ static_cast<kind>(expression[pos]), 0,});
                index = pos + 1;
            }
        }
        const auto ans = evaluate(expression1);
        return ans;
    }
};

void test(string&& expression) {
    output(Solution().diffWaysToCompute(expression));
}

int main()
{
    test("2-1-1");
    test("2*3-4*5");
    return 0;
}