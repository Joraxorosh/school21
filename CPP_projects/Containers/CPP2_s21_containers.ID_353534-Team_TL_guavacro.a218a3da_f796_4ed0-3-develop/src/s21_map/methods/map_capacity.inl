#include "../s21_map.h"

template <typename Key, typename T, typename Compare>

inline bool s21::map<Key, T, Compare>::empty() {
  return m_root == Node::nil();
}

template <typename Key, typename T, typename Compare>

inline typename s21::map<Key, T, Compare>::size_type
s21::map<Key, T, Compare>::size() {
  return count_nodes(m_root);
}

template <typename Key, typename T, typename Compare>

inline typename s21::map<Key, T, Compare>::size_type
s21::map<Key, T, Compare>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename Key, typename T, typename Compare>

inline int s21::map<Key, T, Compare>::count_nodes(Node* node) {
  int count{};
  if (node != Node::nil()) {
    count += count_nodes(node->left);
    count++;
    count += count_nodes(node->right);
  }
  return count;
}
