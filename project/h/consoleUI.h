#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "board.h"
#include "difficult.h"
#include "gameEngine.h"

class ConsoleUI {
  Difficult currentDifficulty;
  Difficult selectDiff(); // Запрашивает у пользователя сложность
  int selectBoardSize();  // Запрашивает у пользователя размер доски
  void displayBoard(const Board &board); // Отображает текущее состояние доски
  void promptMove(GameEngine &engine);   // Запрашивает у пользователя ход и
                                         // применяет его через игровой движок
public:
  void run(); // Запуск программу
};

#endif
