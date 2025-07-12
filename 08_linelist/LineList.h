#ifndef LINE_LIST_H
#define LINE_LIST_H

#include <iostream>

class LineListException {};

template <class T> class LineListElem {
  T data;
  LineListElem *next;

public:
  LineListElem(const T &adata, LineListElem *anext);
  const T &getData() const;
  LineListElem *getNext();
  template <class U> friend class LineList;
};

template <class T> class LineList {
  LineListElem<T> *start;

public:
  LineList();
  ~LineList();
  LineListElem<T> *getStart();
  void deleteFirst();
  void deleteAfter(LineListElem<T> *ptr);
  void insertFirst(const T &data);
  void insertAfter(LineListElem<T> *ptr, const T &data);
  void clear();
  int getSize() const;
  template <class U>
  friend std::ostream &operator<<(std::ostream &out, const LineList<U> &list);
};

// LineListElem
template <class T>
LineListElem<T>::LineListElem(const T &adata, LineListElem<T> *anext)
    : data(adata), next(anext) {}

template <class T> const T &LineListElem<T>::getData() const { return data; }

template <class T> LineListElem<T> *LineListElem<T>::getNext() { return next; }

// Linelist

template <class T> LineList<T>::LineList() : start(nullptr) {}

template <class T> LineList<T>::~LineList() { clear(); }

template <class T> LineListElem<T> *LineList<T>::getStart() { return start; }

template <class T> void LineList<T>::deleteFirst() {
  if (start) {
    LineListElem<T> *temp = start->next;
    delete start;
    start = temp;
  } else {
    throw LineListException();
  }
}

template <class T> void LineList<T>::insertFirst(const T &data) {
  start = new LineListElem<T>(data, start);
}

template <class T> void LineList<T>::deleteAfter(LineListElem<T> *ptr) {
  if (ptr && ptr->next) {
    LineListElem<T> *temp = ptr->next;
    ptr->next = ptr->next->next;
    delete temp;
  } else {
    throw LineListException();
  }
}

template <class T>
void LineList<T>::insertAfter(LineListElem<T> *ptr, const T &data) {
  if (ptr) {
    ptr->next = new LineListElem<T>(data, ptr->next);
  }
}

template <class T> void LineList<T>::clear() {
  while (start) {
    deleteFirst();
  }
}

template <class T> int LineList<T>::getSize() const {
  int amount = 0;
  LineListElem<T> *it = start;
  while (it) {
    amount++;
    it = it->getNext();
  }
  return amount;
}

template <class T>
std::ostream &operator<<(std::ostream &out, const LineList<T> &list) {
  LineListElem<T> *ptr = list.start;
  if (!ptr) {
    out << "EMPTY ";
  } else {
    while (ptr) {
      out << ptr->getData() << ' ';
      ptr = ptr->getNext();
    }
  }
  return out;
}

#endif
