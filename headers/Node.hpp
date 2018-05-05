#ifndef HUFFMANS_CODING_NODE_HPP
#define HUFFMANS_CODING_NODE_HPP

class Node {

private:
    unsigned char c;
    int freq;
    int zeroes;
    Node *left;
    Node *right;

public:
    unsigned char getC() const;

    void setC(unsigned char c);

    int getFreq() const;

    void setFreq(int freq);

    int getZeroes() const;

    void setZeroes(int zeroes);

    Node *getLeft() const;

    void setLeft(Node *left);

    Node *getRight() const;

    void setRight(Node *right);

};


#endif
