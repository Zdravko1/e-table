#include "String.h"
#include <stdexcept>
#include <string>

// delete
#include <iostream>
using namespace std;

String::String(const char* buffer) {
  int bufferSize = _strlen(buffer); 
  this->buffer = new char[bufferSize + 1];
  this->_size = bufferSize;

  for (int i = 0; i < _size; i++) {
    this->buffer[i] = buffer[i];
  }

  this->buffer[_size] = '\0'; 
}

String::String(const String &other) {
  if (buffer != nullptr)
    delete[] buffer;

  _size = other._size;
  buffer = new char[other._size + 1];

  for (int i = 0; i < _size; i++) {
    buffer[i] = other.buffer[i];
  }

  buffer[_size] = '\0'; 
}

String::~String() {
  _size = 0;
  delete[] buffer;
}

String& String::operator= (const String &other) {
  if (this == &other)
    return *this;
  
  if (buffer != nullptr)
    delete[] buffer;

  buffer = new char[other._size + 1];
  _size = other._size;

  for (int i = 0; i < _size; i++) {
    buffer[i] = other.buffer[i];
  }

  buffer[_size] = '\0'; 

  return *this;
}

bool String::operator== (const String &other) {
  if (_size != other.size())
    return false;
  
  for (int i = 0; i < _size; i++) {
    if (buffer[i] != other.buffer[i]) {
      return false;
    }
  }

  return true;
}

String& String::operator+= (const String &other) {
  char* newBuffer = new char[_size + other._size + 1];
  
  int newBufferIdx = 0;
  for (int i = 0; i < _size; i++) {
    newBuffer[newBufferIdx++] = buffer[i];
  }

  for (int i = 0; i < other._size; i++) {
    newBuffer[newBufferIdx++] = other.buffer[i];
  }

  newBuffer[_size + other._size + 1] = '\0';

  delete[] buffer;

  buffer = newBuffer;
  _size = _size + other._size;

  return *this;
}

char& String::operator[] (uint index) {
  if (index < _size) {
    return buffer[index];
  } else {
    throw std::invalid_argument("Index out of bounds.");
  }
}

const char& String::operator[] (uint index) const {
  if (index < _size) {
    return buffer[index];
  } else {
    throw std::invalid_argument("Index out of bounds.");
  }
}

std::ostream& operator<<(std::ostream &os, const String &string) {
  return os << string.c_str();
}

const uint String::size() const {
  return _size;
}

const char* String::c_str() const {
  return buffer;
}

uint String::_strlen(const char* str) {
  uint len = 0;
  int i = 0;

  while (str[i++] != '\0')
    len++;

  return len;
}

bool equal(const String &first, const String &second) {
  if (first.size() != second.size())
    return false;
  
  for (int i = 0; i < first.size(); i++) {
    if (first[i] != second[i]) {
      return false;
    }
  }

  return true;
}

String String::toString(double number) {
  // TODO do it without std::to_string
  return String(std::to_string(number).c_str());
}