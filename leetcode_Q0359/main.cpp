#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_set>
using namespace std;
class Logger {
private:
    map<int, unordered_set<string>> exists_;


public:
    Logger() {

    }

    bool shouldPrintMessage(int timestamp, string message) {
        const int limit = timestamp - 10;
        auto it = begin(exists_);
        while (it != end(exists_) && it->first <= limit) {
            it = exists_.erase(it);
        }

        while (it != end(exists_)) {
            if (it->second.find(message) != end(it->second)) {
                return false;
            }
            ++it;
        }
        exists_[timestamp].insert(message);
        return true;
    }
};

int main() {
	return 0;
}