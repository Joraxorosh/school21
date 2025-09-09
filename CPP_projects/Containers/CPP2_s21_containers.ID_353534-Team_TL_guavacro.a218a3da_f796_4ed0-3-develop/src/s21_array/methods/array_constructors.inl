template <typename T, std::size_t N>
inline s21::array<T, N>::array(std::initializer_list<T> list) {
  if (list.size() > N)
    throw std::invalid_argument(
        "Initializer list cannot be longer than initialized array");
  std::copy(list.begin(), list.end(), m_array);
}

template <typename T, std::size_t N>
inline s21::array<T, N>::array(const array& other) : m_size{other.m_size} {
  std::copy(other.m_array, other.m_array + N, m_array);
}

template <typename T, std::size_t N>
inline s21::array<T, N>& s21::array<T, N>::operator=(const array& other) {
  if (this != &other) {
    if (other.m_size != m_size)
      throw std::invalid_argument("Cannot copy an array of different size");
    std::copy(other.m_array, other.m_array + N, m_array);
  }
  return *this;
}

template <typename T, std::size_t N>
inline s21::array<T, N>::array(array&& other) noexcept : m_size{other.m_size} {
  std::copy(other.m_array, other.m_array + N, m_array);
  std::fill(other.m_array, other.m_array + N, T{});
  other.m_size = 0;
}

template <typename T, std::size_t N>
inline s21::array<T, N>& s21::array<T, N>::operator=(array&& other) noexcept {
  if (this != &other) {
    if (other.m_size != m_size)
      throw std::invalid_argument("Cannot move an array of different size");
    std::copy(other.m_array, other.m_array + N, m_array);
    std::fill(other.m_array, other.m_array + N, T{});
    other.m_size = 0;
  }
  return *this;
}