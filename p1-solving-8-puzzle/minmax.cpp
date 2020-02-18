#include "minmax.h"

int minimaxValue(Node *node, bool max)
{

  // Goal state
  if (node->children.size() == 0)
  {
    return node->value;
  }
  // Return max successors
  else if (max)
  {
    node->value = numeric_limits<int>::min();
    for (int i = 0; i < node->children.size(); i++)
    {
      int val = minimaxValue(node->children[i], !max);
      if (val > node->value)
      {
        node->value = val;
        node->next = i;
      }
    }

    return node->value;
  }
  // Return min successors
  else
  {
    node->value = numeric_limits<int>::max();

    for (int i = 0; i < node->children.size(); i++)
    {
      int val = minimaxValue(node->children[i], !max);

      if (val < node->value)
      {
        node->value = val;
        node->next = i;
      }
    }
    return node->value;
  }
}

void minmax(Node *root)
{
  int val = minimaxValue(root, true);

  while (root->children.size() > 0)
  {
    cout << (root->next + 1);
    if(root->children[root->next]->children.size() > 0){
      cout << ", ";
    }
    root = root->children[root->next];
  }

  cout << endl;
}