#include "../s21_multiset.h"

template <typename Key, typename Compare>

inline typename s21::multiset<Key, Compare>::Node*
s21::multiset<Key, Compare>::get() const {
  return m_root;
}