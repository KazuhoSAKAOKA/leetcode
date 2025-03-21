#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_set<string> supplies_set(cbegin(supplies), cend(supplies));
        set<int> indexes;
        for (int i = 0; i < size(recipes); i++) {
            indexes.insert(i);
        }
        
        vector<string> ans;

        bool changed = true;
        while (changed) {
            changed = false;
            for (auto it = begin(indexes); it != end(indexes);) {
                const auto i = *it;
                if (all_of(cbegin(ingredients[i]), cend(ingredients[i]), [&](const string& ingredient)->bool { return supplies_set.find(ingredient) != cend(supplies_set); })) {
                    ans.emplace_back(recipes[i]);
                    it = indexes.erase(it);
                    changed = true;
                    supplies_set.insert(recipes[i]);
                }
                else {
                    ++it;
                }
            }
        }
        return ans;
    }
};

void test(vector<string>&& recipes, vector<vector<string>>&& ingredients, vector<string>&& supplies) {
    output(Solution().findAllRecipes(recipes, ingredients, supplies));
}
int main() {
    test(get_list_str(R"(["bread"])"), get_matrix_str(R"([["yeast","flour"]])"), get_list_str(R"(["yeast","flour","corn"])"));
    test(get_list_str(R"(["bread","sandwich"])"), get_matrix_str(R"([["yeast","flour"],["bread","meat"]])"), get_list_str(R"(["yeast","flour","meat"])"));
    test(get_list_str(R"(["bread","sandwich","burger"])"), get_matrix_str(R"([["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]])"), get_list_str(R"(["yeast","flour","meat"])"));
    return 0;
}