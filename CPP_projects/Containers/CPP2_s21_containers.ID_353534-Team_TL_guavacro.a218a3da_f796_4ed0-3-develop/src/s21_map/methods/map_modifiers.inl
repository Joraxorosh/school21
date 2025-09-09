
#include "../s21_map.h"

template <typename Key, typename T, typename Compare>

inline void s21::map<Key, T, Compare>::clear() {
  delete_tree(m_root);
  m_root = Node::nil();
}

template <typename Key, typename T, typename Compare>

inline void s21::map<Key, T, Compare>::swap(map& other) {
  Node* temporary{m_root};
  m_root = other.m_root;
  other.m_root = temporary;
}

template <typename Key, typename T, typename Compare>

inline void s21::map<Key, T, Compare>::merge(map& other) {
  for (auto it = other.begin(); it != other.end();) {
    if (!contains(it->first)) {
      insert(*it);
      other.erase(it++);
    } else {
      ++it;
    }
  }
}
