template <typename T, size_t N>

inline typename s21::array<T, N>::iterator s21::array<T, N>::begin() {
  return data();
}

template <typename T, size_t N>

inline typename s21::array<T, N>::iterator s21::array<T, N>::end() {
  return data() + m_size - 1;
}