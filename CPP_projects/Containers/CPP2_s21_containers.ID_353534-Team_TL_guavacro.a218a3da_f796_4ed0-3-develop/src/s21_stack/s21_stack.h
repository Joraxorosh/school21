#ifndef CPP2_S21_CONTAINERS_STACK_H
#define CPP2_S21_CONTAINERS_STACK_H

#include <initializer_list>
#include <iostream>
#include <utility>

#include "s21_deque.h"

namespace s21 {
template <class T, class Container = deque<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<T> const &items);
  stack(const stack &other);
  stack(stack &&other) noexcept;
  ~stack();

  stack &operator=(stack &&other) noexcept;

  const_reference top() const;
  size_type size() const;

  bool empty() const;
  void swap(stack &other);

  void push(const_reference value);
  void pop();

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Container deque_;
};

}  // namespace s21

namespace s21 {
template <class value_type, class Container>
stack<value_type, Container>::stack() : deque_() {}

template <class value_type, class Container>
stack<value_type, Container>::stack(
    std::initializer_list<value_type> const &items)
    : deque_() {
  for (const auto &item : items) push(item);
}

template <class value_type, class Container>
stack<value_type, Container>::stack(const stack &other)
    : deque_(other.deque_) {}

template <class value_type, class Container>
stack<value_type, Container>::stack(stack &&other) noexcept
    : deque_(std::move(other.deque_)) {}

template <class value_type, class Container>
stack<value_type, Container>::~stack() {}

template <class value_type, class Container>
stack<value_type, Container> &stack<value_type, Container>::operator=(
    stack &&other) noexcept {
  if (this != &other) deque_ = std::move(other.deque_);
  return *this;
}

template <class value_type, class Container>
typename stack<value_type, Container>::const_reference
stack<value_type, Container>::top() const {
  if (empty()) throw std::out_of_range("conteiner is empty");
  return deque_.back();
}

template <class value_type, class Container>
bool stack<value_type, Container>::empty() const {
  return deque_.empty();
}

template <class value_type, class Container>
typename stack<value_type, Container>::size_type
stack<value_type, Container>::size() const {
  return deque_.size();
}

template <class value_type, class Container>
void stack<value_type, Container>::push(const_reference value) {
  deque_.push_back(value);
}

template <class value_type, class Container>
void stack<value_type, Container>::pop() {
  if (!deque_.empty()) {
    deque_.pop_back();
  }
}

template <class value_type, class Container>
void stack<value_type, Container>::swap(stack &other) {
  std::swap(deque_, other.deque_);
}

template <class value_type, class Container>
template <typename... Args>
void stack<value_type, Container>::insert_many_back(Args &&...args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_STACK_H