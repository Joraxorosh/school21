#include "../s21_multiset.h"

template <typename Key, typename Compare>

inline typename s21::multiset<Key, Compare>::iterator
s21::multiset<Key, Compare>::find(const Key& key) {
  return multisetIterator(search(m_root, key));
}

template <typename Key, typename Compare>

bool s21::multiset<Key, Compare>::contains(const Key& key) {
  return search(m_root, key) != Node::nil();
}

template <typename Key, typename Compare>

inline typename s21::multiset<Key, Compare>::Node*
s21::multiset<Key, Compare>::search(Node* node, const Key& key)

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