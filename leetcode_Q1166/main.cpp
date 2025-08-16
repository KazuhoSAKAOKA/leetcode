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
#include <sstream>
using namespace std;
class FileSystem {
    static vector<string> split(const string& s, char delimiter) {
		vector<string> tokens;
		stringstream ss(s);
		string item;
		while (std::getline(ss, item, delimiter)) {
			if (!item.empty()) {
				tokens.emplace_back(item);
			}
		}
		return tokens;
    }

	struct trie_tree {
		struct node {
			size_t key_ = 0;
			std::unordered_map<string, node*> nodes_;
		};
		node root_;

		bool add(const std::string& s, int key) {
			const auto lines = split(s, '/');
			if (lines.empty()) { return false; }
			node* current = &root_;
			for (size_t i = 0; i < size(lines) - 1; i++) {
				const auto& line = lines[i];
				const auto it = current->nodes_.find(line);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					return false;
				}
			}
			auto [itnew, ret] = current->nodes_.insert(std::make_pair(lines.back(), new node()));
			if (!ret) { return false; }
			current = (itnew->second);
			current->key_ = key;
			return true;
		}

		int get(const std::string& s) const {
			const auto lines = split(s, '/');
			const node* current = &root_;
			for (auto&& line : lines) {
				const auto it = current->nodes_.find(line);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					return -1;
				}
			}
			return current->key_;
		}

	};
	trie_tree tt;
public:
    FileSystem() {

    }

    bool createPath(string path, int value) {
		return tt.add(path, value);
    }

    int get(string path) {
		return tt.get(path);
    }
};

//[[],["/leet",1],["/leet/code",2],["/leet/code"],["/leet/code",3],["/leet/code"]]
int main() {
	FileSystem fs;
	cout << fs.createPath(R"(/leet)", 1) << endl;
	cout << fs.createPath(R"(/leet/code)", 2) << endl;
	cout << fs.createPath(R"(/leet/code)", 3) << endl;
	cout << fs.get(R"(/leet/code)") << endl;
	cout << fs.createPath(R"(/c/d)", 1) << endl;
	cout << fs.get(R"(/c)") << endl;
	return 0;
}