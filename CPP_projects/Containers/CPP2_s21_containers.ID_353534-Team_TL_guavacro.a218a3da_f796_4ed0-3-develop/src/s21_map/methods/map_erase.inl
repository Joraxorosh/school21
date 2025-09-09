#include "../s21_map.h"

template <typename Key, typename T, typename Compare>
inline void s21::map<Key, T, Compare>::erase(mapIterator pos) {
  Node* y = pos.current_node;
  Node* x = Node::nil();
  int original_color = pos.current_node->color;
  if (pos.current_node->left == Node::nil()) {
    x = pos.current_node->right;
    node_transplant(pos.current_node, pos.current_node->right);
  } else if (pos.current_node->right == Node::nil()) {
    x = pos.current_node->left;
    node_transplant(pos.current_node, pos.current_node->left);
  } else {
    y = minimum(pos.current_node->right);
    original_color = y->color;
    x = y->right;
    if (y != pos.current_node->right) {
      node_transplant(y, y->right);
      y->right = pos.current_node->right;
      y->right->parent = y;
    } else {
      x->parent = y;
    }
    node_transplant(pos.current_node, y);
    y->left = pos.current_node->left;
    y->left->parent = y;
    y->color = pos.current_node->color;
  }
  if (original_color == BLACK) {
    fix_delete_violations(x);
  }
  if (y != pos.current_node)
    delete pos.current_node;
  else if (y != Node::nil())
    delete y;
}

template <typename Key, typename T, typename Compare>

inline void s21::map<Key, T, Compare>::node_transplant(Node* old_node,
                                                       Node* new_node) {
  if (old_node->parent == Node::nil())
    m_root = new_node;
  else if (old_node == old_node->parent->left)
    old_node->parent->left = new_node;
  else
    old_node->parent->right = new_node;
  new_node->parent = old_node->parent;
}

template <typename Key, typename T, typename Compare>

inline typename s21::map<Key, T, Compare>::Node*
s21::map<Key, T, Compare>::minimum(Node* node) {
  while (node->left != Node::nil()) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T, typename Compare>

void s21::map<Key, T, Compare>::fix_delete_violations(Node* new_node) {
  while (new_node != m_root and new_node->color == BLACK) {
    if (new_node == new_node->parent->left) {
      Node* new_node_sibling = new_node->parent->right;
      if (new_node_sibling->color == RED) {
        new_node_sibling->color = BLACK;
        new_node->color = RED;
        left_rotate(new_node->parent);
        new_node_sibling = new_node->parent->right;
      }
      if (new_node_sibling->left->color == BLACK &&
          new_node_sibling->right->color == BLACK) {
        new_node_sibling->color = RED;
        new_node = new_node->parent;
      } else {
        if (new_node_sibling->color == BLACK) {
          new_node_sibling->left->color = BLACK;
          new_node_sibling->color = RED;
          right_rotate(new_node_sibling);
          new_node_sibling = new_node->parent->right;
        }
        new_node->color = new_node->parent->color;
        new_node->parent->color = BLACK;
        new_node_sibling->right->color = BLACK;
        left_rotate(new_node->parent);
        new_node = m_root;
      }
    } else {
      Node* new_node_sibling = new_node->parent->left;
      if (new_node_sibling->color == RED) {
        new_node_sibling->color = BLACK;
        new_node->color = RED;
        right_rotate(new_node->parent);
        new_node_sibling = new_node->parent->left;
      }
      if (new_node_sibling->right->color == BLACK &&
          new_node_sibling->left->color == BLACK) {
        new_node_sibling->color = RED;
        new_node = new_node->parent;
      } else {
        if (new_node_sibling->color == BLACK) {
          new_node_sibling->right->color = BLACK;
          new_node_sibling->color = RED;
          left_rotate(new_node_sibling);
          new_node_sibling = new_node->parent->left;
        }
        new_node->color = new_node->parent->color;
        new_node->parent->color = BLACK;
        new_node_sibling->left->color = BLACK;
        right_rotate(new_node->parent);
        new_node = m_root;
      }
    }
  }
}
