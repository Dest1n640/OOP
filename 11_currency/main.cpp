#include "h/currency.h"
#include "h/datetime.h"
#include <iostream>
#include <string>

int main() {
  try {
    // Ввод даты и времени пользователем для проверки DatetimeException
    std::string input_datetime;
    std::cout << "Введите дату и время (YYYY-MM-DD HH:MM:SS): ";
    std::getline(std::cin, input_datetime);

    // Создаем валюты
    Currency *dollar = new Dollar(10, 90);
    Currency *euro = new Euro(5, 100);
    Currency *pound = new Pound(3, 110);

    // Создаем кошелек с одной валютой и датой
    Purse purse(dollar, input_datetime);

    // Выводим содержимое кошелька
    purse.print();
    purse.print_history();

    std::cout << "Is empty? " << (purse.is_empty() ? "No" : "Yes") << std::endl;
    std::cout << "Total in rubles: " << purse.sum() << std::endl;

    delete euro;
    delete pound;
  } catch (const DatetimeException &ex) {
    std::cout << "Ошибка: " << ex.what() << std::endl;
  }

  return 0;
}
