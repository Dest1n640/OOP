#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

void printBinary(int number, int bits);
void printMatrix(int **matrix, int size);
int encodePosition(int row, int col, int size);

int main() {
  int size;

  cout << "Input the size of the desk (power of 2, e.g., 8, 16, 32): ";
  cin >> size;

  // Проверка на степень двойки
  if ((size & (size - 1)) != 0 || size < 2) {
    cout << "Invalid size. Size must be a power of 2 and greater than or equal "
            "to 2."
         << endl;
    return -1;
  }

  // Выделение памяти под двумерный массив
  int **matrix = new int *[size];
  for (int i = 0; i < size; i++) {
    matrix[i] = new int[size];
  }

  // Заполнение матрицы случайными значениями 0 и 1
  srand(time(0)); // Инициализация генератора случайных чисел
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] = rand() % 2;
    }
  }

  printMatrix(matrix, size);

  // Ход тролля
  int troll_number_x, troll_number_y;
  cout << "Troll turn the coin(x, y): ";
  cin >> troll_number_x >> troll_number_y;

  if (troll_number_x < 0 || troll_number_x >= size || troll_number_y < 0 ||
      troll_number_y >= size) {
    cout << "Invalid coordinates. Coordinates must be within the range of the "
            "desk size."
         << endl;
    return -1;
  }

  cout << "Troll chose (" << troll_number_x << ", " << troll_number_y
       << ") cell" << endl;

  int bits = 0;
  int temp_size = size;
  while (temp_size > 0) {
    bits++;
    temp_size >>= 1;
  }
  bits--;

  // Ход первого программиста
  // Кодируем позицию тролля
  int encoded_position = encodePosition(troll_number_x, troll_number_y, size);

  cout << "Encoded position (in binary):" << endl;
  printBinary(encoded_position, bits * 2);

  // Определяем какую клетку перевернуть
  int flip_coin_x = encoded_position / size;
  int flip_coin_y = encoded_position % size;

  cout << "First programmer flips (" << flip_coin_x << ", " << flip_coin_y
       << ") coin" << endl;

  // Переворачиваем клетку, которую закодировал первый программист
  matrix[flip_coin_x][flip_coin_y] ^= 1;

  printMatrix(matrix, size);

  // Ход тролля (переворачиваем монету)
  matrix[troll_number_x][troll_number_y] ^= 1;

  // Ход второго программиста
  // Кодируем позицию, которую перевернул первый программист
  int decoded_position = encodePosition(flip_coin_x, flip_coin_y, size);

  cout << "Decoded position (in binary):" << endl;
  printBinary(decoded_position, bits * 2);

  // Определяем загаданную троллем клетку
  int target_x = decoded_position / size;
  int target_y = decoded_position % size;

  cout << "The second programmer choose coin (" << target_x << ", " << target_y
       << ")" << endl;
  if (target_x == troll_number_x && target_y == troll_number_y)
    cout << "Correct" << endl;
  else
    cout << "Incorrect" << endl;

  // Освобождение памяти
  for (int i = 0; i < size; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;

  return 0;
}

// Определение функций после main
void printBinary(int number, int bits) {
  for (int i = bits - 1; i >= 0; i--) {
    cout << ((number >> i) & 1);
  }
  cout << endl;
}

void printMatrix(int **matrix, int size) {
  cout << "Chessboard:\n";
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      cout << matrix[i][j] << " ";
    }
    cout << "\n";
  }
}

int encodePosition(int row, int col, int size) {
  int bits = 0;
  int temp_size = size;
  while (temp_size > 0) {
    bits++;
    temp_size >>= 1;
  }
  bits--;

  int encoded_position = 0;
  for (int i = bits - 1; i >= 0; i--) {
    encoded_position |= ((row >> (i)) & 1) << (i + bits);
  }
  for (int i = bits - 1; i >= 0; i--) {
    encoded_position |= ((col >> (i)) & 1) << (i);
  }
  return encoded_position;
}
