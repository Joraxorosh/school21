namespace s21 {

template <typename T>
bool queue<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
size_t queue<T>::size() const noexcept {
  return size_;
}

}  // namespace s21
