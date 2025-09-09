#include "../s21_map.h"

template <typename Key, typename T, typename Compare>

inline std::pair<typename s21::map<Key, T, Compare>::iterator, bool>
s21::map<Key, T, Compare>::insert(
    const typename s21::map<Key, T, Compare>::value_type& value) {
  using Node = typename s21::map<Key, T, Compare>::Node;
  Node* insert_node = new Node{value.first, value.second, RED};
  Node* node_to_compare = this->m_root;
  Node* value_parent = Node::nil();
  Compare compare;

  while (node_to_compare != Node::nil()) {
    if (insert_node->value.first == node_to_compare->value.first) {
      delete insert_node;
      return {iterator(node_to_compare), false};
    }
    value_parent = node_to_compare;
    if (compare(insert_node->value.first, node_to_compare->value.first)) {
      node_to_compare = node_to_compare->left;
    } else {
      node_to_compare = node_to_compare->right;
    }
  }

  insert_node->parent = value_parent;
  if (value_parent == Node::nil()) {
    this->m_root = insert_node;
  } else if (compare(insert_node->value.first, value_parent->value.first)) {
    value_parent->left = insert_node;
  } else {
    value_parent->right = insert_node;
  }
  this->fix_insert_violations(insert_node);
  return {iterator(insert_node), true};
}

template <typename Key, typename T, typename Compare>

inline void s21::map<Key, T, Compare>::fix_insert_violations(
    Node* insert_node) {
  while (insert_node != m_root && insert_node->parent->color == RED) {
    Node* grandparent = insert_node->parent->parent;

    if (insert_node->parent == grandparent->left) {
      Node* uncle = grandparent->right;

      if (uncle != Node::nil() && uncle->color == RED) {
        insert_node->parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        insert_node = grandparent;
      } else {
        if (insert_node == insert_node->parent->right) {
          insert_node = insert_node->parent;
          left_rotate(insert_node);
        }
        insert_node->parent->color = BLACK;
        grandparent->color = RED;
        right_rotate(grandparent);
      }
    } else {
      Node* uncle = grandparent->left;

      if (uncle != Node::nil() && uncle->color == RED) {
        insert_node->parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        insert_node = grandparent;
      } else {
        if (insert_node == insert_node->parent->left) {
          insert_node = insert_node->parent;
          right_rotate(insert_node);
        }
        insert_node->parent->color = BLACK;
        grandparent->color = RED;
        left_rotate(grandparent);
      }
    }
  }
  m_root->color = BLACK;
}

template <typename Key, typename T, typename Compare>

inline std::pair<typename s21::map<Key, T, Compare>::iterator, bool>
s21::map<Key, T, Compare>::insert(const Key& key, const T& obj) {
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename T, typename Compare>

inline std::pair<typename s21::map<Key, T, Compare>::iterator, bool>
s21::map<Key, T, Compare>::insert_or_assign(const Key& key, const T& obj) {
  using Node = typename s21::map<Key, T, Compare>::Node;
  Node* insert_node = new Node{key, obj, RED};
  Node* node_to_compare = this->m_root;
  Node* value_parent = Node::nil();
  Compare compare;

  while (node_to_compare != Node::nil()) {
    if (insert_node->value.first == node_to_compare->value.first) {
      node_to_compare->value.second = insert_node->value.second;
      delete insert_node;
      return {iterator(node_to_compare), true};
    }
    value_parent = node_to_compare;
    if (compare(insert_node->value.first, node_to_compare->value.first)) {
      node_to_compare = node_to_compare->left;
    } else {
      node_to_compare = node_to_compare->right;
    }
  }

  insert_node->parent = value_parent;
  if (value_parent == Node::nil()) {
    this->m_root = insert_node;
  } else if (compare(insert_node->value.first, value_parent->value.first)) {
    value_parent->left = insert_node;
  } else {
    value_parent->right = insert_node;
  }
  this->fix_insert_violations(insert_node);
  return {iterator(insert_node), true};
}