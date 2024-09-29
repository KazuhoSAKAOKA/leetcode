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

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:

    static char get_next(char c) {
        if (c == 'z') {
            return 'a';
        }
        return c + 1;
    }


    static string do_operation(const string& current) {
        string work;
        work.reserve(size(current));
        for (auto&& c : current) {
            work += get_next(c);
        }
        return current + work;
    }


    char kthCharacter(int k) {
        string current = "a";
        while (size(current) < k) {
            current = do_operation(current);
        }
        return current[k - 1];
    }
};

void test(int k) {
    cout << Solution().kthCharacter(k) << endl;
}

void run() {
    test(5);
    test(10);
}
}
namespace problem2 {
class Solution {
public:
    struct info {
        bool a_ = false;
        bool e_ = false;
        bool i_ = false;
        bool o_ = false;
        bool u_ = false;
        size_t consonats_ = 0;

        bool ok_vowles() const {
            return a_ && e_ && i_ && o_ && u_;
        }

    };

    static info create(char c) {
        switch (c) {
        case 'a':
            return info{ true,false,false,false,false, 0 };
        case 'e':
            return info{ false,true,false,false,false, 0 };
        case 'i':
            return info{ false,false,true,false,false, 0 };
        case 'o':
            return info{ false,false,false,true,false, 0 };
        case 'u':
            return info{ false,false,false,false,true, 0 };
        }
        return info{ false,false,false,false,false, 1 };
    }

    static info append(const info& obj, char c) {
        switch (c) {
        case 'a':
            return info{ obj.a_ || true, obj.e_,obj.i_,obj.o_,obj.u_, obj.consonats_ };
        case 'e':
            return info{ obj.a_,obj.e_ || true,obj.i_,obj.o_,obj.u_, obj.consonats_ };
        case 'i':
            return info{ obj.a_,obj.e_,obj.i_ || true,obj.o_,obj.u_, obj.consonats_ };
        case 'o':
            return info{ obj.a_,obj.e_,obj.i_,obj.o_ || true,obj.u_, obj.consonats_ };
        case 'u':
            return info{ obj.a_,obj.e_,obj.i_,obj.o_,obj.u_ || true, obj.consonats_ };
        }
        return info{ obj.a_,obj.e_,obj.i_,obj.o_,obj.u_, obj.consonats_ + 1 };
    }



    int countOfSubstrings(string word, int k) {


        vector<info> before;
        before.emplace_back(create(word[0]));
        int count = 0;
        for (size_t i = 1; i < size(word); i++) {
            vector<info> current{ create(word[i]) };

            for (auto&& curr : before) {
                const auto cur_info = append(curr, word[i]);
                if (cur_info.ok_vowles() && cur_info.consonats_ == k) {
                    count++;
                }
                if (cur_info.consonats_ <= k) {
                    current.emplace_back(cur_info);
                }
            }
            before = current;
        }
        return count;
    }
};
void test(string&& word, int k) {
    cout << Solution().countOfSubstrings(word, k) << endl;
}
void run() {
    test("aeioqq", 1);
    test("aeiou", 0);
    test("ieaouqqieaouqq", 1);
}
}
namespace problem3 {
    class Solution {
    public:
        long long countOfSubstrings(string word, int k) {

            unordered_map<char, size_t> vowels{ {'a', 0}, {'e', 0}, {'i', 0}, {'o', 0}, {'u', 0}, };

            long long count = 0;
            int consonants = 0;
            int vowels_var_counts = 0;
            size_t lv = 0;
            size_t lkl = 0;
            size_t lkr = 0;
            for (size_t r = 0; r < size(word); r++) {
                const auto it = vowels.find(word[r]);
                if (it == end(vowels)) {
                    consonants++;
                }
                else {
                    if (it->second == 0) {
                        vowels_var_counts++;
                    }
                    it->second++;
                }
                if (consonants > k) {
                    while (lkr < r && consonants > k) {
                        const auto it = vowels.find(word[lkr]);
                        if (it == end(vowels)) {
                            consonants--;
                        }
                        lkr++;
                    }
                    lkl = lkr;
                }
                if (consonants == k) {
                    while (lkr < r && vowels.find(word[lkr]) != cend(vowels)) {
                        lkr++;
                    }
                }
                if (vowels_var_counts == 5) {
                    while (lv < r) {
                        const auto it = vowels.find(word[lv]);
                        if (it != cend(vowels)) {
                            if(it->second == 1) {
                                break;
                            }
                            it->second--;
                        }
                        lv++;
                    }
                }
                if (vowels_var_counts == 5 && consonants == k) {
                    if (lkl <= lv) {
                        count += min(lv, lkr) - lkl + 1;
                    }
                }


            }
            return count;

        }
    };
    void test(string&& word, int k) {
        cout << Solution().countOfSubstrings(word, k) << endl;
    }
void run() {
    test("hoiuafoehh", 3);
    test("aeiou", 0);
    test("ieaouqqieaouqq", 1);
    test("aeioqq", 1);
    test("aeueio", 0);
}
}
namespace problem4 {
class Solution {
public:
    static char get_next(char c) {
        if (c == 'z') {
            return 'a';
        }
        return c + 1;
    }
    static string do_operation(const string& current) {
        string work;
        work.reserve(size(current));
        for (auto&& c : current) {
            work += get_next(c);
        }
        return current + work;
    }

    static char solve_naive(long long k, const vector<int>& operations) {
        string current = "a";
        for (auto&& o : operations) {
            if (o == 0) {
                current = current + current;
            }
            else {
                current = do_operation(current);
            }
        }
        return current[k - 1];
    }

    char kthCharacter(long long k, vector<int>& operations) {
        char target = 'a';
        size_t index = 0;
        vector<int> op_indexes;
        long long current = k - 1;
        while (current > 0) {
            if (operations[index] != 0 && current % 2 != 0) {
                target = get_next(target);
                op_indexes.emplace_back(index);
            }
            current /= 2;
            index++;
        }

        //if (solve_naive(k, operations) != target) {
        //    cout << "failed" << endl;
        //}
        return target;
    }
};
void test(long long k, vector<int>&& operations) {
    cout << Solution().kthCharacter(k, operations) << endl;
}
void run() {
    test(1522596, get_list_int("[0,1,1,1,0,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,1,0,1,1]"));
    test(4, get_list_int("[1,1]"));
    test(2, get_list_int("[1]"));
    test(100, get_list_int("[1,1,1,1,1,1,1,1,1]"));
    test(5, get_list_int("[0,0,0]"));
    test(10, get_list_int("[0,1,0,1]"));
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}