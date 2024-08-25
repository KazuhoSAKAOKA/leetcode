#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        for (int i = 0; i < k; i++) {
            auto it = min_element(begin(nums), end(nums));
            *it *= multiplier;
        }
        return nums;
    }
};
void test(vector<int>&& nums, int k, int multiplier) {
    const auto ans = Solution().getFinalState(nums, k, multiplier);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
void run() {
    test(get_list_int("[2,1,3,5,6]"), 5, 2);
    test(get_list_int("[1,2]"), 3, 4);
}
}
namespace problem2 {
class Solution {
public:

    static bool almost_equals(int u, int v) {
        if (u == v) { return true; }
        auto ustr = '0' + to_string(u);
        for (int i = 0; i < size(ustr) - 1; i++) {
            for (int j = i + 1; j < size(ustr); j++) {
                string temp(ustr);
                temp[i] = ustr[j];
                temp[j] = ustr[i];
                if (stoi(temp) == v) {
                    return true;
                }
            }
        }
        return false;
    }
    int countPairs(vector<int>& nums) {
        int count = 0;
        for (int i = 0; i < size(nums) - 1; i++) {
            for (int j = i + 1; j < size(nums); j++) {
                if (almost_equals(nums[i], nums[j]) || almost_equals(nums[j], nums[i])) {
                    count++;
                }
            }
        }
        return count;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().countPairs(nums) << endl;
}
void run() {
    test(get_list_int("[936364,9134,693364,247642,987573,427642,778782,67416,309104,61476,396364,534154,309424,67416,393664,693346,963364,963364,963364,693346,847668,987573,145597,396364,493366,943366,643396,806680,76072,806690,467242,493663,685492,860680,496363]"));
    test(get_list_int("[3,12,30,17,21]"));
    test(get_list_int("[1,1,1,1,1]"));
    test(get_list_int("[123,231]"));
}
}
namespace problem3 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        const auto n = size(nums);

        struct work {
            long long value_;
            size_t index_;
            bool operator < (const work& other) const {
                if (value_ != other.value_) {
                    return value_ > other.value_;
                }
                return index_ > other.index_;
            }
        };

        priority_queue<work> p_queue;
        for (size_t i = 0; i < n; i++) {
            p_queue.push(work{nums[i], i});
        }
        int i = 0;
        while(i < k) {
            work top = p_queue.top();
            p_queue.pop();
            const auto& next_val = p_queue.top().value_;
            const auto diff = next_val - top.value_;
            const int op_count = diff / (top.value_ * multiplier);
            if (op_count == 0) {
                top.value_ *= multiplier;
                top.value_ %= MODULO;
                p_queue.push(top);
                i++;
                continue;
            }
            const long long multiple = min(k - i, op_count);
            top.value_ *= multiple * multiplier;
            top.value_ %= MODULO;
            p_queue.push(top);
            i += multiple;
        }
        while (!p_queue.empty()) {
            work top = p_queue.top();
            p_queue.pop();
            nums[top.index_] = static_cast<int>(top.value_);
        }
        return nums;
    }
};
void test(vector<int>&& nums, int k, int multiplier) {
    const auto ans = Solution().getFinalState(nums, k, multiplier);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
void run() {
    test(get_list_int("[2,1,3,5,6]"), 5, 2);
    test(get_list_int("[100000,2000]"), 2, 1000000);
}
}
namespace problem4 {
class Solution {
public:
    struct num_info {
        int num_;
        vector<int> digit_freq_;
        int zeros_;
        string digits_;
    };
    static num_info convert(int num) {
        auto s = to_string(num);
        vector<int> digit_freq(10);
        int zeros = 0;
        for (auto&& c : s) {
            if (c == '0') {
                zeros++;
            }
            else {
                digit_freq[c - '0']++;
            }
        }
        return num_info{
            num,
            digit_freq,
            zeros,
            s,
        };
    }


