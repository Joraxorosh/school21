template <typename T, size_t N>
inline typename s21::array<T, N>::reference s21::array<T, N>::at(
    typename array<T, N>::size_type pos) {
  if (pos >= m_size) throw std::out_of_range("Inex is out of range");

  return m_array[pos];
}

template <typename T, size_t N>
inline typename s21::array<T, N>::reference s21::array<T, N>::operator[](
    typename array<T, N>::size_type pos) {
  return m_array[pos];
}

template <typename T, size_t N>
inline typename s21::array<T, N>::const_reference s21::array<T, N>::front() {
  return m_array[0];
}

template <typename T, size_t N>
inline typename s21::array<T, N>::const_reference s21::array<T, N>::back() {
  return m_array[m_size - 1];
}

template <typename T, size_t N>
inline typename s21::array<T, N>::iterator s21::array<T, N>::data() {
  return m_array;
}