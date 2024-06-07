// leetcode_Q0648.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    struct trie_tree {
        struct node {
            bool teminate_ = false;
            std::map<char, node> nodes_;
        };
        node root_;

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
            current->teminate_ = true;
        }

        pair<string, size_t> find(const std::string& s, int offset) {
            node* current = &root_;
            for (size_t i = 0; i + offset < s.size(); i++) {
                const char c = s[i + offset];
                if (c == ' ') {
                    return make_pair(s.substr(offset, i), offset + i + 1);
                }

                const auto it = current->nodes_.find(c);
                if (it != cend(current->nodes_)) {
                    current = &(it->second);
                    if (current->teminate_) {
                        size_t index = i;
                        while (index + offset < s.size() && s[offset + index] != ' ') {
                            index++;
                        }
                        return make_pair(s.substr(offset, i + 1), offset + index + 1);
                    }
                }
                else {
                    size_t index = i;
                    while (index + offset < s.size() && s[offset + index] != ' ') {
                        index++;
                    }
                    return make_pair(s.substr(offset, index), offset + index + 1);
                }
            }
            return make_pair(s.substr(offset, s.size() - offset), s.size());
        }
    };

    string replaceWords(vector<string>& dictionary, string sentence) {
        trie_tree trie;
        for (auto&& s : dictionary) {
            trie.add(s);
        }

        string ans;
        size_t index = 0;
        while (index < sentence.size()) {
            const auto [word, next_p] = trie.find(sentence, index);
            ans.append(word);
            if (next_p < sentence.size()) {
                ans.append(1, ' ');
            }
            index = next_p;
        }
        return ans;
    }
};

void test(vector<string>&& dictionary, string&& sentence) {
    cout << Solution().replaceWords(dictionary, sentence) << endl;
}


int main()
{
    test(get_list_str(R"(["a", "aa", "aaa", "aaaa"])"), "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa");
    test(get_list_str(R"(["cat","cate"])"), "ca category");
    test(get_list_str(R"(["cat","bat","rat"])"), "the cattle was rattled by the battery");
    test(get_list_str(R"(["a","b","c"])"), "aadsfasf absbs bbab cadsfafs");
}