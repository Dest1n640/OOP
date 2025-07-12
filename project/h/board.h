#ifndef BOARD_H
#define BOARD_H

#include <vector>

struct Cell {
  int value, row, column;
  bool is_locked;
  Cell(int x, int y, int v, bool locked);
};

class Block {
  int blockSize, blockIndex;
  std::vector<Cell *> cells;

public:
  Block(int index, int bSize);
  void addCell(Cell *c); // Добавление ячейки в блок
  bool contains(int val) const; // Проверка - содержит ли блок указанное
                                // значение
  int size() const; // Возвращает кол-во ячеек в блоке
  std::vector<Cell *>
  getCell() const; // Геттер - возвращает вектор указателей на все ячейки блока
};

class BoardException {};

class Board {
  int size;
  int blockSize;
  std::vector<std::vector<Cell>> grid;
  std::vector<Block> blocks;

  void initBlocks();
  // Приватный метод который инициализирует блоки на доске

public:
  Board(int s);

  Cell &getCell(int r,
                int c); // Геттер - возвращает ссылку на ячейку по координатам
  const Cell &getCell(int r,
                      int c) const; // Геттер - возвращает константное значени
  void
  setCell(int x, int y,
          int value); // Сеттер - устанавлявем значение ячейки по опр. коорд.
  bool isValidMove(int r, int c, int val) const; // Проверка на корректность
                                                 // хода
  std::vector<Cell *> getRow(int r); // Геттер - возвращает все ячейки строки
  std::vector<Cell *> getColumn(int c); // Геттер - возвращает все ячейки
                                        // колонки
  std::vector<Cell *> getBlock(int r,
                               int c); // Геттер - вовращает все ячейки блока
  bool isFull() const; // Проверка - заполнена ли доска полностью
  int getSize() const; // Геттер - возвращает размер доски
  int getBlockSize() const; // Геттер - вовращает размер блока
};

#endif
