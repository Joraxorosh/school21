namespace s21 {

template <typename T>
void queue<T>::push(const T& value) {
  Node* node = new Node(value);
  if (empty()) {
    front_ = back_ = node;
  } else {
    back_->next = node;
    back_ = node;
  }
  ++size_;
}

template <typename T>
void queue<T>::push(T&& value) {
  Node* node = new Node(std::move(value));
  if (empty()) {
    front_ = back_ = node;
  } else {
    back_->next = node;
    back_ = node;
  }
  ++size_;
}

template <typename T>
void queue<T>::pop() {
  if (empty()) throw std::out_of_range("Queue is empty");
  Node* temp = front_;
  front_ = front_->next;
  delete temp;
  --size_;
  if (!front_) back_ = nullptr;
}

template <typename T>
void queue<T>::clear() {
  while (!empty()) pop();
}

template <typename T>
void queue<T>::swap(queue& other) noexcept {
  std::swap(front_, other.front_);
  std::swap(back_, other.back_);
  std::swap(size_, other.size_);
}

}  // namespace s21
