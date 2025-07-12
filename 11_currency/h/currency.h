#ifndef CURRENCY_H
#define CURRENCY_H

#include "datetime.h"
#include <map>
#include <string>
#include <vector>

// Абстрактный класс для валют
class Currency {
protected:
  double course;
  double value;
  std::string name;

public:
  Currency(double value, double course, std::string name);
  virtual void print() = 0; // Виртуальный метод для вывода
  virtual double
  to_ruble() = 0;               // Виртуальный метод для перевода валюты в рубли
  virtual double to_cent() = 0; // Виртуальный метод для перевода
  virtual ~Currency() = default;
};

// Класс для доллара, наследуется от Currency
class Dollar : public Currency {
public:
  Dollar(double value, double course);

  // Реализация виртуальных функций
  void print();
  double to_ruble();
  double to_cent();
};

// Класс для евро, наследуется от Currency
class Euro : public Currency {
public:
  Euro(double value, double course);
  // Реализация виртуальных функций
  void print();
  double to_ruble();
  double to_cent();
};

// Класс для фунта, наследуется от Currency
class Pound : public Currency {
public:
  Pound(double value, double course);
  // Реализация виртуальных функций
  void print();
  double to_ruble();
  double to_cent();
};

// Класс кошелька, который хранит валюты и историю их добавления
class Purse {
  std::vector<Currency *> *values; // Вектор указателей на объекты валют
  std::map<Datetime, Currency *>
      *history; // История: ключ - дата, значение - валюта

public:
  // Конструктор кошелька: добавляет одну валюту с датой
  Purse(Currency *currency, const std::string &datetime);

  // Проверка, пуст ли кошелек
  bool is_empty();

  // Сумма всех валют в кошельке в рублях
  double sum();

  // Выводит все валюты в кошельке
  void print();

  // Выводит историю добавления валют
  void print_history();

  // Деструктор: освобождает память
  ~Purse();
};
#endif
