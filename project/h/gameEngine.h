#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "board.h"
#include <vector>

struct Move {
  int row, col;
  int oldValue, newValue;
};

// Move - структура для хранения информации о ходе: позиция и изменение значения

class GameEngineException {};

class GameEngine {
  Board board;
  std::vector<Move> history;

public:
  GameEngine(int boardSize);
  GameEngine(const Board &initialBoard);
  // GameEngine - конструктор игрового движка, инициализирует с существующей
  // доской

  void applyMove(int x, int y,
                 int value); // Применение хода - устанавливает в опр ячейку
                             // значение и сохраняет в историю

  void undo();                   // Отмена хода
  bool is_win() const;           // Проверка на победу
  void setboard(const Board &b); // Сеттер - устанавливает новое состояние доски
  const Board &getBoard() const; // Возвращает ссылку на текующию доску

  void getHint(); // Метод который будет выводить подскадкук
                  // по нажатию на кнопку
};

#endif
