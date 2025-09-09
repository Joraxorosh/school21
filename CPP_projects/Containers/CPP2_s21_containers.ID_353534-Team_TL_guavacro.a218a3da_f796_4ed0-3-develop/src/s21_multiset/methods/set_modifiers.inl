#include "../s21_multiset.h"

template <typename Key, typename Compare>

inline void s21::multiset<Key, Compare>::clear() {
  delete_tree(m_root);
  m_root = Node::nil();
}

template <typename Key, typename Compare>

inline void s21::multiset<Key, Compare>::swap(multiset& other) {
  Node* temporary{m_root};
  m_root = other.m_root;
  other.m_root = temporary;
}

template <typename Key, typename Compare>

inline void s21::multiset<Key, Compare>::merge(multiset& other) {
  merge_node(other.m_root);
  delete_tree(other.m_root);
  other.m_root = Node::nil();
}

template <typename Key, typename Compare>

inline void s21::multiset<Key, Compare>::merge_node(Node* node) {
  if (node != Node::nil()) {
    merge_node(node->left);
    insert(node->value);
    merge_node(node->right);
  }
}