namespace s21 {

template <typename T>
const T& queue<T>::front() const {
  if (empty()) throw std::out_of_range("Queue is empty");
  return front_->data;
}

template <typename T>
const T& queue<T>::back() const {
  if (empty()) throw std::out_of_range("Queue is empty");
  return back_->data;
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21
