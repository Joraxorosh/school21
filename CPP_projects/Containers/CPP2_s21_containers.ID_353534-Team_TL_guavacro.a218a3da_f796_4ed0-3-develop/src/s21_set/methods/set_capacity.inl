#include "../s21_set.h"

template <typename Key, typename Compare>

inline bool s21::set<Key, Compare>::empty() {
  return m_root == Node::nil();
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::size_type
s21::set<Key, Compare>::size() {
  return count_nodes(m_root);
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::size_type
s21::set<Key, Compare>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename Key, typename Compare>

inline int s21::set<Key, Compare>::count_nodes(Node* node) {
  int count{};
  if (node != Node::nil()) {
    count += count_nodes(node->left);
    count++;
    count += count_nodes(node->right);
  }
  return count;
}