    static bool almost_equals(const num_info& info1, const num_info& info2) {
        if (info1.num_ == info2.num_) { return true; }
        if (info1.digit_freq_ != info2.digit_freq_) { return false; }
        if (abs(info1.zeros_ - info2.zeros_) > 2) { return false; }

        const size_t info1_len = size(info1.digits_);
        const size_t info2_len = size(info2.digits_);
        string info1s;
        string info2s;
        if (info1_len != info2_len) {
            const num_info& smaller = info1_len < info2_len ? info1 : info2;
            const num_info& lager = info1_len < info2_len ? info2 : info1;
            const int zero_margin = min(max(0, lager.zeros_ - smaller.zeros_), 2);
            if (zero_margin > size(lager.digits_) - size(smaller.digits_)) {
                return false;
            }
            info1s = lager.digits_;
            info2s = string(zero_margin, '0') +  smaller.digits_;
        }
        else {
            info1s = info1.digits_;
            info2s = info2.digits_;
        }

        vector<int> incorrects;

        for (int i = 0; i < size(info1s); i++) {
            if (info1s[i] != info2s[i]) {
                incorrects.push_back(i);
            }
        }
        if (incorrects.empty()) {
            return true;
        }
        auto incorrect = incorrects.back();
        incorrects.pop_back();

        for (int i = 0; i < 2; i++) {
            const char target = info1s[incorrect];
            for (auto it = begin(incorrects); it != end(incorrects); ++it) {
                if (info2s[*it] == target) {
                    if (info1s[*it] == info2s[incorrect]) {
                        incorrects.erase(it);
                        if (incorrects.empty()) {
                            return true;
                        }
                        incorrect = incorrects.back();
                        incorrects.pop_back();
                    }
                    else {
                        incorrect = *it;
                        incorrects.erase(it);
                    }
                    break;
                }
            }
        }
        return incorrects.empty();
    }

    static int wa(const vector<int>& nums) {
        vector<num_info> num_infos;
        num_infos.reserve(size(nums));
        for (auto&& num : nums) {
            num_infos.emplace_back(convert(num));
        }

        int count = 0;
        for (int i = 0; i < size(nums) - 1; i++) {
            for (int j = i + 1; j < size(nums); j++) {
                if (almost_equals(num_infos[i], num_infos[j])) {
                    //cout << nums[i] << "(=)" << nums[j] << endl;
                    count++;
                }
            }
        }
        return count;
    }

    static unordered_set<int> create_candidates(int num, int max_len) {
        string num_str = to_string(num);
        if (size(num_str) < max_len) {
            num_str = string(max_len - size(num_str), '0') + num_str;
        }
        unordered_set<int> candidates;
        candidates.insert(num);
        for (int i = 0; i < max_len; i++) {
            for (int j = i + 1; j < max_len; j++) {
                swap(num_str[i], num_str[j]);
                candidates.insert(stoi(num_str));
                for (int k = 0; k < max_len; k++) {
                    for (int l = k + 1; l < max_len; l++) {
                        swap(num_str[k], num_str[l]);
                        candidates.insert(stoi(num_str));
                        swap(num_str[k], num_str[l]);
                    }
                }
                swap(num_str[i], num_str[j]);
            }
        }
        return candidates;
    }

