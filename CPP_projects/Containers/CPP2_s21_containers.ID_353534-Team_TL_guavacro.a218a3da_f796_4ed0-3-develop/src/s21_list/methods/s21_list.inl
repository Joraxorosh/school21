#pragma once

#include <algorithm>
#include <vector>

namespace s21 {

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
list<T>::list(std::initializer_list<T> init) : list() {
  for (const auto& val : init) push_back(val);
}

template <typename T>
list<T>::list(const list& other) : list() {
  for (auto it = other.begin(); it != other.end(); ++it) push_back(*it);
}

template <typename T>
list<T>::list(list&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  if (this != &other) {
    clear();
    for (auto it = other.begin(); it != other.end(); ++it) push_back(*it);
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  return const_iterator(head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return const_iterator(nullptr);
}

template <typename T>
bool list<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
void list<T>::clear() {
  while (!empty()) pop_front();
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  Node* insert_pos = const_cast<Node*>(pos.get_node());

  if (other.empty()) return;

  if (!insert_pos) {
    if (!tail_) {
      head_ = other.head_;
      tail_ = other.tail_;
    } else {
      tail_->next = other.head_;
      other.head_->prev = tail_;
      tail_ = other.tail_;
    }
  } else {
    Node* prev = insert_pos->prev;
    if (prev)
      prev->next = other.head_;
    else
      head_ = other.head_;

    other.head_->prev = prev;
    insert_pos->prev = other.tail_;
    other.tail_->next = insert_pos;
  }

  size_ += other.size_;
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::reverse() {
  Node* current = head_;

  while (current) {
    std::swap(current->next, current->prev);
    current = current->prev;
  }

  std::swap(head_, tail_);
}

template <typename T>
void list<T>::unique() {
  if (empty()) return;
  Node* curr = head_;
  while (curr && curr->next) {
    if (curr->data == curr->next->data) {
      Node* duplicate = curr->next;
      curr->next = duplicate->next;
      if (duplicate->next)
        duplicate->next->prev = curr;
      else
        tail_ = curr;
      delete duplicate;
      --size_;
    } else {
      curr = curr->next;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) return;
  std::vector<T> values;
  for (auto it = begin(); it != end(); ++it) values.push_back(*it);
  std::sort(values.begin(), values.end());

  clear();
  for (const auto& val : values) push_back(val);
}

template <typename T>
void list<T>::push_back(const T& value) {
  Node* node = new Node(value);
  if (!tail_) {
    head_ = tail_ = node;
  } else {
    tail_->next = node;
    node->prev = tail_;
    tail_ = node;
  }
  ++size_;
}

template <typename T>
void list<T>::push_front(const T& value) {
  Node* node = new Node(value);
  if (!head_) {
    head_ = tail_ = node;
  } else {
    node->next = head_;
    head_->prev = node;
    head_ = node;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  if (!tail_) throw std::out_of_range("List is empty");
  Node* temp = tail_;
  tail_ = tail_->prev;
  if (tail_)
    tail_->next = nullptr;
  else
    head_ = nullptr;
  delete temp;
  --size_;
}

template <typename T>
void list<T>::pop_front() {
  if (!head_) throw std::out_of_range("List is empty");
  Node* temp = head_;
  head_ = head_->next;
  if (head_)
    head_->prev = nullptr;
  else
    tail_ = nullptr;
  delete temp;
  --size_;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T& value) {
  Node* current = pos.get_node();
  if (!current) {
    push_back(value);
    return iterator(tail_);
  } else if (!current->prev) {
    push_front(value);
    return iterator(head_);
  } else {
    Node* node = new Node(value);
    node->prev = current->prev;
    node->next = current;
    current->prev->next = node;
    current->prev = node;
    ++size_;
    return iterator(node);
  }
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
  Node* current = pos.get_node();
  if (!current) throw std::out_of_range("Invalid iterator");
  Node* next_node = current->next;

  if (current->prev)
    current->prev->next = current->next;
  else
    head_ = current->next;

  if (current->next)
    current->next->prev = current->prev;
  else
    tail_ = current->prev;

  delete current;
  --size_;

  return iterator(next_node);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(iterator pos, Args&&... args) {
  if constexpr (sizeof...(Args) == 0) {
    return pos;
  } else {
    for (auto&& value : {T(std::forward<Args>(args))...}) {
      pos = insert(pos, value);
      ++pos;
    }
    return pos;
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  (void)std::initializer_list<int>{(push_back(std::forward<Args>(args)), 0)...};
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  std::vector<T> values{std::forward<Args>(args)...};
  for (auto it = values.rbegin(); it != values.rend(); ++it) {
    this->push_front(*it);
  }
}

template <typename T>
T& list<T>::front() {
  if (!head_) throw std::out_of_range("List is empty");
  return head_->data;
}

template <typename T>
T& list<T>::back() {
  if (!tail_) throw std::out_of_range("List is empty");
  return tail_->data;
}

}  // namespace s21
