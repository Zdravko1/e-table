#include "Vector.h"
#include <stdexcept>

template <class T>
Vector<T>::Vector() {
  capacity = 16;
  _size = 0;
  elements = new T[capacity];
}

template <class T>
Vector<T>::~Vector() {
  delete[] elements;
}

template <class T>
T& Vector<T>::operator[](uint index) {
    if (index < _size) {
    return elements[index];
  } else {
    throw std::invalid_argument("Index out of bounds.");
  }
}

template <class T>
void Vector<T>::add(T element) {
  ensureCapacity();
  elements[_size++] = element;
}

template <class T>
const uint Vector<T>::size() const {
  return _size;
}

template <class T>
void Vector<T>::ensureCapacity() {
  if (_size < capacity) {
    return;
  }

  capacity *= 2;
  T* newElements = new T[capacity];

  for (int i = 0; i < _size; i++) {
    newElements[i] = elements[i];
  }

  delete[] elements;

  elements = newElements;
}