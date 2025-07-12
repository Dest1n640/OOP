#include "../h/consoleUI.h"
#include <iostream>
#include <limits>
#include <sstream>

Difficult ConsoleUI::selectDiff() {
  int choice;
  while (true) {
    std::cout << "Select difficulty:\n"
              << " 1) Easy\n"
              << " 2) Medium\n"
              << " 3) Hard\n"
              << "Enter choice: ";
    if (std::cin >> choice && (choice >= 1 && choice <= 3)) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return static_cast<Difficult>(choice - 1);
    }
    std::cout << "Invalid choice, try again.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

int ConsoleUI::selectBoardSize() {
  int size;
  while (true) {
    std::cout << "Select board size"
                 " (perfect square, e.g. 4,9,16): ";
    if (std::cin >> size && size > 0) {
      int r = static_cast<int>(std::round(std::sqrt(size)));
      if (r * r == size) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return size;
      }
    }
    std::cout << "Invalid board size, try again.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void ConsoleUI::displayBoard(const Board &b) {
  int n = b.getSize();
  int blockSize = b.getBlockSize();

  // Выводим номера колонок с разделителями блоков
  std::cout << "   ";
  for (int c = 1; c <= n; ++c) {
    std::cout << c;
    if (c % blockSize == 0 && c < n) {
      std::cout << " |";
    } else {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  std::cout << "  +";
  for (int block = 0; block < blockSize; ++block) {
    for (int i = 0; i < blockSize * 2; ++i) {
      std::cout << "-";
    }
    if (block < blockSize - 1) {
      std::cout << "+";
    }
  }
  std::cout << "+\n";

  for (int r = 1; r <= n; ++r) {
    std::cout << r << " |";

    for (int c = 1; c <= n; ++c) {
      const Cell &cell = b.getCell(r - 1, c - 1);
      char ch = (cell.value == 0 ? '.' : char('0' + cell.value));
      std::cout << ch;

      if (c % blockSize == 0 && c < n) {
        std::cout << " |";
      } else {
        std::cout << " ";
      }
    }
    std::cout << "|\n";

    if (r % blockSize == 0 && r < n) {
      std::cout << "  +";
      for (int block = 0; block < blockSize; ++block) {
        for (int i = 0; i < blockSize * 2; ++i) {
          std::cout << "-";
        }
        if (block < blockSize - 1) {
          std::cout << "+";
        }
      }
      std::cout << "+\n";
    }
  }

  std::cout << "  +";
  for (int block = 0; block < blockSize; ++block) {
    for (int i = 0; i < blockSize * 2; ++i) {
      std::cout << "-";
    }
    if (block < blockSize - 1) {
      std::cout << "+";
    }
  }
  std::cout << "+\n\n";

  std::cout << "Commands:\n"
               " m row col value   -> make move\n"
               " u                 -> undo last move\n"
               " q                 -> quit\n"
               " h                 -> get a hint\n";
}

void ConsoleUI::promptMove(GameEngine &engine) {
  std::string line;
  while (true) {
    std::cout << "Enter command: ";
    if (!std::getline(std::cin, line)) {
      std::exit(0);
    }
    std::istringstream iss(line);
    char cmd;
    if (!(iss >> cmd)) {
      std::cout << "Unknown command.\n";
      continue;
    }
    if (cmd == 'h') {
      if (cmd == 'h') {
        try {
          engine.getHint();
        } catch (...) {
          std::cout << "Failed to provide a hint.\n";
        }
        continue;
      }
    }
    if (cmd == 'q') {
      std::cout << "Goodbye!\n";
      std::exit(0);
    }
    if (cmd == 'u') {
      try {
        engine.undo();
      } catch (...) {
        std::cout << "Nothing to undo.\n";
        continue;
      }
      break;
    }
    if (cmd == 'm') {
      int r, c, v;
      if (iss >> r >> c >> v) {
        if (r < 1 || r > engine.getBoard().getSize() || c < 1 ||
            c > engine.getBoard().getSize()) {
          std::cout << "Coordinates out of range.\n";
          continue;
        }

        try {
          engine.applyMove(r - 1, c - 1, v);
        } catch (...) {
          const Cell &cell = engine.getBoard().getCell(r - 1, c - 1);
          if (cell.is_locked) {
            std::cout << "Invalid move: This cell is locked and cannot be "
                         "changed.\n";
          } else {
            std::cout << "Invalid move: Violates Sudoku rules or invalid "
                         "value.\n";
          }
          continue;
        }
        break;
      } else {
        std::cout << "Usage: m row col value\n";
        continue;
      }
    }
    std::cout << "Unknown command.\n";
  }
}

void ConsoleUI::run() {
  currentDifficulty = selectDiff();
  int size = selectBoardSize();
  PuzzleGenerator gen(currentDifficulty);
  GameEngine engine(gen.generate(size));
  while (true) {
    displayBoard(engine.getBoard());
    promptMove(engine);
    if (engine.is_win()) {
      displayBoard(engine.getBoard());
      std::cout << "Congratulations, you won!\n";
      break;
    }
  }
}
