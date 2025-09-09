template <typename T, size_t N>

inline bool s21::array<T, N>::empty() {
  return N == 0;
}

template <typename T, size_t N>

inline typename s21::array<T, N>::size_type s21::array<T, N>::size() {
  return N;
}

template <typename T, size_t N>

inline typename s21::array<T, N>::size_type s21::array<T, N>::max_size() {
  return N;
}