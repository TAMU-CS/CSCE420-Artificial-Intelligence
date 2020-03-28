#include "prover.h"
using namespace std;

int main()
{
  // vector<Clause> howling = {
  //     Clause("(1 ((howl z)) ((hound z)))"),
  //     Clause("(2 nil ((have x y) (cat y) (have x z) (mouse z)))"),
  //     Clause("(3 nil ((ls w) (have w v) (howl v)))"),
  //     Clause("(4 ((have (john) (a))) nil)"),
  //     Clause("(5 ((cat (a)) (hound (a))) nil)"),
  //     Clause("(6 ((mouse (b))) nil)"),
  //     Clause("(7 ((ls (john))) nil)"),
  //     Clause("(8 ((have (john) (b))) nil)"),
  // };
  // resolve(howling, 0);

  // vector<Clause> rr = {
  //     Clause("(1 ((rr (a))) ((coyote y)))"),
  //     Clause("(2 ((chase z (a))) ((coyote z)))"),
  //     Clause("(3 ((smart x)) ((rr x) (beep x)))"),
  //     Clause("(4 nil ((coyote w) (rr u) (catch w u) (smart u)))"),
  //     Clause("(5 ((frustrated s) (catch s t)) ((coyote s) (rr t) 	(chase s t)))"),
  //     Clause("(6 ((beep r))  ((rr r)))"),
  //     Clause("(7 ((coyote (b))) nil)"),
  //     Clause("(8 nil ((frustrated (b))))"),
  // };
  // resolve(rr, 7);

  // vector<Clause> customs = {
  //     Clause("(1 ((v x) (s x (f x))) ((e x)))"),
  //     Clause("(2 ((v y) (c (f y))) ((e y)))"),
  //     Clause("(3 ((e (a))) nil)"),
  //     Clause("(4 ((d (a))) nil)"),
  //     Clause("(5 ((d z)) ((s (a) z)))"),
  //     Clause("(6 nil ( (d w) (v w)))"),
  //     Clause("(7 nil ((d r) (c r)))"),
  // };
  // resolve(customs, 0);

  // vector<Clause> harmonia = {
  //     Clause("(1 ((Grandparent x y)) ((Parent x z) (Parent z y)))"), //(~Parent(x, z) || ~Parent(z, y)) || Grandparent(x, y)
  //     Clause("(2 ((Parent x y)) ((Mother x y)))"),
  //     Clause("(3 ((Parent x y)) ((Father x y)))"), // -father(x,y) || parent(x,y)
  //     Clause("(4 ((Father (Zues) (Ares))) nil)"),
  //     Clause("(5 ((Mother (Hera) (Ares))) nil"),
  //     Clause("(6 ((Father (Ares) (Harmonia))) nil)"),
  //     Clause("(7 nil ((Grandparent x (Harmonia))))"),
  // };
  // resolve(harmonia, 0);

  return 0;
}

void resolveHelper(unordered_map<string, bool> &dup, vector<Clause> &clauses, Clause &c1, Clause &c2, vector<Literal> &c1List,
                   vector<Literal> &c2List, int l1, int l2)
{

  // reset variable count if unification is not possible
  int oldVarCount = Variable::varNum;

  try
  {
    unordered_map<string, Unifiable *> sub = Literal::unify(c1List[l1].root, c2List[l2].root);

    // delete l1 and l2
    c1List.erase(c1List.begin() + l1);
    c2List.erase(c2List.begin() + l2);

    //apply substitution on both c1 and c2
    c1.substitute(sub);
    c2.substitute(sub);

    //combine the two clauses
    c1.add(c2);
    c1.num = clauses.size();

    string rawVal = c1.toStringNoNum();
    if (dup.find(rawVal) == dup.end())
    {
      dup[rawVal] = true;
      clauses.push_back(c1);

      cout << clauses[clauses.size() - 1] << endl;

      for (int i = 0; i < c1.pos.size(); i++)
      {
        if (typeid(*(c1.pos[i].root)) != typeid(Function))
        {
          throw 100;
        }
      }
      for (int i = 0; i < c1.neg.size(); i++)
      {
        if (typeid(*(c1.neg[i].root)) != typeid(Function))
        {
          throw 100;
        }
      }
    }
    else
    {
      Variable::varNum = oldVarCount;
    }
  }
  catch (int errCode)
  {
    // reset the variable counts
    Variable::varNum = oldVarCount;

    if (errCode == 100)
    {
      throw errCode;
    }
  }
}

void resolve(vector<Clause> clauses, int thm)
{

  unordered_map<string, bool> dup;

  for (int i = 0; i < clauses.size(); i++)
  {
    for (int j = i + 1; j < clauses.size(); j++)
    {
      for (int l1 = 0; l1 < clauses[i].pos.size(); l1++)
      {
        for (int l2 = 0; l2 < clauses[j].neg.size(); l2++)
        {
          // make deep copys of clauses[i] and clauses[j] for c1 and c2
          Clause c1(clauses[i].value);
          Clause c2(clauses[j].value);

          resolveHelper(dup, clauses, c1, c2, c1.pos, c2.neg, l1, l2);

          if (clauses[clauses.size() - 1].neg.size() == 0 && clauses[clauses.size() - 1].pos.size() == 0)
          {
            cout << "FAIL!" << endl;
            return;
          }
        }
      }

      for (int l1 = 0; l1 < clauses[i].neg.size(); l1++)
      {
        for (int l2 = 0; l2 < clauses[j].pos.size(); l2++)
        {
          // make deep copys of clauses[i] and clauses[j] for c1 and c2
          Clause c1(clauses[i].value);
          Clause c2(clauses[j].value);
          resolveHelper(dup, clauses, c1, c2, c1.neg, c2.pos, l1, l2);

          if (clauses[clauses.size() - 1].neg.size() == 0 && clauses[clauses.size() - 1].pos.size() == 0)
          {
            cout << "FAIL!" << endl;
            return;
          }
        }
      }
    }
  }

  cout << "Theorem was not proved" << endl;
}

//Clause("(1 ((howl v2)) ((hound v2)))"),
//Clause("(3 nil ((ls w1) (have w1 v2) (howl v2)))"),
// subs = (z0 | v2)
// l1 and l2 are unifiable
