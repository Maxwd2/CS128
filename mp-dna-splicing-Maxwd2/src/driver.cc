#include <iostream>

#include "dna_strand.hpp"

int main() {
  Node one = Node('f');
  Node* one_p = &one;
  Node two = Node('e', one_p);
  Node* two_p = &two;
  Node three = Node('d', two_p);
  Node* three_p = &three;
  Node four = Node('c', three_p);
  Node* four_p = &four;
  Node five = Node('b', four_p);
  Node* five_p = &five;
  Node six = Node('a', five_p);
  Node* six_p = &six;
  DNAstrand d1;
  d1.SetHead(six_p);
  d1.SetTail(one_p);

  Node* curr_node = d1.GetHead();
  while (curr_node != nullptr) {
    std::cout << curr_node->data << "  ";
    curr_node = curr_node->next;
  }
  std::cout << "\nhead: " << d1.GetHead()->data << std::endl;
  std::cout << "tail: " << d1.GetTail()->data << std::endl;

  Node a = Node('t');
  Node* ap = &a;
  Node b = Node('s', ap);
  Node* bp = &b;
  Node c = Node('r', bp);
  Node* cp = &c;
  DNAstrand d2;
  d2.SetHead(cp);
  d2.SetTail(ap);

  // char string[]{"cde"};
  char string_p[] = "cde";
  std::cout << " After Splice: \n";
  d1.SpliceIn(string_p, d2);
  // std::cout << " After Splice: \n";
  Node* curr_node2 = d1.GetHead();
  while (curr_node2 != nullptr) {
    std::cout << curr_node2->data << "  ";
    curr_node2 = curr_node2->next;
  }
  std::cout << "\nhead: " << d1.GetHead()->data << std::endl;
  std::cout << "tail: " << d1.GetTail()->data << std::endl;
}