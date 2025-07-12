#ifndef DIFFICULT_H
#define DIFFICULT_H

#include "board.h"
#include "gameEngine.h"
#include <random>
#include <vector>

enum class Difficult { Easy, Medium, Hard };
// Cтрого типизированное перечисление, предназначенное для представления уровней
// сложности

class PuzzleGenerator {
  Difficult level;

  bool fillGrid(Board &board, int row, int column, std::mt19937 &rng);
  // Рекурсивно заполняется доска валидными предназнаениями
  void removeCells(Board &board, int removeCount, std::mt19937 &rng);
  // Удаление определенное кол-во подсказок в зависимости от сложности

public:
  PuzzleGenerator(Difficult d);
  Board generate(int size);
  // Генерирует новую головоломку указанного размера с заданным уровнем
  // сложности
};

#endif // !DIFFICULT_H
