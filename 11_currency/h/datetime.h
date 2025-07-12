#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>

class DatetimeException : public std::exception {
  std::string message;

public:
  DatetimeException(const std::string &msg) : message(msg) {}
};

class Datetime {
  std::string full_data;

public:
  Datetime(const std::string &full_data);

  // Геттер
  std::string str() const;

  bool operator<(const Datetime &other) const;
};

#endif
