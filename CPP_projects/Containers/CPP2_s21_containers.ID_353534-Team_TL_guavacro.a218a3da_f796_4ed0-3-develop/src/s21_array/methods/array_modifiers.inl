template <typename T, size_t N>

inline void s21::array<T, N>::swap(array<T, N>& other) {
  array buffer{other};
  other = *this;
  *this = buffer;
}

template <typename T, size_t N>

inline void s21::array<T, N>::fill(
    typename array<T, N>::const_reference value) {
  std::fill(m_array, m_array + N, value);
}