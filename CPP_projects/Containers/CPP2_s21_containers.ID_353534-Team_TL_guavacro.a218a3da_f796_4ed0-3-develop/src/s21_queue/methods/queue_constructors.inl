namespace s21 {

template <typename T>
queue<T>::queue() : front_(nullptr), back_(nullptr), size_(0) {}

template <typename T>
queue<T>::queue(std::initializer_list<T> init) : queue() {
  for (const T& val : init) push(val);
}

template <typename T>
queue<T>::queue(const queue& other) : queue() {
  Node* temp = other.front_;
  while (temp) {
    push(temp->data);
    temp = temp->next;
  }
}

template <typename T>
queue<T>::queue(queue&& other) noexcept
    : front_(other.front_), back_(other.back_), size_(other.size_) {
  other.front_ = nullptr;
  other.back_ = nullptr;
  other.size_ = 0;
}

template <typename T>
queue<T>::~queue() {
  clear();
}

template <typename T>
queue<T>& queue<T>::operator=(const queue& other) {
  if (this != &other) {
    clear();
    Node* temp = other.front_;
    while (temp) {
      push(temp->data);
      temp = temp->next;
    }
  }
  return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue&& other) noexcept {
  if (this != &other) {
    clear();
    front_ = other.front_;
    back_ = other.back_;
    size_ = other.size_;
    other.front_ = nullptr;
    other.back_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

}  // namespace s21
