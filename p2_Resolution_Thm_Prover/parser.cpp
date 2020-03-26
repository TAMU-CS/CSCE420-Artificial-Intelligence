#include "parser.h"

vector<string> Parser::parse_terms(string info)
{
  vector<string> varList;

  // parse and divide info string into the three elements
  int first = 0;
  int last = 0;
  while (last < info.size())
  {
    // ignore white space
    while (last < info.size() && isspace(info[last]))
    {
      last++;
    }
    if (last == info.size())
    {
      break;
    }

    first = last;
    if (info[first] == '(')
    {
      int leftCount = 1;
      int rightCount = 0;
      last++;
      while (leftCount > rightCount)
      {
        if (info[last] == '(')
        {
          leftCount++;
        }
        else if (info[last] == ')')
        {
          rightCount++;
        }
        last++;
      }
      varList.push_back(info.substr(first, last - first));
    }
    else
    {
      // ignore white space
      while (last < info.size() && !isspace(info[last]))
      {
        last++;
      }
      varList.push_back(info.substr(first, last - first));
    }

    last++;
  }

  return varList;
}
