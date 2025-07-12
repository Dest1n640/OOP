#include "../h/difficult.h"
#include <algorithm> //либо так либо написать свой shuffle
#include <random>
#include <vector>

PuzzleGenerator::PuzzleGenerator(Difficult d) : level(d) {}

Board PuzzleGenerator::generate(int size) {
  Board board(size);

  // Инициализируем генератор случайных чисел
  std::mt19937 rng(std::random_device{}());

  // Заполняем поле допустимыми значениями (полное решение)
  fillGrid(board, 0, 0, rng);

  // Вычисляем количество подсказок в зависимости от уровня
  int total = size * size;
  int clues;
  switch (level) {
  case Difficult::Easy:
    clues = total * 4 / 5; // 80% ячеек
    break;
  case Difficult::Medium:
    clues = total * 3 / 5; // 60% ячеек
    break;
  case Difficult::Hard:
    clues = total * 2 / 5; // 40% ячеек
    break;
  }

  int removeCount = total - clues;
  removeCells(board, removeCount, rng);

  return board;
}

// Рекурсивная функция заполнения поля
bool PuzzleGenerator::fillGrid(Board &board, int row, int col,
                               std::mt19937 &rng) {
  int n = board.getSize();

  // Базовый случай: прошли все строки — поле заполнено
  if (row == n)
    return true;

  // Переход к следующей ячейке
  int nextRow = (col + 1 == n) ? row + 1 : row;
  int nextCol = (col + 1 == n) ? 0 : col + 1;

  // Список значений от 1 до n, в случайном порядке
  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i)
    nums[i] = i + 1;
  std::shuffle(nums.begin(), nums.end(), rng);

  for (int v : nums) {
    if (board.isValidMove(row, col, v)) {
      board.setCell(row, col, v);
      if (fillGrid(board, nextRow, nextCol, rng))
        return true;
      board.setCell(row, col, 0);
    }
  }
  return false;
}

// Удаляет заданное количество ячеек с доски
void PuzzleGenerator::removeCells(Board &board, int removeCount,
                                  std::mt19937 &rng) {
  int n = board.getSize();

  // Список всех координат поля
  std::vector<std::pair<int, int>> positions;
  positions.reserve(n * n);
  for (int r = 0; r < n; ++r)
    for (int c = 0; c < n; ++c)
      positions.emplace_back(r, c);

  // Перемешиваем список координат
  std::shuffle(positions.begin(), positions.end(), rng);

  int removed = 0;
  for (auto &pos : positions) {
    if (removed >= removeCount)
      break;

    int r = pos.first, c = pos.second;
    Cell &cell = board.getCell(r, c);

    // Удаляем только непустые ячейки
    if (cell.value != 0) {
      board.setCell(r, c, 0);
      cell.is_locked = false;
      ++removed;
    }
  }
}
