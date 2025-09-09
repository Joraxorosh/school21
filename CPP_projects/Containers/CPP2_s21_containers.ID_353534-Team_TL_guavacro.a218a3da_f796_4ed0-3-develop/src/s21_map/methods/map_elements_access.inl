#include "../s21_map.h"

template <typename Key, typename T, typename Compare>

inline T& s21::map<Key, T, Compare>::at(const Key& key) {
  mapIterator it = find(key);
  if (it.current_node == Node::nil()) throw std::out_of_range("Invalid key");
  return it.current_node->value.second;
}

template <typename Key, typename T, typename Compare>

inline T& s21::map<Key, T, Compare>::operator[](const Key& key) {
  mapIterator it = find(key);
  if (it.current_node == Node::nil()) {
    auto [new_it, _] = insert({key, T{}});
    return new_it.current_node->value.second;
  }
  return it.current_node->value.second;
}

template <typename Key, typename T, typename Compare>

inline typename s21::map<Key, T, Compare>::iterator
s21::map<Key, T, Compare>::find(const Key& key) {
  return mapIterator(search(m_root, key));
}

template <typename Key, typename T, typename Compare>

bool s21::map<Key, T, Compare>::contains(const Key& key) {
  return search(m_root, key) != Node::nil();
}

template <typename Key, typename T, typename Compare>

inline typename s21::map<Key, T, Compare>::Node*
s21::map<Key, T, Compare>::search(Node* node, const Key& key)

{
  Compare compare;
  while (node != Node::nil()) {
    if (compare(key, node->value.first)) {
      node = node->left;
    } else if (compare(node->value.first, key)) {
      node = node->right;
    } else {
      return node;
    }
  }
  return Node::nil();
}
