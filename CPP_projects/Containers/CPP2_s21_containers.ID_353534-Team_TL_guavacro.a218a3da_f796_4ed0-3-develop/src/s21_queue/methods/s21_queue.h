#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class queue {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& val) : data(val), next(nullptr) {}
    Node(T&& val) : data(std::move(val)), next(nullptr) {}
  };

  Node* front_;
  Node* back_;
  size_t size_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  queue();
  queue(std::initializer_list<T> init);
  queue(const queue& other);
  queue(queue&& other) noexcept;
  ~queue();

  queue& operator=(const queue& other);
  queue& operator=(queue&& other) noexcept;

  const_reference front() const;
  const_reference back() const;

  bool empty() const noexcept;
  size_type size() const noexcept;

  void push(const_reference value);
  void push(value_type&& value);
  void pop();
  void swap(queue& other) noexcept;
  void clear();

  template <typename... Args>
  void insert_many_back(Args&&... args);
};

}  // namespace s21

#include "queue_capacity.inl"
#include "queue_constructors.inl"
#include "queue_extra_functions.inl"
#include "queue_modifiers.inl"

#endif
