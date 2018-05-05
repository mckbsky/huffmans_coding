#ifndef LIST_HPP
#define LIST_HPP

#include "ListNode.hpp"

class List {

private:

    ListNode *head;
    ListNode *tail;

public:

    ListNode *getHead() const;

    void setHead(ListNode *head);

    ListNode *getTail() const;

    void setTail(ListNode *tail);

    void createList();

    void insertListNode();

    void deleteListNode(List **list);

};

#endif