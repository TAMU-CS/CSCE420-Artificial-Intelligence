#include "tree.h"
using namespace std;

Node *makeTree(string input)
{
  Node *root = new Node();
  input = input.substr(1, input.size() - 2);

  int openLoc = 0;
  int closedLoc = 0;
  while (openLoc < input.size())
  {
    closedLoc = openLoc;

    //number
    if (input[closedLoc] == '-' || isdigit(input[closedLoc]))
    {
      closedLoc++;
      while (closedLoc < input.size() && isdigit(input[closedLoc]))
      {
        closedLoc++;
      }

      int num = stoi(input.substr(openLoc, closedLoc - openLoc));
      Node *child = new Node();
      child->value = num;
      root->children.push_back(child);
    }
    //parenthesis
    else if (input[closedLoc] == '(')
    {
      int leftCount = 1;
      closedLoc++;
      while (leftCount > 0)
      {
        if (input[closedLoc] == ')')
        {
          leftCount--;
        }
        else if (input[closedLoc] == '(')
        {
          leftCount++;
        }
        closedLoc++;
      }

      Node *child = makeTree(input.substr(openLoc, closedLoc - openLoc));
      root->children.push_back(child);
    }

    openLoc = closedLoc + 1; //skip spaces
  }

  return root;
}

void printNode(Node *root)
{

  if (root->children.size() == 0)
  {
    cout << root->value;
  }
  else
  {
    cout << "(";
    for (int i = 0; i < root->children.size(); i++)
    {
      printNode(root->children[i]);
      if (i != root->children.size() - 1)
      {
        cout << " ";
      }
    }
    cout << ")";
  }
}

void printTree(Node *root)
{
  printNode(root);
  cout << "\n";
}
