// leetcode_Q1062.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:

    static int tle(const string& s) {
        unordered_set<string> allofs;
        unordered_set<string> befores;
        size_t max_len = 0;

        befores.insert(string(1, s[0]));
        allofs.insert(string(1, s[0]));
        for (int i = 1; i < size(s); i++) {
            unordered_set<string> currents;
            auto update = [&](const string& sub) {
                const auto it = allofs.find(sub);
                if (it != cend(allofs)) {
                    max_len = max(max_len, size(sub));
                }
                else {
                    allofs.insert(sub);
                }
                currents.insert(sub);
                };
            update(string(1, s[i]));
            for (auto&& item : befores) {
                auto current_substr = item + s[i];
                update(current_substr);
            }
            swap(befores, currents);
        }

        return static_cast<int>(max_len);
    }

    static void make_substrings(const string& s, int index, unordered_set<string>& substrings, int& max_length) {

        for (int l = 1; l < size(s) - index + 1; l++) {
            const auto temp = s.substr(index, l);
            if (substrings.find(temp) == cend(substrings)) {
                substrings.insert(temp);
            }
            else {
                max_length = max(max_length, static_cast<int>(size(temp)));
            }
        }
    }

    static int slow(const string& s) {
        int max_length = 0;
        unordered_set<string> substrings;
        for (int i = 0; i < size(s); i++) {
            make_substrings(s, i, substrings, max_length);
        }
        return max_length;
    }

    struct trie_tree {
        struct node {
            std::unordered_map<char, node*> nodes_;
        };
        node root_;

        int add(const std::string& s, int offset) {
            node* current = &root_;
            int max_len = 0;
            for (int i = offset; i < s.size(); i++) {
                const auto it = current->nodes_.find(s[i]);
                if (it != cend(current->nodes_)) {
                    max_len++;
                    current = (it->second);
                }
                else {
                    auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
                    current = (itnew->second);
                }
            }
            return max_len;
        }

    };

    static int use_trie(const string& s) {
        trie_tree trie;
        int max_len = 0;
        for (int i = 0; i < size(s); i++) {
            max_len = max(max_len, trie.add(s, i));
        }
        return max_len;
    }

    int longestRepeatingSubstring(string s) {
        return use_trie(s);
    }
};

void test(string&& s) {
    cout << Solution().longestRepeatingSubstring(s) << endl;
}
int main()
{
    test("abcd");
    test("abbaba");
    test("aabcaabdaab");
    return 0;
}