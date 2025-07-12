#include "../h/board.h"
#include <cmath>
#include <vector>

Cell::Cell(int x, int y, int v, bool lock)
    : row(x), column(y), value(v), is_locked(lock) {};

Block::Block(int index, int bsize) : blockSize(bsize), blockIndex(index) {}

void Block ::addCell(Cell *c) { cells.push_back(c); }

bool Block::contains(int val) const {
  for (auto c : cells) {
    if (c->value == val)
      return true;
  }
  return false;
}

int Block::size() const { return blockSize * blockSize; }

void Board::initBlocks() {
  int numBlock = blockSize * blockSize;
  blocks.reserve(numBlock);
  for (int i = 0; i < numBlock; i++)
    blocks.emplace_back(i, blockSize);
  for (int r = 0; r < size; ++r) {
    for (int c = 0; c < size; c++) {
      int br = r / blockSize;
      int bc = c / blockSize;
      int idx = br * blockSize + bc;
      blocks[idx].addCell(&grid[r][c]);
    }
  }
}

Board::Board(int s) : size(s), blockSize(static_cast<int>(std::sqrt(s))) {
  if (blockSize * blockSize != s)
    throw BoardException();
  grid.resize(size);
  for (int r = 0; r < size; r++) {
    grid[r].reserve(size);
    for (int c = 0; c < size; c++) {
      grid[r].emplace_back(r, c, 0, false);
    }
  }
  initBlocks();
}
Cell &Board::getCell(int r, int c) {
  return grid.at(r).at(c);
} // grid.at = grid[x] + проверка на выход из границы

const Cell &Board::getCell(int r, int c) const { return grid.at(r).at(c); }

bool Board::isValidMove(int r, int c, int val) const {
  if (val <= 0 || val > size)
    return false;
  // строка и столбец
  for (int i = 0; i < size; ++i) {
    if (grid[r][i].value == val)
      return false;
    if (grid[i][c].value == val)
      return false;
  }
  // блок
  int br = r / blockSize;
  int bc = c / blockSize;
  int idx = br * blockSize + bc;
  if (blocks[idx].contains(val))
    return false;

  return true;
}

void Board::setCell(int r, int c, int v) {
  if (r < 0 || r >= size || c < 0 || c >= size)
    throw BoardException();
  Cell &cell = grid[r][c];
  cell.value = v;
  if (v == 0)
    cell.is_locked = false;
}

std::vector<Cell *> Board::getRow(int r) {
  std::vector<Cell *> out;
  out.reserve(size);
  for (int j = 0; j < size; ++j)
    out.push_back(&grid[r][j]);
  return out;
}

std::vector<Cell *> Board::getColumn(int c) {
  std::vector<Cell *> out;
  out.reserve(size);
  for (int i = 0; i < size; ++i)
    out.push_back(&grid[i][c]);
  return out;
}

std::vector<Cell *> Board::getBlock(int r, int c) {
  int br = r / blockSize;
  int bc = c / blockSize;
  int idx = br * blockSize + bc;
  return blocks[idx].getCell();
}

int Board::getSize() const { return size; }

int Board::getBlockSize() const { return blockSize; }

bool Board::isFull() const {
  for (int r = 0; r < size; ++r) {
    for (int c = 0; c < size; ++c) {
      if (grid[r][c].value == 0)
        return false;
    }
  }
  return true;
}

std::vector<Cell *> Block::getCell() const { return cells; }
