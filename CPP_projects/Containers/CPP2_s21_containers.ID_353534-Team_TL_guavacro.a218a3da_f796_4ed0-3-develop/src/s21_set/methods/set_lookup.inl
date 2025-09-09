#include "../s21_set.h"

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::iterator s21::set<Key, Compare>::find(
    const Key& key) {
  return setIterator(search(m_root, key));
}

template <typename Key, typename Compare>

bool s21::set<Key, Compare>::contains(const Key& key) {
  return search(m_root, key) != Node::nil();
}

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::Node* s21::set<Key, Compare>::search(
    Node* node, const Key& key)

{
  Compare compare;
  while (node != Node::nil()) {
    if (compare(key, node->value)) {
      node = node->left;
    } else if (compare(node->value, key)) {
      node = node->right;
    } else {
      return node;
    }
  }
  return Node::nil();
}