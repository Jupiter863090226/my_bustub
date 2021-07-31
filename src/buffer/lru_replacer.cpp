//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {
    num_frames_ = num_pages;
    replacable_frames_ = 0;
    head_ = new node(INVALID_PAGE_ID);
    tail_ = head_;
}

LRUReplacer::~LRUReplacer() {
    node *p = head_, *next;
    while(p != nullptr){
        next = p->next;
        delete p;
        p = next;
    }
}

void LRUReplacer::add_head(frame_id_t frame_id){
    node *new_node = new node(frame_id);
    map_[frame_id] = new_node;
    new_node->next = head_->next;
    new_node->prev = head_;
    if(head_->next != nullptr){
        head_->next->prev = new_node;
    }
    head_->next = new_node;
    if(tail_ == head_){
        tail_ = new_node;
    }
}

void LRUReplacer::delete_node(frame_id_t frame_id){
    node *target_node = map_[frame_id];
    if(tail_ == target_node){
        target_node->prev->next = nullptr;
        tail_ = target_node->prev;
        delete target_node;
    }
    else{
        target_node->prev->next = target_node->next;
        target_node->next->prev = target_node->prev;
        delete target_node;
    }
    map_.erase(frame_id);
}

bool LRUReplacer::Victim(frame_id_t *frame_id) {
    if(replacable_frames_ == 0){
        *frame_id = INVALID_PAGE_ID;
        return false;
    }
    
    *frame_id = tail_->frame_id;
    delete_node(tail_->frame_id);
    --replacable_frames_;
    return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
    if(map_.find(frame_id) != map_.end()){
        delete_node(frame_id);
        --replacable_frames_;
    }
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
    if(map_.find(frame_id) == map_.end()){
        add_head(frame_id);
        ++replacable_frames_;
    }
}

size_t LRUReplacer::Size() {
    return replacable_frames_;
}

}  // namespace bustub
