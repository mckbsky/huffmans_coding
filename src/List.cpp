#include <List.hpp>
#include <cstdio>

void List::createList() {
    auto *newNode = new ListNode();
    newNode->setNext(nullptr);
    newNode->setPrev(nullptr);
    head = tail = newNode;
}

ListNode *List::getHead() const {
    return head;
}

void List::setHead(ListNode *head) {
    List::head = head;
}

ListNode *List::getTail() const {
    return tail;
}

void List::setTail(ListNode *tail) {
    List::tail = tail;
}

void List::insertListNode() {
    auto *newNode = new ListNode();
    newNode->setPrev(nullptr);
    newNode->setNext(getHead());
    getHead()->setPrev(newNode);
    setHead(newNode);
}

void List::deleteListNode(List **list) {
    if ((*list)->getHead() == nullptr) {
        fprintf(stderr, "Can't delete node from empty list\n");
        return;
    }
    ListNode *deletedNode = (*list)->getHead();
    (*list)->setHead(deletedNode->getNext());
    delete deletedNode;
}

