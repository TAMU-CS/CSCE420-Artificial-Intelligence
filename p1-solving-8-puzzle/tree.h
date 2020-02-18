#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Node
{
  int value;
  vector<Node *> children;

  // solution path that is filled when minmax is run
  int next;
};

Node *makeTree(string input);
void printTree(Node *root);

#endif