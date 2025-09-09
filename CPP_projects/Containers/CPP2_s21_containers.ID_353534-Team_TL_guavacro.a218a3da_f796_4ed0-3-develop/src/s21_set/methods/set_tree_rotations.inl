#include "../s21_set.h"

template <typename Key, typename Compare>

inline void s21::set<Key, Compare>::left_rotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != Node::nil()) y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == Node::nil())
    this->m_root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename Key, typename Compare>

inline void s21::set<Key, Compare>::right_rotate(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  if (y->right != Node::nil()) y->right->parent = x;
  y->parent = x->parent;
  if (x->parent == Node::nil())
    this->m_root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->right = x;
  x->parent = y;
}
