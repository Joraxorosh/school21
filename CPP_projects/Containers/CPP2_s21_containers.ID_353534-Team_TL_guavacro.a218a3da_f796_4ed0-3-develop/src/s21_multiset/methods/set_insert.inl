#include "../s21_multiset.h"

template <typename Key, typename Compare>

inline void s21::multiset<Key, Compare>::fix_insert_violations(
    Node* insert_node) {
  while (insert_node->parent->color == RED) {
    if (insert_node->parent == insert_node->parent->parent->left) {
      Node* y = insert_node->parent->parent->right;
      if (y->color == RED) {
        insert_node->parent->color = BLACK;
        y->color = BLACK;
        insert_node->parent->parent->color = RED;
        insert_node = insert_node->parent->parent;
      } else {
        if (insert_node == insert_node->parent->right) {
          insert_node = insert_node->parent;
          left_rotate(insert_node);
        }
        insert_node->parent->color = BLACK;
        insert_node->parent->parent->color = RED;
        right_rotate(insert_node->parent->parent);
      }
    } else {
      Node* y = insert_node->parent->parent->left;
      if (y->color == RED) {
        insert_node->parent->color = BLACK;
        y->color = BLACK;
        insert_node->parent->parent->color = RED;
        insert_node = insert_node->parent->parent;
      } else {
        if (insert_node == insert_node->parent->left) {
          insert_node = insert_node->parent;
          right_rotate(insert_node);
        }
        insert_node->parent->color = BLACK;
        insert_node->parent->parent->color = RED;
        left_rotate(insert_node->parent->parent);
      }
    }
  }
  m_root->color = BLACK;
}

template <typename Key, typename Compare>

inline std::pair<typename s21::multiset<Key, Compare>::iterator, bool>
s21::multiset<Key, Compare>::insert(
    const typename s21::multiset<Key, Compare>::value_type& value) {
  using Node = typename s21::multiset<Key, Compare>::Node;
  Node* insert_node = new Node{value, s21::multiset<Key, Compare>::RED};
  Node* node_to_compare = this->m_root;
  Node* value_parent = Node::nil();
  Compare compare;

  while (node_to_compare != Node::nil()) {
    value_parent = node_to_compare;
    if (compare(insert_node->value, node_to_compare->value)) {
      node_to_compare = node_to_compare->left;
    } else {
      node_to_compare = node_to_compare->right;
    }
  }

  insert_node->parent = value_parent;
  if (value_parent == Node::nil()) {
    this->m_root = insert_node;
  } else if (compare(insert_node->value, value_parent->value)) {
    value_parent->left = insert_node;
  } else {
    value_parent->right = insert_node;
  }
  this->fix_insert_violations(insert_node);

  typename s21::multiset<Key, Compare>::iterator Iterator(insert_node);
  std::pair<typename s21::multiset<Key, Compare>::iterator, bool> returnedPair(
      Iterator, true);

  return returnedPair;
}