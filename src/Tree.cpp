#include <cstdio>
#include <cstdlib>
#include "Tree.hpp"

Node *Tree::generateTree(Node *root, Histogram *histogram) {
    auto index = histogram->findHistogramSize();

    while (index >= 0) {
        if (nullptr != root) {
            if (index == 0) {
                root = addLeafToLeftBranch(histogram, root, index);
            } else {
                root = addTwoLeavesAndCreateNewRoot(histogram, root, index);
            }
        } else {
            if (index == 0) {
                root = addLeaf(histogram, index);
            } else {
                root = addTwoLeaves(histogram, index);
            }
        }
        index -= NUMBER_OF_NODES;
    }
    return root;
}

Node *Tree::addLeafToLeftBranch(Histogram *histogram, Node *root, int index) {
    auto *node = new Node();
    node->setLeft(new Node());
    node->getLeft()->setC(histogram->getNode(index)->getC());
    node->setRight(root);
    return node;
}

Node *Tree::addTwoLeavesAndCreateNewRoot(Histogram *histogram, Node *root, int index) {
    auto *node = new Node();
    node->setLeft(new Node());
    node->getLeft()->setC(histogram->getNode(index - 1)->getC());
    node->setRight(new Node());
    node->getRight()->setC(histogram->getNode(index)->getC());

    auto *newRoot = new Node();
    newRoot->setLeft(node);
    newRoot->setRight(root);
    return newRoot;
}

Node *Tree::addLeaf(Histogram *histogram, int index) {
    auto *node = new Node();
    node->setC(histogram->getNode(index)->getC());
    return node;
}

Node *Tree::addTwoLeaves(Histogram *histogram, int index) {
    auto *node = new Node();
    node->setLeft(new Node());
    node->getLeft()->setC(histogram->getNode(index - 1)->getC());
    node->setRight(new Node());
    node->getRight()->setC(histogram->getNode(index)->getC());
    return node;
}

void Tree::removeTree(Node *root) {
    if (root->getLeft() == nullptr && root->getRight() == nullptr) {
        delete root;
        return;
    }
    removeTree(root->getRight());
    if (root->getLeft() != nullptr) {
        removeTree(root->getLeft());
    }
    delete root;
}

Node *Tree::getRoot() {
    return this->root;
}

void Tree::createCodes(Node *root, List *list) {
    if (isSingleLeafTree(root, list)) {
        list->insertListNode();
        list->getHead()->setCode(CODE_LEFT);
    }

    if (isLeaf(root)) {
        saveCode(list, root->getC());
        list->deleteListNode(&list);
        return;
    }

    list->insertListNode();
    list->getHead()->setCode(CODE_RIGHT);
    createCodes(root->getRight(), list);
    list->insertListNode();
    list->getHead()->setCode(CODE_LEFT);
    createCodes(root->getLeft(), list);
    list->deleteListNode(&list);
}

bool Tree::isSingleLeafTree(Node *root, List *list) {
    return root->getLeft() == nullptr && root->getRight() == nullptr && list->getHead() == list->getTail();
}

bool Tree::isLeaf(Node *root) {
    return root->getC() != 0;
}

void Tree::saveCode(List *list, unsigned char c) {
    auto tmp = list->getTail()->getPrev();
    unsigned int i;
    size_t allocatedChunks = 0;

    for (i = 0; tmp != nullptr; i++) {
        if (i + 2 >= allocatedChunks) {
            allocatedChunks += 10;
            codes[c] = (char *) realloc(codes[c], (allocatedChunks) * sizeof(char));
        }
        codes[c][i] = tmp->getCode();
        codes[c][i + 1] = '\0';
        tmp = tmp->getPrev();
    }
}

void Tree::setRoot(Node *node) {
    this->root = node;
}
