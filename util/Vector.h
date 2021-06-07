#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

using uint = unsigned int;

template <class T>
class Vector {
  private:
    T* elements = nullptr;
    uint _size;
    uint capacity;

    void ensureCapacity() {
      if (_size < capacity)
        return;

      capacity *= 2;
      T* newElements = new T[capacity];

      for (int i = 0; i < _size; i++) {
        newElements[i] = elements[i];
      }

      delete[] elements;

      elements = newElements;
    }
  
  public:
    Vector() {
      capacity = 16;
      _size = 0;
      elements = new T[capacity];
    }

    Vector(const Vector &other) {
      _size = other._size;
      capacity = other.capacity;

      if (elements != nullptr)
        delete[] elements;

      elements = new T[capacity];

      for (int i = 0; i < _size; i++) {
        elements[i] = other.elements[i];
      }
    }

    ~Vector() {
      if (elements != nullptr)
        delete[] elements;
    }

    T& operator[](uint index) {
      if (index < _size) {
        return elements[index];
      } else {
        throw std::invalid_argument("Index out of bounds.");
      }
    }
    
    const T& operator[](uint index) const {
      if (index < _size) {
        return elements[index];
      } else {
        throw std::invalid_argument("Index out of bounds.");
      }
    }

    Vector& operator= (const Vector &other) {
      if (this == &other)
        return *this;

      if (elements != nullptr)
        delete[] elements;

      capacity = other.capacity;
      _size = other._size;
      elements = new T[capacity];

      for (int i = 0; i < _size; i++)
        elements[i] = other.elements[i];
      
      return *this;
    }

    void add(T element) {
      ensureCapacity();
      elements[_size++] = element;
    }

    const uint size() const {
      return _size;
    }

    void clear() {
      capacity = 16;
      _size = 0;
      if (elements != nullptr)
        delete[] elements;
    }
};

#endif