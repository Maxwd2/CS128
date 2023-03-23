#include <stdexcept>

#include "dna_strand.hpp"

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
  }
  curr_node = head_;
  if (needs_deletion) {
    // just to set the replace_head to the node before the node we want
    // to replace, will make replacement easier
    while (curr_node->next != nullptr) {
      if (curr_node->next == delete_tracker_head) {
        replace_head = curr_node;
        break;
      }
      curr_node = curr_node->next;
    }
    replace_head->next = to_splice_in.head_;
    // checks if the replaced sequence stops at the last node in the list
    //(at the tail)
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
      Node* next = delete_tracker_head->next;
      delete delete_tracker_head;
      delete_tracker_head = next;
    }
    // this is for the deconstructor, as I think the issue was that the
    // to_plice_in DNAstrand still had it's head_ and tail_ pointing to the
    // nodes now in the given strand, so the deconstructor deleted both strands,
    // thereby deleting the same nodes more than once
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
  } else {
    throw std::invalid_argument("DNA does not contain pattern");
  }
}
