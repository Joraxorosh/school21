#include "../s21_map.h"

template <typename Key, typename T, typename Compare>

inline typename s21::map<Key, T, Compare>::Node*
s21::map<Key, T, Compare>::get() const {
  return m_root;
}
