#ifndef HUFFMANS_CODING_LISTNODE_HPP
#define HUFFMANS_CODING_LISTNODE_HPP

class ListNode {

private:

    char code;
    ListNode *prev;
    ListNode *next;

public:

    ListNode *getPrev() const;

    void setPrev(ListNode *prev);

    ListNode *getNext() const;

    void setNext(ListNode *next);

    char getCode() const;

    void setCode(char code);

};


#endif
