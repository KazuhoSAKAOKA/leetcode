// leetcode_Q0592.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
T gcd(const T& a, const T& b) {
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

template <typename T>
T lcm(const T& a, const T& b) {
    return a / gcd(a, b) * b;
}


class Solution {
public:
    struct fraction {
        int numerator_;
        int denominator_;

        fraction operator+(const fraction& v) const {
            const auto new_denominator = lcm(abs(denominator_), abs(v.denominator_));
            return {
                numerator_ * (new_denominator / denominator_) + v.numerator_ * (new_denominator / v.denominator_),
                new_denominator,
            };
        }

        fraction reduction() const {
            const auto p = gcd(abs(numerator_), abs(denominator_));
            return {
                numerator_ / p,
                denominator_ / p,
            };
        }
        string to_string() const {
            return std::to_string(numerator_) + "/" + std::to_string(denominator_);
        }
    };
    static fraction parse(const string& expression, size_t& index) {
        int signed_val = 1;
        auto current_index = index;
        if (expression[current_index] == '-') {
            current_index++;
            signed_val = -1;
        }
        else if (expression[current_index] == '+') {
            current_index++;
        }
        const auto num_ptr = expression.find('/', current_index);
        if (num_ptr == string::npos) {
            cerr << "invalid data" << endl;
            throw 0;
        }
        const auto num_str = expression.substr(current_index, num_ptr - current_index);
        const auto numerator = stoi(num_str);
        current_index = num_ptr + 1;
        static const char spliters[] = { '-','+' };
        const auto den_ptr = expression.find_first_of(spliters, current_index, size(spliters));
        const auto den_str = den_ptr == string::npos ? expression.substr(current_index) : expression.substr(current_index, den_ptr - current_index);
        const auto denominator = stoi(den_str);
        if (denominator == 0) {
            cerr << "invalid denominator" << endl;
            throw 0;
        }
        index = den_ptr;
        return {
            signed_val * numerator,
            denominator,
        };
    }

    string fractionAddition(string expression) {
        size_t index = 0;
        fraction current = parse(expression, index);

        while (index != string::npos) {
            auto f2 = parse(expression, index);
            current = current + f2;
        }
        const auto ans = current.reduction();
        return ans.to_string();
    }
};
void test(string&& expression) {
    cout << Solution().fractionAddition(expression) << endl;
}

int main()
{
    test("1/3-1/2");
    test("-1/2+1/2");
    test("-1/2+1/2+1/3");
    return 0;
}