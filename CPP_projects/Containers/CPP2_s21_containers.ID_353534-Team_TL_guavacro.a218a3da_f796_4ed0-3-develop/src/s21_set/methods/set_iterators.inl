#include "../s21_set.h"

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::const_reference
s21::set<Key, Compare>::setIterator::operator*() const {
  return current_node->value;
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::setIterator&
s21::set<Key, Compare>::setIterator::operator++() {
  current_node = find_next(current_node);
  return *this;
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::setIterator&
s21::set<Key, Compare>::setIterator::operator--() {
  current_node = find_previous(current_node);
  return *this;
}

template <typename Key, typename Compare>

inline bool s21::set<Key, Compare>::setIterator::operator==(
    const setIterator& other) const {
  return current_node == other.current_node;
}

template <typename Key, typename Compare>

inline bool s21::set<Key, Compare>::setIterator::operator!=(
    const setIterator& other) const {
  return current_node != other.current_node;
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::const_reference
s21::set<Key, Compare>::setConstIterator::operator*() const {
  return current_node->value;
}

template <typename Key, typename Compare>

bool s21::set<Key, Compare>::setConstIterator::operator==(
    const setConstIterator& other) const {
  return current_node == other.current_node;
}

template <typename Key, typename Compare>

bool s21::set<Key, Compare>::setConstIterator::operator!=(
    const setConstIterator& other) const {
  return current_node != other.current_node;
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::Node*
s21::set<Key, Compare>::setIterator::find_next(Node* node) {
  Node* next_node = Node::nil();
  if (node->right != Node::nil()) {
    next_node = node->right;
    while (next_node->left != Node::nil()) next_node = next_node->left;
  } else {
    Node* parent = node->parent;
    while (parent != Node::nil() && node == parent->right) {
      next_node = parent;
      parent = next_node->parent;
    }
    next_node = parent;
  }
  return next_node;
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::Node*
s21::set<Key, Compare>::setIterator::find_previous(Node* node) {
  Node* previous_node = Node::nil();
  if (node->left != Node::nil()) {
    previous_node = node->left;
    while (previous_node->right != Node::nil())
      previous_node = previous_node->right;
  } else {
    Node* parent = node->parent;
    while (parent != Node::nil() && node == parent->left) {
      previous_node = parent;
      parent = previous_node->parent;
    }
    previous_node = parent;
  }
  return previous_node;
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::iterator s21::set<Key, Compare>::end() {
  Node* end_iterator = m_root;

  while (end_iterator->right != Node::nil()) end_iterator = end_iterator->right;

  return setIterator(end_iterator);
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::iterator
s21::set<Key, Compare>::begin() {
  Node* begin_iterator = m_root;

  while (begin_iterator->left != Node::nil())
    begin_iterator = begin_iterator->left;

  return setIterator(begin_iterator);
}
