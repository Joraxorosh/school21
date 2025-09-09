#include "../s21_multiset.h"

template <typename Key, typename Compare>

inline s21::multiset<Key, Compare>::multiset(const multiset& s) {
  m_root = Node::nil();
  copy_tree(s.m_root);
}

template <typename Key, typename Compare>

inline s21::multiset<Key, Compare>::multiset(
    std::initializer_list<
        typename s21::multiset<Key, Compare>::value_type> const& items) {
  for (const auto& item : items) {
    this->insert(item);
  }
}

template <typename Key, typename Compare>

inline s21::multiset<Key, Compare>::multiset(multiset&& s) {
  m_root = s.m_root;
  s.m_root = Node::nil();
}

template <typename Key, typename Compare>

inline s21::multiset<Key, Compare>& s21::multiset<Key, Compare>::operator=(
    multiset&& s) {
  if (this != &s) {
    delete_tree(m_root);
    m_root = s.m_root;
    s.m_root = Node::nil();
  }
  return *this;
}

template <typename Key, typename Compare>

inline s21::multiset<Key, Compare>::~multiset() {
  delete_tree(m_root);
}

template <typename Key, typename Compare>

inline void s21::multiset<Key, Compare>::delete_tree(Node* node) {
  if (node != Node::nil()) {
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
  }
}

template <typename Key, typename Compare>
inline void s21::multiset<Key, Compare>::copy_tree(Node* node) {
  if (node != Node::nil()) {
    copy_tree(node->left);
    this->insert(node->value);
    copy_tree(node->right);
  }
}