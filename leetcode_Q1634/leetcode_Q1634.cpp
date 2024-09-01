// leetcode_Q1634.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

struct PolyNode {
    int coefficient, power;
    PolyNode* next;
    PolyNode() : coefficient(0), power(0), next(nullptr) {};
    PolyNode(int x, int y) : coefficient(x), power(y), next(nullptr) {};
    PolyNode(int x, int y, PolyNode* next) : coefficient(x), power(y), next(next) {};
};

class Solution {
public:
    PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {
        PolyNode dummy_head;
        PolyNode* ptr1 = poly1;
        PolyNode* ptr2 = poly2;

        PolyNode* before = &dummy_head;

        while (ptr1 != nullptr && ptr2 != nullptr) {
            if (ptr1->power == ptr2->power) {
                const auto new_coefficient = ptr1->coefficient + ptr2->coefficient;
                if (new_coefficient != 0) {
                    PolyNode* new_node = new PolyNode(new_coefficient, ptr1->power);
                    before->next = new_node;
                    before = new_node;
                }
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            else {
                PolyNode* target_ptr = ptr1->power > ptr2->power ? ptr1 : ptr2;
                PolyNode* new_node = new PolyNode(target_ptr->coefficient, target_ptr->power);
                before->next = new_node;
                before = new_node;
                if (ptr1->power > ptr2->power) {
                    ptr1 = ptr1->next;
                }
                else {
                    ptr2 = ptr2->next;
                }
            }
        }

        PolyNode* only_ptr = ptr1 == nullptr ? ptr2 : ptr1;
        while (only_ptr != nullptr) {
            PolyNode* new_node = new PolyNode(only_ptr->coefficient, only_ptr->power);
            before->next = new_node;
            before = new_node;
            only_ptr = only_ptr->next;
        }

        return dummy_head.next;
    }
};

PolyNode* create_poly_node(const vector<vector<int>>& values) {
    PolyNode dummy_head;
    PolyNode* before = &dummy_head;
    for (auto&& value_pair : values) {
        PolyNode* current = new PolyNode(value_pair[0], value_pair[1]);
        before->next = current;
        before = current;
    }
    return dummy_head.next;
}

void test(vector<vector<int>>&& values1, vector<vector<int>>&& values2) {
    PolyNode* ans = Solution().addPoly(create_poly_node(values1), create_poly_node(values2));
    PolyNode* current = ans;
    cout << "[";
    while (current != nullptr) {
        cout << "[" << current->coefficient << "," << current->power << "],";
        current = current->next;
    }
    cout << "]" << endl;
}

int main()
{
    test(get_matrix_int("[[1,1]]"), get_matrix_int("[[1,0]]"));
    test(get_matrix_int("[[2,2],[4,1],[3,0]]"), get_matrix_int("[[3,2],[-4,1],[-1,0]]"));
    test(get_matrix_int("[[1,2]]"), get_matrix_int("[[-1,2]]"));
    return 0;
}