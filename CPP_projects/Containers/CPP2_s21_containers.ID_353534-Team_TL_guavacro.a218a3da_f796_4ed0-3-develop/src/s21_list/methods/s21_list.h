#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class list {
 private:
  struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  size_t size_;

 public:
  class iterator {
   public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    iterator(Node* ptr = nullptr) : current_(ptr) {}

    T& operator*() const { return current_->data; }

    iterator& operator++() {
      if (current_) current_ = current_->next;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      if (current_) current_ = current_->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iterator& other) const {
      return current_ == other.current_;
    }
    bool operator!=(const iterator& other) const {
      return current_ != other.current_;
    }

    Node* get_node() const { return current_; }

    friend class list;

   private:
    Node* current_;
  };

  class const_iterator {
   public:
    using value_type = const T;
    using reference = const T&;
    using pointer = const T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    const_iterator(const Node* ptr = nullptr) : current_(ptr) {}

    const T& operator*() const { return current_->data; }

    const_iterator& operator++() {
      if (current_) current_ = current_->next;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator& operator--() {
      if (current_) current_ = current_->prev;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator& other) const {
      return current_ == other.current_;
    }
    bool operator!=(const const_iterator& other) const {
      return current_ != other.current_;
    }

    const Node* get_node() const { return current_; }

    friend class list;

   private:
    const Node* current_;
  };

  using size_type = size_t;

  list();
  list(std::initializer_list<T> init);
  list(const list& other);
  list(list&& other) noexcept;
  ~list();

  list& operator=(const list& other);
  list& operator=(list&& other) noexcept;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  void clear();
  void swap(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  void push_back(const T& value);
  void push_front(const T& value);
  void pop_back();
  void pop_front();

  iterator insert(iterator pos, const T& value);
  iterator erase(iterator pos);

  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

  T& front();
  T& back();
};

}  // namespace s21

#include "s21_list.inl"

#endif  // S21_LIST_H
