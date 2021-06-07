#ifndef VECTOR_H
#define VECTOR_H

using uint = unsigned int;

template <class T>
class Vector {
  private:
    T* elements;
    uint _size;
    int capacity;

    void ensureCapacity();
  
  public:
    Vector();
    ~Vector();
    T& operator[](uint i);
    void add(T element);
    const uint size() const;
};

#endif