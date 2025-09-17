#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
class FoodRatings {
    map<string, map<int, set<string>, greater<int>>> forward_map;
    map<string, pair<int, string>> reverse_map;

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        const auto n = size(foods);
        for (int i = 0; i < n; i++) {
            const auto& food = foods[i];
            const auto& cuisine = cuisines[i];
            const auto& rating = ratings[i];
            forward_map[cuisine][rating].insert(food);
            reverse_map[food] = { rating, cuisine };
        }
    }

    void changeRating(string food, int newRating) {
        auto it = reverse_map.find(food);
        if (it == cend(reverse_map)) {
            return;
        }
        const auto rating = it->second.first;
        const auto& cuisine = it->second.second;
        auto it2 = forward_map.find(cuisine);
        auto& inner_map = it2->second;
        auto it3 = inner_map.find(rating);
        it3->second.erase(food);
        if (it3->second.empty()) {
            inner_map.erase(it3);
        }
        inner_map[newRating].insert(food);
        it->second.first = newRating;
    }

    string highestRated(string cuisine) {
        auto it = forward_map.find(cuisine);
        if (it == cend(forward_map)) {
            return "";
        }
        const auto& [_, items] = *cbegin(it->second);
        return *cbegin(items);
    }
};

int main() {
	return 0;
}