    int countPairs(vector<int>& nums) {
        const int max_len = size(to_string(*max_element(cbegin(nums), cend(nums))));
        int count = 0;
        map<int, int> freq_map;
        for (int i = 0; i < size(nums); i++) {
            const auto candidates = create_candidates(nums[i], max_len);
            for (auto&& candidate : candidates) {
                count += freq_map[candidate];
            }
            freq_map[nums[i]]++;
        }
        return count;
    }


};
void test(vector<int>&& nums) {
    cout << Solution().countPairs(nums) << endl;
}
void run() {

    test(get_list_int("[1,10,100]"));
    test(get_list_int("[16,9,9,16,9,16,9,9,16,6,16,9,9,9,20,9]"));
    test(get_list_int("[1023,2310,2130,213]"));
    test(get_list_int("[928102,840054,199066,852080,800915,979693,625467,610996,934544,70414,189983,617768,616990,660424,113428,424374,603750,199606,186320,130912,503251,676503,275734,484364,742630,605313,609169,402156,53635,7897,63355,471359,768025,160969,919066,106996,961690,669019,166875,606244,416019,916906,129076,291983,246867,966901,61699,106699,58111,104968,966901,7798,288806,669190,422711,737693,378188,626404,910696,269338,817006,732760,617786,814616,916690,307276,128064,175325,206644,76563,535759,601969,183225,676105,277354,270376,601699,768358,446472,419106,7631,96169,597517,278449,820416,223201,125127,421217,377206,925031,283634,669190,55633,96916,891603,263834,55633,360207,672073,85,106969,444317,169069,360207,601699,609795,249748,987442,777383,487539,411833,53635,313772,693200,91966,56335,619906,606199,234264,427112,669901,188536,105325,581918,961609,606244,240853,515749,610996,106996,371659,199066,753427,869741,294847,635744,17310,539201,906619,640246,158223,16438,906169,610969,863301,450216,793454,126177,451795,610699,734465,880286,729820,910669,774496,69961,325274,740326,424473,130722,283436,224261,535759,271501,616099,653619,818536,217501,734456,715325,196096,196906,368758,350006,668724,214371,743026,696019,669190,9875,538243,882147,160996,53563,8266,640264,505321,280543,259528,169906,27376,414885,979693,58111,768520,103365,679993,840504,425273,152640,924748,661673,7897,348416,9787,482513,996016,141322,660919,332611,7136,135725,603351,123421,38689,110572,160969,910669,597078,720736,196690,743845,249748,823890,996160,69196,169690,127241,84557,906196,317094,906619,721656,329609,85273,396249,612177,980505,76744,503521,383642,966190,505132,444765,791255,916069,16996,105235,467345,790758,33655,916960,911848,945452,382634,390152,214217,737524,960196,710521,206464,174395,966190,7897,702763,961960,332648,7789,910696,221714,169906,96619,916069,696190,289447,819841,188356,734546,992742,800005,13701,906169,292870,715459,792515,916069,427885,118646,918841,774325,571597,424215,96619,223201,217501,172898,696019,660244,275734,16996,394801,601969,610996,128987,106996,166909,169609,806193,209161,734231,984742,106996,860140,669091,574327,7879,785447,13107,196096,165326,924428,749290,874920,963055,66991,916906,53635,864544,766046,797633,484634,451759,16996,15118,145759,160996,916906,391116,26446,814616,908292,106996,230138,696901,128897,428479,69619,91696,816255,476002,922208,691609,819841,108462,610699,466024,966703,956383,931049,734645,837189,53635,715325,910966,906916,644755,929888,906916,773701,411722,906961,487457,610996,629071,906169,906961,991066,546267,507978,916609,32776,760529,609961,424374,190696,297844,820198,917557,484577,763937,616990,545348,576106,691096,992472,134036,202217,481891,96619,206644,396002,966091,610996,6268,6628,708081,737206,427121,969160,61969,609619,596383,143163,427211,192788,609169,535021,105325,166909,721214,120468,105325,859522,754203,221714,55633,246744,35635,99166,989288,493801,240635,606919,452016,143122,976408,103356,212714,690691,669019,263839,595177,486434,233684,631497,428265,759897,452016,906196,775324,575197,753035,901669,795708,369238,267444,744359,51118,740236,766377,11370,106996,374645,540347,99616,8662,16996,634273,906916,392222,104268,772603,906196,640327,775234,906196,302776,40909,166099,726117,53635,98092,572402,152406,382634,327881,69916,776203,61553,966109,86431,229791,689954,422711,123418,364770,120468,606244,130255,878138]"));
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    //problem4::run();
    return 0;
}