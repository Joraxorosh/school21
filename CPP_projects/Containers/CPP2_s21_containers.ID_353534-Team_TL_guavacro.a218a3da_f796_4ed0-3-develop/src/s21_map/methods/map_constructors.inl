#include "../s21_map.h"

template <typename Key, typename T, typename Compare>

inline void s21::map<Key, T, Compare>::copy_tree(Node* node) {
  if (node != Node::nil()) {
    copy_tree(node->left);
    insert(node->value);
    copy_tree(node->right);
  }
}

template <typename Key, typename T, typename Compare>

inline s21::map<Key, T, Compare>::map(const map& s) {
  m_root = Node::nil();
  copy_tree(s.m_root);
}

template <typename Key, typename T, typename Compare>

inline s21::map<Key, T, Compare>::map(map&& s) {
  m_root = s.m_root;
  s.m_root = Node::nil();
}

template <typename Key, typename T, typename Compare>

inline s21::map<Key, T, Compare>& s21::map<Key, T, Compare>::operator=(
    map&& s) {
  if (this != &s) {
    delete_tree(m_root);
    m_root = s.m_root;
    s.m_root = Node::nil();
  }
  return *this;
}
template <typename Key, typename T, typename Compare>

inline s21::map<Key, T, Compare>::map(
    std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    this->insert(item);
  }
}

template <typename Key, typename T, typename Compare>

inline s21::map<Key, T, Compare>::~map() {
  delete_tree(m_root);
}

template <typename Key, typename T, typename Compare>

inline void s21::map<Key, T, Compare>::delete_tree(Node* node) {
  if (node != Node::nil()) {
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
  }
}
