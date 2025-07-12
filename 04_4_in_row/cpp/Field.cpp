#include "../h/Field.h"
#include <iostream>

Field::Field(bool isRedFirst) { clear(isRedFirst); }

void Field::clear(bool isRedFirst) {
  isRedTurn = isRedFirst;
  winner = EMPTY;
  for (int i = 0; i < FIELD_WIDTH; i++)
    for (int j = 0; j < FIELD_HEIGHT; j++)
      cells[i][j] = EMPTY;
}

bool Field::makeTurn(int column) {
  if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
    return false;
  int i = column - 1;
  for (int j = FIELD_HEIGHT - 1; j >= 0; j--)
    if (cells[i][j] == EMPTY) {
      cells[i][j] = isRedTurn ? RED : YELLOW;
      checkWinner();
      isRedTurn = !isRedTurn;
      return true;
    }
  return false;
}

const int DIR_NUMBER = 4;
const int di[] = {1, 0, 1, 1};
const int dj[] = {0, 1, -1, 1};
const int WIN_LENGTH = 4;
void Field::checkWinner() {
  for (int i = 0; i < FIELD_WIDTH; i++)
    for (int j = 0; j < FIELD_HEIGHT; j++) {
      Cell start = cells[i][j];
      if (start == EMPTY)
        continue;
      for (int dir = 0; dir < DIR_NUMBER; dir++) {
        int length = 0, iline = i, jline = j;
        while (++length < WIN_LENGTH) {
          iline += di[dir];
          jline += dj[dir];
          if (iline < 0 || iline >= FIELD_WIDTH || jline < 0 ||
              jline >= FIELD_HEIGHT)
            break;
          if (cells[iline][jline] != start)
            break;
        }
        if (length == WIN_LENGTH) {
          winner = start;
          return;
        }
      }
    }
}

bool Field::isOver() const {
  if (winner != EMPTY)
    return true;
  for (int i = 0; i < FIELD_WIDTH; i++)
    for (int j = 0; j < FIELD_HEIGHT; j++)
      if (cells[i][j] == EMPTY)
        return false;
  return true;
}

void Field::print() const {
  std::cout << "-------------" << std::endl;
  for (int j = FIELD_HEIGHT - 1; j >= 0; j--) {
    std::cout << "|";
    for (int i = 0; i < FIELD_WIDTH; i++) {
      switch (cells[i][j]) {
      case EMPTY:
        std::cout << " ";
        break;
      case RED:
        std::cout << "R";
        break;
      case YELLOW:
        std::cout << "Y";
        break;
      }
      std::cout << "|";
    }
    std::cout << std::endl;
  }
  std::cout << "-------------" << std::endl;
  for (int i = 1; i <= FIELD_WIDTH; i++) {
    std::cout << " " << i;
  }
  std::cout << std::endl;
}

bool Field::isRedTurnNow() const { return isRedTurn; }

void Field::printResult() const {
  if (winner == RED) {
    std::cout << "RED player win!" << std::endl;
  } else if (winner == YELLOW) {
    std::cout << "YELLOW player win!" << std::endl;
  } else if (isOver()) {
    std::cout << "DRAW!" << std::endl;
  }
}

bool Field::isWon(bool red) const { return winner == (red ? RED : YELLOW); }

Cell Field::getCell(int i, int j) const {
  if (i >= 0 && i < FIELD_WIDTH && j >= 0 && j < FIELD_HEIGHT) {
    return cells[i][j];
  }
  return EMPTY;
}
