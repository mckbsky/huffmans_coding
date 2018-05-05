#ifndef TREE_H
#define TREE_H

#include "Node.hpp"
#include "Histogram.hpp"
#include "List.hpp"

#define NUMBER_OF_NODES 2
#define CODE_LEFT '0'
#define CODE_RIGHT '1'

class Tree {

private:

    Node *root;
    char **codes;

public:

    Node *generateTree(Node *root, Histogram *histogram);

    Node *addLeafToLeftBranch(Histogram *histogram, Node *root, int index);

    Node *addTwoLeavesAndCreateNewRoot(Histogram *histogram, Node *root, int index);

    Node *addLeaf(Histogram *histogram, int index);

    Node *addTwoLeaves(Histogram *histogram, int index);

    void createCodes(Node *root, List *list);

    void saveCode(List *list, unsigned char c);

    void removeTree(Node *root);

    Node *getRoot();

    bool isLeaf(Node *root);

    bool isSingleLeafTree(Node *root, List *list);

};

#endif
