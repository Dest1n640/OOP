#include "../h/gameEngine.h"
#include "../h/board.h"
#include <iostream>
#include <vector>

GameEngine::GameEngine(int boardSize) : board(boardSize) {};

GameEngine::GameEngine(const Board &initialBoard) : board(initialBoard) {}

void GameEngine::setboard(const Board &b) {
  board = b;
  history.clear();
}

const Board &GameEngine::getBoard() const { return board; }

void GameEngine::applyMove(int r, int c, int val) {
  Cell &cell = board.getCell(r, c);
  if (cell.is_locked || !board.isValidMove(r, c, val))
    throw GameEngineException();

  history.push_back({r, c, cell.value, true});
  board.setCell(r, c, val);
}

void GameEngine::undo() {
  if (history.empty())
    throw GameEngineException();

  auto m = history.back();
  history.pop_back();
  board.setCell(m.row, m.col, m.oldValue);
}

bool GameEngine::is_win() const { return board.isFull(); }

void GameEngine::getHint() {
  // Ищем ячейку с единственным возможным значением
  for (int row = 0; row < board.getSize(); ++row) {
    for (int col = 0; col < board.getSize(); ++col) {
      if (board.getCell(row, col).value == 0) {
        // Проверка на то пустая ли ячейка

        int possibleValue = 0;
        int count = 0;

        for (int value = 1; value <= board.getSize(); ++value) {
          if (board.isValidMove(row, col, value)) {
            possibleValue = value;
            count++;
            // Ищем какое значение можем поставить
          }
        }

        if (count == 1) {
          std::cout << "\nHINT: Put " << possibleValue << " in cell ("
                    << row + 1 << ", " << col + 1 << ")\n";
          return;
          // Если будет найденно только одно допустимое значени
          // то функция вернет это значение и его координаты
        }
      }
    }
  }

  std::cout << "\nNo obvious moves found\n";
}
