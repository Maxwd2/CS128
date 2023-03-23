#include "dna_strand.hpp"

#include <stdexcept>
/*
DNAstrand::DNAstrand() {
  head_ = nullptr;
  tail_ = nullptr;
} */

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* temp = head_->next;
    delete head_;
    head_ = temp;
  }
}

/*
void DNAstrand::Clear() {
  while (head_ != nullptr) {
    Node* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  head_ = nullptr;
  tail_ = nullptr;
}*/

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern == nullptr || to_splice_in.head_ == nullptr ||
      this == &to_splice_in) {
    return;
  }
  Node* delete_tracker_head = nullptr;
  Node* delete_tracker_tail = nullptr;
  bool found_sequence =
      FindSequence(delete_tracker_head, delete_tracker_tail, pattern);

  if (found_sequence) {
    SpliceFoundSequence(delete_tracker_head, delete_tracker_tail, to_splice_in);
  } else {
    throw std::invalid_argument("DNA does not contain pattern");
  }
}

bool DNAstrand::FindSequence(Node*& delete_tracker_head,
                             Node*& delete_tracker_tail,
                             const char* pattern) {
  // for finding pattern's length
  unsigned int length = 0;
  while (pattern[length] != '\0') {
    length++;
  }
  bool found_sequence = false;

  Node* curr_node = head_;
  while (curr_node != nullptr) {
    bool match = false;
    if (pattern[0] == curr_node->data) {
      Node* temp_curr_node = curr_node;
      for (unsigned int i = 0; i < length; i++) {
        if (temp_curr_node == nullptr || pattern[i] != temp_curr_node->data) {
          break;
        }
        if (i == length - 1) {
          match = true;
          delete_tracker_tail = temp_curr_node;
        }
        temp_curr_node = temp_curr_node->next;
      }
    }
    if (match) {
      delete_tracker_head = curr_node;
      found_sequence = true;
    }
    curr_node = curr_node->next;
  }
  return found_sequence;
}

void DNAstrand::SpliceFoundSequence(Node*& delete_tracker_head,
                                    Node*& delete_tracker_tail,
                                    DNAstrand& to_splice_in) {
  if (delete_tracker_head == head_) {
    SpliceSequenceAtHead(
        delete_tracker_head, delete_tracker_tail, to_splice_in);
  } else {
    Node* curr_node = head_;
    Node* replace_head = nullptr;
    // sets replace_head to the node before the node we want to replace
    while (curr_node->next != nullptr) {
      if (curr_node->next == delete_tracker_head) {
        replace_head = curr_node;
        break;
      }
      curr_node = curr_node->next;
    }
    replace_head->next = to_splice_in.head_;
    // checks if the replaced sequence stops at the tail_
    if (delete_tracker_tail->next == nullptr) {
      tail_ = to_splice_in.tail_;
    } else {
      to_splice_in.tail_->next = delete_tracker_tail->next;
    }
    // to make sure delete_tracker_tail->next can be found, since it would be
    // deleted before the while loop can read it
    Node* delete_tracker_tail_next = delete_tracker_tail->next;
    // deletes the original found pattern
    while (delete_tracker_head != delete_tracker_tail_next) {
      Node* temp = delete_tracker_head->next;
      delete delete_tracker_head;  // Causing double free or corruption error
      delete_tracker_head = temp;
    }
  }
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}

void DNAstrand::SpliceSequenceAtHead(Node*& delete_tracker_head,
                                     Node*& delete_tracker_tail,
                                     DNAstrand& to_splice_in) {
  // For the case where the sequence only has 1 node and is being replaced
  if (delete_tracker_head == delete_tracker_tail &&
      delete_tracker_tail == tail_) {
    delete head_;
    head_ = to_splice_in.head_;
    tail_ = to_splice_in.tail_;
    //  case where the whole sequence is being replaced and has more than 1 node
  } else if (delete_tracker_head == head_ && delete_tracker_tail == tail_ &&
             delete_tracker_head != delete_tracker_tail) {
    Node* curr_node = head_;
    while (curr_node != nullptr) {
      Node* temp = curr_node->next;
      delete curr_node;
      curr_node = temp;
    }
    head_ = to_splice_in.head_;
    tail_ = to_splice_in.tail_;
    // for the case where only the 1st node is being replaced in a sequence with
    // more than 1 node
  } else if (delete_tracker_tail == delete_tracker_head &&
             delete_tracker_tail != tail_) {
    to_splice_in.tail_->next = head_->next;
    delete head_;
    head_ = to_splice_in.head_;
    // for the case where multiple nodes are being replaced and starts at the
    // first node, but the last node being replaced is not the tail_
  } else if (delete_tracker_tail != delete_tracker_head &&
             delete_tracker_tail != tail_) {
    Node* curr_node = head_;
    Node* delete_tracker_tail_next = delete_tracker_tail->next;
    while (curr_node != delete_tracker_tail_next) {
      Node* temp = curr_node->next;
      delete curr_node;
      curr_node = temp;
    }
    to_splice_in.tail_->next = delete_tracker_tail_next;
    head_ = to_splice_in.head_;
  }
}

/*
// for finding pattern's length
  unsigned int length = 0;
  while (pattern[length] != '\0') {
    length++;
  }

  Node* delete_tracker_head = nullptr;
  Node* delete_tracker_tail = nullptr;
  Node* replace_head = nullptr;
  bool needs_deletion = false;
  bool first_loop = true;

  Node* curr_node = head_;
  while (curr_node != nullptr) {
    bool match = false;
    if (pattern[0] == curr_node->data) {
      Node* temp_curr_node = curr_node;
      for (unsigned int i = 0; i < length; i++) {
        if (temp_curr_node == nullptr || pattern[i] != temp_curr_node->data) {
          break;
        }
        if (i == length - 1) {
          match = true;
          delete_tracker_tail = temp_curr_node;
        }
        temp_curr_node = temp_curr_node->next;
      }
    }
    if (match) {
      delete_tracker_head = curr_node;
      needs_deletion = true;
    }
    curr_node = curr_node->next;
    first_loop = false;
  } */