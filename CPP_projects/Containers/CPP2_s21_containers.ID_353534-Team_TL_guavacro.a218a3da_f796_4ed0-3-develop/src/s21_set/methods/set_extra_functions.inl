#include "../s21_set.h"

template <typename Key, typename Compare>

inline void s21::set<Key, Compare>::print(Node* root) {
  if (root != Node::nil()) {
    print(root->left);
    std::cout << root->value << ' ';
    print(root->right);
  }
}