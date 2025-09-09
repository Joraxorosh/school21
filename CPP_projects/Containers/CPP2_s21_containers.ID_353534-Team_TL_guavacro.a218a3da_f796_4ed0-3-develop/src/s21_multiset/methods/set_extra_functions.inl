#include "../s21_multiset.h"

template <typename Key, typename Compare>

inline void s21::multiset<Key, Compare>::print(Node* root) {
  if (root != Node::nil()) {
    print(root->left);
    std::cout << root->value << ' ';
    print(root->right);
  }
}