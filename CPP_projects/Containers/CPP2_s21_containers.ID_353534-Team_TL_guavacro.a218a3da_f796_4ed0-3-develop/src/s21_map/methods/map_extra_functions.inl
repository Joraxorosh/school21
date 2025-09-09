template <typename Key, typename T, typename Compare>
inline void s21::map<Key, T, Compare>::print(Node* root) {
  if (root != Node::nil()) {
    print(root->left);
    std::cout << root->value.first << ":" << root->value.second << " ";
    print(root->right);
  }
}