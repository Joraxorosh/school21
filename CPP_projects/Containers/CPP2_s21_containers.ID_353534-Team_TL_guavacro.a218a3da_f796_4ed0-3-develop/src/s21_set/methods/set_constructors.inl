#include "../s21_set.h"

template <typename Key, typename Compare>

inline s21::set<Key, Compare>::set(const set& s) {
  m_root = Node::nil();
  copy_tree(s.m_root);
}

template <typename Key, typename Compare>

inline s21::set<Key, Compare>::set(std::initializer_list<Key> items) {
  for (const auto& item : items) {
    this->insert(item);
  }
}

template <typename Key, typename Compare>

inline s21::set<Key, Compare>::set(set&& s) {
  m_root = s.m_root;
  s.m_root = Node::nil();
}

template <typename Key, typename Compare>

inline s21::set<Key, Compare>& s21::set<Key, Compare>::operator=(set&& s) {
  if (this != &s) {
    delete_tree(m_root);
    m_root = s.m_root;
    s.m_root = Node::nil();
  }
  return *this;
}

template <typename Key, typename Compare>

inline s21::set<Key, Compare>::~set() {
  delete_tree(m_root);
}

template <typename Key, typename Compare>

inline void s21::set<Key, Compare>::delete_tree(Node* node) {
  if (node && node != Node::nil()) {
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
  }
}

template <typename Key, typename Compare>
inline void s21::set<Key, Compare>::copy_tree(Node* node) {
  if (node != Node::nil()) {
    copy_tree(node->left);
    this->insert(node->value);
    copy_tree(node->right);
  }
}