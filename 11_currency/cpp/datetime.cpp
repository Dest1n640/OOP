#include "../h/datetime.h"

Datetime::Datetime(const std::string &full_data) {
  // Проверка длины и разделителей
  if (full_data.length() != 19 || full_data[4] != '-' || full_data[7] != '-' ||
      full_data[10] != ' ' || full_data[13] != ':' || full_data[16] != ':') {
    throw DatetimeException("Invalid datetime format. Use YYYY-MM-DD HH:MM:SS");
  }
  // Можно добавить еще простую проверку на цифры, если нужно

  this->full_data = full_data;
}

std::string Datetime::str() const { return full_data; }

bool Datetime::operator<(const Datetime &other) const {
  return full_data < other.full_data;
}
