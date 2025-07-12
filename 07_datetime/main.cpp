#include "datatime.h"
#include <iostream>

int main() {
  std::cout << "--- Constructors ---" << std::endl;
  Datetime dt1(2024, 1, 20);              // Date without time
  Datetime dt2(2023, 12, 31, 23, 59, 59); // Date and time
  Datetime dt3("2024-02-29");
  Datetime dt4(2024, 2, 30);          // Incorrect date
  Datetime dt5(2024, 1, 1, -1, 0, 0); // Incorrect time
  Datetime dt6;                       // Default constructor

  std::cout << "dt1: " << dt1 << ", dt2: " << dt2 << ", dt3: " << dt3
            << std::endl;
  std::cout << "dt4 (incorrect): " << dt4 << ", dt5 (incorrect): " << dt5
            << ", dt6 (default): " << dt6 << std::endl;
  std::cout << std::endl;

  std::cout << "--- Input/Output ---" << std::endl;
  Datetime dt_input;
  std::cout << "Enter date and time (yyyy mm dd hh mm ss): ";
  std::cin >> dt_input;
  std::cout << "You entered: " << dt_input << std::endl;
  std::cout << std::endl;

  std::cout << "Enter date only (yyyy mm dd): ";
  std::cin >> dt_input;
  std::cout << "You entered: " << dt_input << std::endl;
  std::cout << std::endl;

  std::cout << "--- Arithmetic ---" << std::endl;
  Datetime dt_arithmetic(2024, 3, 10);
  std::cout << "Initial date: " << dt_arithmetic << std::endl;
  std::cout << "+7 days: " << (dt_arithmetic + 7) << std::endl;
  dt_arithmetic += 10;
  std::cout << "+=10 days: " << dt_arithmetic << std::endl;
  std::cout << "-5 days: " << (dt_arithmetic - 5)
            << std::endl; // Теперь работает!
  dt_arithmetic -= 3;
  std::cout << "-=3 days: " << dt_arithmetic << std::endl;

  Datetime dt_diff_start(2024, 1, 1);
  Datetime dt_diff_end(2024, 1, 15);
  std::cout << std::endl;

  std::cout << "--- Additional ---" << std::endl;
  Datetime dt_check;
  return 0;
}
