#include <Node.hpp>

unsigned char Node::getC() const {
    return c;
}

void Node::setC(unsigned char c) {
    Node::c = c;
}

int Node::getFreq() const {
    return freq;
}

void Node::setFreq(int freq) {
    Node::freq = freq;
}

int Node::getZeroes() const {
    return zeroes;
}

void Node::setZeroes(int zeroes) {
    Node::zeroes = zeroes;
}

Node *Node::getLeft() const {
    return left;
}

void Node::setLeft(Node *left) {
    Node::left = left;
}

Node *Node::getRight() const {
    return right;
}

void Node::setRight(Node *right) {
    Node::right = right;
}
