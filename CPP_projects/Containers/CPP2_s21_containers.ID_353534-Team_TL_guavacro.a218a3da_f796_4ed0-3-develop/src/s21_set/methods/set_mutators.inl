#include "../s21_set.h"

template <typename Key, typename Compare>

inline typename s21::set<Key, Compare>::Node* s21::set<Key, Compare>::get()
    const {
  return m_root;
}