#include "../s21_multiset.h"

template <typename Key, typename Compare>

inline bool s21::multiset<Key, Compare>::empty() {
  return m_root == Node::nil();
}

template <typename Key, typename Compare>

inline typename s21::multiset<Key, Compare>::size_type
s21::multiset<Key, Compare>::size() {
  return count_nodes(m_root);
}

template <typename Key, typename Compare>

inline typename s21::multiset<Key, Compare>::size_type
s21::multiset<Key, Compare>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename Key, typename Compare>

inline int s21::multiset<Key, Compare>::count_nodes(Node* node) {
  int count{};
  if (node != Node::nil()) {
    count += count_nodes(node->left);
    count++;
    count += count_nodes(node->right);
  }
  return count;
}