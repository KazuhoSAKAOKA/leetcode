// leetcode_Q0030.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    static void create_permutation(const vector<string>& words, size_t index, vector<bool>& used, string& current, unordered_set<string>& permutations) {
        if (words.size() == index) {
            permutations.insert(current);
            return;
        }

        for (size_t i = 0; i < words.size(); i++) {
            if (!used[i]) {
                used[i] = true;
                string temp = current + words[i];
                create_permutation(words, index + 1, used, temp, permutations);
                used[i] = false;
            }
        }
    }

    static vector<int> brute_force(const string& s, const vector<string>& words) {
        unordered_set<string> permutations;
        string working;
        vector<bool> used(words.size(), false);

        create_permutation(words, 0, used, working, permutations);

        vector<int> ans;
        const auto sub_str_len = words.size() * words.front().size();
        if (sub_str_len <= s.size()) {
            for (int i = 0; i < s.size() - sub_str_len + 1; i++) {
                const auto temp = s.substr(i, sub_str_len);
                if (permutations.find(temp) != cend(permutations)) {
                    ans.emplace_back(i);
                }
            }
        }
        return ans;
    }


    struct trie_tree {
        struct node {
            size_t arrive_count_ = 0;
            size_t checked_count_ = 0;
            unordered_map<char, node> nodes_;
        };
        node root_;
        unordered_set<node*> leaves_;

        void add(const std::string& s) {
            node* current = &root_;
            for (int i = 0; i < s.size(); i++) {
                const auto it = current->nodes_.find(s[i]);
                if (it != cend(current->nodes_)) {
                    current = &(it->second);
                } 
                else {
                    auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], node()));
                    current = &(itnew->second);
                }
            }
            current->arrive_count_++;
            leaves_.insert(current);
        }
        void clear_check() {
            for (auto&& leaf : leaves_) {
                leaf->checked_count_ = 0;
            }
        }

        bool check(const string& s, size_t offset, size_t len) {
            node* current = &root_;
            for (int i = 0; i < len; i++) {
                const auto it = current->nodes_.find(s[i + offset]);
                if (it == cend(current->nodes_)) {
                    return false;
                }
                current = &(it->second);
            }
            if (current->checked_count_ < current->arrive_count_) {
                current->checked_count_++;
                return true;
            }
            return false;
        }

    };

    vector<int> findSubstring(string s, vector<string>& words) {

        trie_tree trie;
        for (int i = 0; i < words.size(); i++) {
            trie.add(words[i]);
        }

        vector<int> ans;
        const auto word_size = words.front().size();
        const auto sub_str_len = words.size() * word_size;
        if (sub_str_len <= s.size()) {
            for (int i = 0; i < s.size() - sub_str_len + 1; i++) {
                trie.clear_check();
                auto check = [&]() {
                    for (int j = 0; j < words.size(); j++) {
                        if (!trie.check(s, i + j * word_size, word_size)) {
                            return false;
                        }
                    }
                    return true;
                    };
                if (check()) {
                    ans.emplace_back(i);
                }
            }
        }
        return ans;

    }
};



void test(string&& s, vector<string>&& words) {
    const auto ans = Solution().findSubstring(s, words);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

const string exapmle_1 = R"(["foo", "bar"])";
const string exapmle_2 = R"(["word","good","best","word"])";
const string exapmle_3 = R"(["bar","foo","the"])";


const string my_1 = R"(["abc","def","ghi"])";

int main()
{
    test("barfoothefoobarman", get_list_str(exapmle_1));
    test("wordgoodgoodgoodbestword", get_list_str(exapmle_2));
    test("barfoofoobarthefoobarman", get_list_str(exapmle_3));
    test("abcdefghi", get_list_str(my_1));
    test("abcdefgh", get_list_str(my_1));
}

