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
class Bank {
    vector<long long> balance_;
public:
    Bank(vector<long long>& balance) :balance_(balance){
    }

    bool transfer(int account1, int account2, long long money) {
        if (!(1 <= account1 && account1 <= size(balance_) && 1 <= account2 && account2 <= size(balance_))) {
            return false;
        }
        if (balance_[account1 - 1] < money) {
            return false;
        }
        balance_[account2 - 1] += money;
        balance_[account1 - 1] -= money;
        return true;
    }

    bool deposit(int account, long long money) {
        if (!(1 <= account && account <= size(balance_))) {
            return false;
        }
        balance_[account - 1] += money;
        return true;
    }

    bool withdraw(int account, long long money) {
        if (!(1 <= account && account <= size(balance_))) {
            return false;
        }
        if (balance_[account - 1] < money) {
            return false;
        }
        balance_[account - 1] -= money;
        return true;
    }
};

int main() {
	return 0;
}