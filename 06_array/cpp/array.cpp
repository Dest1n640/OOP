#include "../h/array.h"
#include <iostream>

Array::Array(int startCapacity) : size(0) {
  if (startCapacity <= 0) {
    capacity = DEFAULT_CAPACITY;
  } else {
    capacity = startCapacity;
  }
  ptr = new int[capacity];
}

Array::~Array() { delete[] ptr; }

Array::Array(const Array &arr) : size(arr.size), capacity(arr.capacity) {
  ptr = new int[capacity];
  for (int i = 0; i < size; ++i) {
    ptr[i] = arr.ptr[i];
  }
}

Array &Array::operator=(const Array &arr) {
  if (this == &arr) {
    return *this;
  }
  if (capacity != arr.capacity) {
    delete[] ptr;
    capacity = arr.capacity;
    ptr = new int[capacity];
  }
  size = arr.size;
  for (int i = 0; i < size; ++i) {
    ptr[i] = arr.ptr[i];
  }
  return *this;
}

int &Array::operator[](int index) {
  if (index < 0 || index >= size) {
    throw ArrayException();
  }
  return ptr[index];
}

void Array::increaseCapacity(int newCapacity) {
  capacity = newCapacity < capacity * 2 ? capacity * 2 : newCapacity;
  int *newPtr = new int[capacity];
  for (int i = 0; i < size; ++i) {
    newPtr[i] = ptr[i];
  }
  delete[] ptr;
  ptr = newPtr;
}

void Array::insert(int elem, int index) {
  if (index < 0 || index > size) {
    throw ArrayException();
  }
  if (size == capacity) {
    increaseCapacity(size + 1);
  }
  for (int j = size - 1; j >= index; --j) {
    ptr[j + 1] = ptr[j];
  }
  size++;
  ptr[index] = elem;
}

void Array::insert(int elem) { insert(elem, size); }

void Array::remove(int index) {
  if (index < 0 || index >= size) {
    throw ArrayException();
  }
  for (int j = index; j < size - 1; ++j) {
    ptr[j] = ptr[j + 1];
  }
  if (size > 0) {
    ptr[size - 1] = 0;
  }
  size--;
}

int Array::getSize() const { return size; }

std::ostream &operator<<(std::ostream &out, const Array &arr) {
  out << std::endl;
  out << "Total size: " << arr.size << std::endl;
  out << "[";
  for (int i = 0; i < arr.size; ++i) {
    out << arr.ptr[i];
    if (i < arr.size - 1) {
      out << ", ";
    }
  }
  out << "]";
  out << std::endl;
  return out;
}
