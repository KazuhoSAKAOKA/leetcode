#pragma once
#include <vector>
#include <optional>
#include <utility>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* create_listnode(const std::vector<int>& list) {
    ListNode dummy_head;
    ListNode* before = &dummy_head;
    for (auto&& value : list) {
        before->next = new ListNode(value, nullptr);
        before = before->next;
    }
    return dummy_head.next;
}

void output_listnode(const ListNode* head) {
    std::cout << "output listnode begin" << std::endl;
    const ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->val << ",";
        current = current->next;
    }
    std::cout << std::endl << "output listnode begin" << std::endl;
}