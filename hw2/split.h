#ifndef SPLIT_H
#define SPLIT_H


struct Node 
{
  int value;
  Node* next;

  /**
   * Initializing constructor
   */
  Node(int v, Node* n)
  {
    value = v;
    next = n;
  }
};

void split(Node*& in, Node*& odds, Node*& evens);
void split_help(Node*& in, Node*& odds, Node*& evens, Node*& temp1, Node*& temp2, Node*& temp3);
void split_check(Node*& temp, int type);


#endif
