#// CircularList.h
#ifndef CURCULAR_LIST_H
#define CURCULAR_LIST_H
#include <fstream>
#include <iostream>
using namespace std;

class CurcularListException {};

template <class T> class CurcularList;

template <class T> ostream &operator<<(ostream &out, CurcularList<T> &list);

template <class T> class CurcularListElem {
  T data;
  CurcularListElem *next;

public:
  CurcularListElem(const T &adata, CurcularListElem *anext);
  const T &getData() const;
  CurcularListElem *getNext();
  friend class ::CurcularList<T>;
};

template <class T> class CurcularList {
  CurcularListElem<T> *start;
  CurcularListElem<T> *end;
  CurcularList(const CurcularList &list);

public:
  CurcularList();
  ~CurcularList();
  CurcularListElem<T> *getStart();
  void deleteFirst();
  void deleteAfter(CurcularListElem<T> *ptr);
  void insertFirst(const T &data);
  void insertAfter(CurcularListElem<T> *ptr, const T &data);
  friend ostream &operator<< <T>(ostream &out, CurcularList<T> &list);
};

template <class T>
CurcularListElem<T>::CurcularListElem(const T &adata,
                                      CurcularListElem<T> *anext) {
  data = adata;
  next = anext;
}

template <class T> const T &CurcularListElem<T>::getData() const {
  return data;
}

template <class T> CurcularListElem<T> *CurcularListElem<T>::getNext() {
  return next;
}

template <class T> CurcularList<T>::CurcularList() {
  start = 0;
  end = 0;
}

template <class T> CurcularList<T>::~CurcularList() {
  while (start)
    deleteFirst();
}

template <class T> CurcularListElem<T> *CurcularList<T>::getStart() {
  return start;
}

template <class T> void CurcularList<T>::deleteFirst() {
  if (start) {
    CurcularListElem<T> *temp = start;
    if (start == end) {
      start = 0;
      end = 0;
    } else {
      start = start->next;
      end->next = start;
    }
    delete temp;
  } else
    throw CurcularListException();
}

template <class T> void CurcularList<T>::insertFirst(const T &data) {
  CurcularListElem<T> *newElem = new CurcularListElem<T>(data, start);
  if (!start) {
    start = newElem;
    end = newElem;
    end->next = start;
  } else {
    start = newElem;
    end->next = start;
  }
}

template <class T> void CurcularList<T>::deleteAfter(CurcularListElem<T> *ptr) {
  if (ptr && ptr->next) {
    CurcularListElem<T> *temp = ptr->next;
    ptr->next = ptr->next->next;
    if (temp == end) {
      end = ptr;
      end->next = start;
    } else if (temp == start) {
      start = start->next;
      end->next = start;
    }
    delete temp;
  } else {
    throw CurcularListException();
  }
}

template <class T>
void CurcularList<T>::insertAfter(CurcularListElem<T> *ptr, const T &data) {
  if (ptr) {
    CurcularListElem<T> *newElem = new CurcularListElem<T>(data, ptr->next);
    ptr->next = newElem;
    if (ptr == end) {
      end = newElem;
      end->next = start;
    }
  }
}

template <class T> ostream &operator<<(ostream &out, CurcularList<T> &list) {
  if (!list.start) {
    out << "EMPTY ";
  } else {
    CurcularListElem<T> *ptr = list.start;
    do {
      out << ptr->getData() << " ";
      ptr = ptr->getNext();
    } while (ptr != list.start);
  }
  return out;
}
#endif
