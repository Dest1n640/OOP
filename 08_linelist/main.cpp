// main.cpp
#include "CircularList.h"
#include "LineList.h"
#include <iostream>

void LineList_task(int N, int k);
void CurcularList_task(int N, int k);

int main() {
  int N, k;

  std::cout << "--- Josephus Problem ---" << std::endl;
  std::cout << "Input the number of people (N): ";
  std::cin >> N;
  std::cout << "Input the step size (k): ";
  std::cin >> k;
  std::cout << std::endl;

  if (N <= 0 || k <= 0) {
    std::cerr << "Error: N and k must be positive integers." << std::endl;
    return 1;
  }

  std::cout << "--- LineList Task ---" << std::endl;
  LineList_task(N, k);
  std::cout << "--- End of LineList Task ---" << std::endl << std::endl;

  std::cout << "--- CurcularList Task ---" << std::endl;
  CurcularList_task(N, k);
  std::cout << "--- End of CurcularList Task ---" << std::endl << std::endl;

  std::cout << "--- Program execution completed ---" << std::endl;
  return 0;
}

void LineList_task(int N, int k) {
  std::cout << "Realization of LineList as CircularList" << std::endl;
  LineList<int> arr;

  for (int i = N; i >= 1; --i)
    arr.insertFirst(i);

  LineListElem<int> *current = arr.getStart();
  if (!current) {
    std::cout << "Initial LineList is empty." << std::endl;
    return;
  }
  std::cout << "Initial LineList: " << arr << std::endl;

  int elimination_step = 1;
  while (arr.getSize() > 1) {
    std::cout << "\n--- Elimination Step " << elimination_step++ << " ---"
              << std::endl;
    for (int step = 1; step < k; ++step) {
      if (current->getNext()) {
        current = current->getNext();
      } else {
        current = arr.getStart();
      }
    }
    LineListElem<int> *toDelete = current->getNext();
    if (!toDelete) {
      toDelete = arr.getStart();
      std::cout << "Person to be eliminated (LineList): " << toDelete->getData()
                << std::endl;
      arr.deleteFirst();
      current = arr.getStart();
      if (!current)
        break;
    } else {
      std::cout << "Person to be eliminated (LineList): " << toDelete->getData()
                << std::endl;
      arr.deleteAfter(current);
      current = current->getNext();
      if (!current)
        current = arr.getStart();
    }
    std::cout << "LineList after elimination: " << arr << std::endl;
  }
  std::cout << "\n--- Final Result (LineList) ---" << std::endl;
  std::cout << "The last survivor in LineList is: " << arr << std::endl;
}

void CurcularList_task(int N, int k) {
  std::cout << "Realization of CurcularList" << std::endl;
  if (N <= 0) {
    std::cout << "No survivors in an empty circle." << std::endl;
    return;
  }
  if (k <= 0) {
    std::cout << "Invalid step size k." << std::endl;
    return;
  }

  CurcularList<int> list;
  for (int i = 1; i <= N; ++i) {
    list.insertFirst(i);
  }

  if (N == 1) {
    std::cout << "Initial CurcularList: " << list << std::endl;
    std::cout << "\n--- Final Result (CurcularList) ---" << std::endl;
    std::cout << "Survivor in CurcularList: " << list << std::endl;
    return;
  }

  CurcularListElem<int> *current = list.getStart();
  std::cout << "Initial CurcularList: " << list << std::endl;
  int elimination_step = 1;
  while (current->getNext() != current) {
    std::cout << "\n--- Elimination Step " << elimination_step++ << " ---"
              << std::endl;
    for (int i = 1; i < k; ++i) {
      current = current->getNext();
    }
    CurcularListElem<int> *toDelete = current->getNext();
    std::cout << "Person to be eliminated (CurcularList): "
              << toDelete->getData() << std::endl;
    try {
      list.deleteAfter(current);
      current = current->getNext();
    } catch (CurcularListException &e) {
      std::cerr << "Error during deletion." << std::endl;
      return;
    }
    std::cout << "CurcularList after elimination: " << list << std::endl;
  }

  std::cout << "\n--- Final Result (CurcularList) ---" << std::endl;
  std::cout << "Survivor in CurcularList: " << list << std::endl;
}
