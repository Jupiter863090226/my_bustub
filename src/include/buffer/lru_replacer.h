//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.h
//
// Identification: src/include/buffer/lru_replacer.h
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <list>
#include <mutex>  // NOLINT
#include <vector>
#include <unordered_map>

#include "buffer/replacer.h"
#include "common/config.h"

namespace bustub {

/**
 * LRUReplacer implements the lru replacement policy, which approximates the Least Recently Used policy.
 */
class LRUReplacer : public Replacer {
 public:
  /**
   * Create a new LRUReplacer.
   * @param num_pages the maximum number of pages the LRUReplacer will be required to store
   */
  explicit LRUReplacer(size_t num_pages);

  /**
   * Destroys the LRUReplacer.
   */
  ~LRUReplacer() override;

  bool Victim(frame_id_t *frame_id) override;

  void Pin(frame_id_t frame_id) override;

  void Unpin(frame_id_t frame_id) override;

  size_t Size() override;

 private:
  // TODO(student): implement me!
  struct node{
      frame_id_t frame_id;
      struct node *prev;
      struct node *next;
      node(frame_id_t frame_id) : frame_id(frame_id){
          prev = nullptr;
          next = nullptr;
      }
  };
  node *head_, *tail_;
  size_t num_frames_;
  size_t replacable_frames_;
  std::unordered_map<frame_id_t, node*> map_;
  void add_head(frame_id_t frame_id);
  void delete_node(frame_id_t frame_id);
  std::mutex latch_;
};

}  // namespace bustub
