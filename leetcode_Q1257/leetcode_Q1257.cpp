// leetcode_Q1257.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    struct node {
        string region_name_;
        map<string, shared_ptr<node>> childs_;
    };

    static void build_node_rec(node& current_node, const map<string, shared_ptr<node>> node_map) {
        for (auto&& [name, item] : current_node.childs_) {
            auto it = node_map.find(name);
            if (it != cend(node_map)) {
                item = it->second;
                build_node_rec(*item, node_map);
            }
        }
    }

    static shared_ptr<node> build_node(const vector<vector<string>>& regions) {

        set<string> candidates;
        for (auto&& region : regions) {
            candidates.insert(region.front());
        }

        map<string, shared_ptr<node>> node_map;
        for (auto&& region : regions) {
            const auto& parent = region.front();
            auto cur_node = make_shared<node>();
            cur_node->region_name_ = parent;
            for (int i = 1; i < size(region); i++) {
                candidates.erase(region[i]);
                cur_node->childs_.insert(make_pair(region[i], nullptr));
            }
            node_map.insert(make_pair(parent, cur_node));
        }

        auto dummy_root_node = make_shared<node>();

        for (auto&& region : candidates) {
            dummy_root_node->childs_.insert(make_pair(region, node_map[region]));
        }
        for (auto&& [name, cur_node] : dummy_root_node->childs_) {
            build_node_rec(*cur_node, node_map);
        }

        return dummy_root_node;
    }

    static pair<bool, bool> find_region(const pair<string, shared_ptr<node>>& cur_pair, const string& region1, const string& region2, string& ans) {
        bool region1_detected = cur_pair.first == region1;
        bool region2_detected = cur_pair.first == region2;
        if (cur_pair.second != nullptr) {
            for (auto&& child_pair : cur_pair.second->childs_) {
                auto [ret1, ret2] = find_region(child_pair, region1, region2, ans);
                if (ret1 && ret2) {
                    //if (ans.empty()) {
                    //    ans = cur_node->region_name_;
                    //}
                    return { true,true };
                }
                region1_detected |= ret1;
                region2_detected |= ret2;
                if (region1_detected && region2_detected) {
                    ans = cur_pair.first;
                    return { true,true };
                }
            }
        }
        return {region1_detected, region2_detected};
    }

    static string tle(vector<vector<string>>& regions, string region1, string region2) {
        auto root = build_node(regions);
        string ans;
        find_region(make_pair("", root), region1, region2, ans);
        return ans;
    }


    static pair<bool, bool> find_region(const map<string, vector<string>>& region_map, const string& current_region, const string& region1, const string& region2, string& ans) {
        const auto it = region_map.find(current_region);
        bool region1_detected = current_region == region1;
        bool region2_detected = current_region == region2;
        if (it != cend(region_map)) {
            for (auto&& child_region : it->second) {
                auto [ret1, ret2] = find_region(region_map, child_region, region1, region2, ans);
                if (ret1 && ret2) {
                    return { true,true };
                }
                region1_detected |= ret1;
                region2_detected |= ret2;
                if (region1_detected && region2_detected) {
                    ans = current_region;
                    return { true,true };
                }
            }
        }
        return { region1_detected, region2_detected };
    }


    string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {
        set<string> region_groups;
        map<string, vector<string>> regions_map;
        for (auto&& region : regions) {
            region_groups.insert(region.front());
        }
        for (auto&& region : regions) {
            vector<string> childs;
            for (int i = 1; i < size(region); i++) {
                region_groups.erase(region[i]);
                childs.emplace_back(region[i]);
            }
            regions_map.insert({ region.front(), childs });
        }
        const string root_name = "dummy_root";
        regions_map.insert({ root_name, vector<string>(cbegin(region_groups), cend(region_groups)) });
        string ans;

        find_region(regions_map, root_name, region1, region2, ans);

        return ans;
    }
};

void test(vector<vector<string>>&& regions, string&& region1, string&& region2) {
    cout << Solution().findSmallestRegion(regions, region1, region2) << endl;
}
int main()
{
    test(get_matrix_str(R"([["Earth","North America","South America"],["North America","United States","Canada"],["United States","New York","Boston"],["Canada","Ontario","Quebec"],["South America","Brazil"]])"), "Quebec", "New York");
    test(get_matrix_str(R"([["Earth","North America","South America"],["North America","United States","Canada"],["United States","New York","Boston"],["Canada","Ontario","Quebec"],["South America","Brazil"]])"),"Canada","South America");
    return 0;
}