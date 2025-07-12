#include "./h/array.h"
#include <iostream>
using namespace std;

void task(int N, int k);

int main(void) {
  try {
    Array arr(4);
    for (int i = 0; i < 4; i++)
      arr.insert(i + 1);
    cout << arr << endl;
    for (int i = 0; i < 8; i += 2)
      arr.insert(10 + i, i);
    cout << arr << endl;
    for (int i = 1; i < 8; i += 2)
      arr[i] = 20 + i;
    cout << arr << endl;
    for (int i = 6; i >= 0; i -= 3)
      arr.remove(i);
    cout << arr << endl;
  } catch (const ArrayException &e) {
    cout << "ArrayException!" << endl;
  }

  int k, N;
  cout << "Input the k: ";
  cin >> k;
  cout << "Input the N: ";
  cin >> N;
  cout << "The result of the the task:" << '\n';
  task(N, k);
  cout << "The programm is finish" << endl;
  return 0;
}

void task(int N, int k) {
  Array arr(N);
  for (int i = 0; i < N; i++)
    arr.insert(i);
  int index = 0;
  for (int i = arr.getSize(); i > 1; i--) {
    index = (index + k - 1) % arr.getSize();
    arr.remove(index);
    std::cout << "\t" << "Total size: " << arr.getSize() << std::endl;
    std::cout << "\t" << arr << std::endl;
  }
  return;
}
