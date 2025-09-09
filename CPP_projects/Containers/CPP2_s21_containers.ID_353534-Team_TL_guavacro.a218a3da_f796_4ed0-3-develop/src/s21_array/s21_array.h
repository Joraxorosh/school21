#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <typename T, std::size_t N>
class array {
 private:
  std::size_t m_size{N};
  T m_array[N];

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  array() = default;
  array(const array& other);
  array(std::initializer_list<value_type> list);
  array& operator=(const array& other);
  array(array&& other) noexcept;
  array& operator=(array&& other) noexcept;
  ~array() = default;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void swap(array<T, N>& other);
  void fill(const_reference value);
};
}  // namespace s21

#include "methods/array_capacity.inl"
#include "methods/array_constructors.inl"
#include "methods/array_element_access.inl"
#include "methods/array_iterator_access.inl"
#include "methods/array_modifiers.inl"

#endif