#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class MovieRentingSystem {
    using PRICE = int;
    using SHOP = int;
    using MOVIE = int;
    map<pair<SHOP, MOVIE>, PRICE> shop_movie_to_price_map;

    map<MOVIE, map<PRICE, set<SHOP>>> active_movie_price_shop_map;

    map<PRICE, map<SHOP, set<MOVIE>>> rented_price_shop_movies_map;
public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {

        for (auto&& entry : entries) {
            const auto& shop = entry[0];
            const auto& movie = entry[1];
            const auto& price = entry[2];

            active_movie_price_shop_map[movie][price].insert(shop);
            shop_movie_to_price_map[{shop, movie}] = price;
        }
    }

    vector<int> search(int movie) {
        vector<int> movies;
        auto movie_it = active_movie_price_shop_map.find(movie);
        if (movie_it != cend(active_movie_price_shop_map)) {
            const auto& price_movies_map = movie_it->second;
            auto it = cbegin(price_movies_map);
            while (size(movies) < 5 && it != cend(price_movies_map)) {
                const auto& movies_set = it->second;
                auto inner_it = cbegin(movies_set);
                while (size(movies) < 5 && inner_it != cend(movies_set)) {
                    movies.emplace_back(*inner_it);
                    ++inner_it;
                }
                ++it;
            }
        }
        return movies;
    }

    void rent(int shop, int movie) {
        const auto price = shop_movie_to_price_map[{shop, movie}];
        active_movie_price_shop_map[movie][price].erase(shop);
        rented_price_shop_movies_map[price][shop].insert(movie);
    }

    void drop(int shop, int movie) {
        const auto price = shop_movie_to_price_map[{shop, movie}];
        active_movie_price_shop_map[movie][price].insert(shop);
        rented_price_shop_movies_map[price][shop].erase(movie);
    }

    vector<vector<int>> report() {
        vector<vector<int>> shop_movies;
        auto it = cbegin(rented_price_shop_movies_map);
        while (size(shop_movies) < 5 && it != cend(rented_price_shop_movies_map)) {
            const auto& price_movies_map = it->second;
            auto inner_it = cbegin(price_movies_map);
            while (size(shop_movies) < 5 && inner_it != cend(price_movies_map)) {
                const auto& movies = inner_it->second;
                const auto shop = inner_it->first;
                auto movie_it = cbegin(movies);
                while (size(shop_movies) < 5 && movie_it != cend(movies)) {
                    shop_movies.emplace_back(vector<int>{ shop, *movie_it });
                    ++movie_it;
                }
                ++inner_it;
            }
            ++it;
        }

        return shop_movies;
    }
};

static void test1() {
    //[[10,],[],[],[4,7100],[],[],[],[],[4,7100]]
    auto temp = get_matrix_int("[[0,418,3],[9,5144,46],[2,8986,29],[6,1446,28],[3,8215,97],[7,9105,34],[6,9105,30],[5,1722,94],[9,528,40],[3,850,77],[3,7069,40],[8,1997,42],[0,8215,28],[7,4050,80],[4,7100,97],[4,9686,32],[4,2566,93],[2,8320,12],[2,5495,56]]");
    MovieRentingSystem mrs(10, temp);
    output(mrs.search(7837));
    output(mrs.search(5495));
    mrs.rent(4, 7100);
    output(mrs.search(9105));
    output(mrs.search(1446));
    output_matrix(mrs.report());
    output(mrs.search(9869));
    mrs.drop(4, 7100);
}


int main() {
    test1();
	return 0;
}