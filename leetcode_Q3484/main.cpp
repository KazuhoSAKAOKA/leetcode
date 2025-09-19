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
class Spreadsheet {
    vector<vector<int>> sheet;

    static pair<int, int> get_axis(const string& cell) {
        return {
            static_cast<int>(cell[0] - 'A'),
            stoi(cell.substr(1)) - 1
        };
    }

    static vector<string> split(const string& s, char c) {
        vector<string> values;
        size_t current = 0;
        while (current < size(s)) {
            const auto pos = s.find(c, current);
            if (pos == string::npos) {
                values.emplace_back(s.substr(current));
                break;
            }
            values.emplace_back(s.substr(current, pos - current));
            current = pos + 1;
        }
        return values;
    }

    int get_value(const string& cell_or_value) {
        if ('0' <= cell_or_value[0] && cell_or_value[0] <= '9') {
            return stoi(cell_or_value);
        }
        else {
            const auto [x, y] = get_axis(cell_or_value);
            return sheet[y][x];
        }
    }

public:
    Spreadsheet(int rows) :sheet(rows, vector<int>(26)){
    }

    void setCell(string cell, int value) {
        const auto [x, y] = get_axis(cell);
        sheet[y][x] = value;
    }

    void resetCell(string cell) {
        const auto [x, y] = get_axis(cell);
        sheet[y][x] = 0;
    }

    int getValue(string formula) {
        const vector<string> vals = split(formula.substr(1), '+');
        return get_value(vals[0]) + get_value(vals[1]);
    }
};

static void test1() {
    Spreadsheet ss(3);
    cout << ss.getValue("=5+7") << endl;
    ss.setCell("A1", 10);
    cout << ss.getValue("=A1+6") << endl;
    ss.setCell("B2", 15);
    cout << ss.getValue("=A1+B2") << endl;
    ss.resetCell("A1");
    cout << ss.getValue("=A1+B2") << endl;
}
static void test2() {
    Spreadsheet ss(458);
    cout << ss.getValue("=O126+10272") << endl;
}

int main() {
    test2();
    return 0;
}