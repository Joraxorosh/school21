#ifndef s21_multiset_H
#define s21_multiset_H

#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>

class multiset {
 protected:
  // member types
  using key_type = Key;
  using value_type = Key;
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

    Node(const Key& value, Color color = RED)
        : value(value),
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
  void merge_node(Node* node);
  void node_transplant(Node* old_node, Node* new_node);

 public:
  // iterators
  class multisetIterator {
   public:
    Node* current_node;

   private:
    Node* find_next(Node* node);
    Node* find_previous(Node* node);

   public:
    multisetIterator(Node* node = Node::nil()) : current_node(node) {}

    multiset::const_reference operator*() const;
    multisetIterator& operator++();
    multisetIterator& operator--();
    bool operator==(const multisetIterator& other) const;
    bool operator!=(const multisetIterator& other) const;
  };

  class multisetConstIterator {
   private:
    Node* current_node;

   public:
    multisetConstIterator(Node* node = Node::nil()) : current_node(node) {}

    multiset::const_reference operator*() const;
    bool operator==(const multisetConstIterator& other) const;
    bool operator!=(const multisetConstIterator& other) const;
  };

  using iterator = multisetIterator;
  using const_iterator = multisetConstIterator;
  Node* get_root() const { return m_root; }
  // constructors
  multiset() = default;
  multiset(std::initializer_list<
           typename s21::multiset<Key, Compare>::value_type> const& items);
  multiset(const multiset& s);
  multiset(multiset&& s);
  multiset& operator=(multiset&& s);
  ~multiset();

  // main methods
  void clear();
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);
  std::pair<multiset::iterator, bool> insert(
      const typename s21::multiset<Key, Compare>::value_type& value);

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

  // mutators
  Node* get() const;

  // extra functions
  void print(Node* root);
  Node* minimum(Node* node);
};
}  // namespace s21

#include "methods/set_capacity.inl"
#include "methods/set_constructors.inl"
#include "methods/set_erase.inl"
#include "methods/set_extra_functions.inl"
#include "methods/set_insert.inl"
#include "methods/set_iterators.inl"
#include "methods/set_lookup.inl"
#include "methods/set_modifiers.inl"
#include "methods/set_mutators.inl"
#include "methods/set_tree_rotations.inl"

#endif