#include <ListNode.hpp>

ListNode *ListNode::getPrev() const {
    return prev;
}

void ListNode::setPrev(ListNode *prev) {
    ListNode::prev = prev;
}

ListNode *ListNode::getNext() const {
    return next;
}

void ListNode::setNext(ListNode *next) {
    ListNode::next = next;
}

char ListNode::getCode() const {
    return code;
}

void ListNode::setCode(char code) {
    ListNode::code = code;
}

