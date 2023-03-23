#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  // Don't know if I need to do something here
  DNAstrand() = default;

  // don't worry about these 2 functions
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;

  // Done
  ~DNAstrand();

  // Still need to account for the sequence being at the first node (head_)
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

  // My Helper Functions

  // these are just for testing and creating a full DNAstrand object, not
  // planning to use in the final code
  void SetHead(Node* head) { head_ = head; };
  void SetTail(Node* tail) { tail_ = tail; };
  Node* GetHead() { return head_; };
  Node* GetTail() { return tail_; };

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;

  // Helper Functions
  // Just need to account for head with both
  bool FindSequence(Node*& delete_tracker_head,
                    Node*& delete_tracker_tail,
                    const char* pattern);

  void SpliceFoundSequence(Node*& delete_tracker_head,
                           Node*& delete_tracker_tail,
                           DNAstrand& to_splice_in);

  void SpliceSequenceAtHead(Node*& delete_tracker_head,
                            Node*& delete_tracker_tail,
                            DNAstrand& to_splice_in);
};

#endif