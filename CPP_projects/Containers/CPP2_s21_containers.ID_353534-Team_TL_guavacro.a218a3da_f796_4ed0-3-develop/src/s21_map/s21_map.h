#ifndef S21_MAP_H
#define S21_MAP_H

#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename Key, typename T, typename Compare = std::less<Key>>
class map {
 private:
  // member types
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  // color structure
  enum Color { RED, BLACK };

  // node structure
  struct Node {
    value_type value;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(const Key& key, const T& mapped, Color color = RED)
        : value(key, mapped),
          color(color),
          parent(nil_node),
          left(nil_node),
          right(nil_node) {}

    inline static Node* nil_node = new Node(Key{}, BLACK);
    static Node* nil() { return nil_node; }
  };

  // member variables
  Node* m_root = Node::nil();

  // help functions
  void left_rotate(Node* node);
  void right_rotate(Node* node);
  void fix_insert_violations(Node* insert_node);
  void fix_delete_violations(Node* new_node);
  void delete_tree(Node* node);
  void copy_tree(Node* node);
  int count_nodes(Node* node);
  Node* search(Node* node, const Key& key);
  void node_transplant(Node* old_node, Node* new_node);

 public:
  // iterators
  class mapIterator {
   public:
    Node* current_node;

   private:
    Node* find_next(Node* node);
    Node* find_previous(Node* node);

   public:
    mapIterator(Node* node = Node::nil()) : current_node(node) {}

    map::const_reference operator*() const;
    std::pair<const Key, T>* operator->() const;
    mapIterator& operator++();
    mapIterator operator++(int);
    mapIterator& operator--();
    mapIterator operator--(int);
    bool operator==(const mapIterator& other) const;
    bool operator!=(const mapIterator& other) const;
  };

  class mapConstIterator {
   private:
    Node* current_node;

   public:
    mapConstIterator(Node* node = Node::nil()) : current_node(node) {}

    map::const_reference operator*() const;
    bool operator==(const mapConstIterator& other) const;
    bool operator!=(const mapConstIterator& other) const;
  };

  using iterator = mapIterator;
  using iteratorConst = mapConstIterator;

  // constructors
  map() = default;
  map(std::initializer_list<value_type> const& items);
  map(const map& s);
  map(map&& s);
  map& operator=(map&& s);
  ~map();

  // main methods
  void clear();
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);

  // iterator methods
  iterator end();
  iterator begin();

  // capacity methods
  bool empty();
  size_type size();
  size_type max_size();

  // lookup methods
  iterator find(const Key& key);
  bool contains(const Key& key);

  // element access methods
  T& at(const Key& key);
  T& operator[](const Key& key);

  // mutators
  Node* get() const;

  // //extra functions
  void print(Node* root);
  Node* minimum(Node* node);
};
}  // namespace s21

#include "methods/map_capacity.inl"
#include "methods/map_constructors.inl"
#include "methods/map_elements_access.inl"
#include "methods/map_erase.inl"
#include "methods/map_extra_functions.inl"
#include "methods/map_insert.inl"
#include "methods/map_iterators.inl"
#include "methods/map_modifiers.inl"
#include "methods/map_mutators.inl"
#include "methods/map_tree_rotations.inl"

#endif