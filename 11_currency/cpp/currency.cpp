#include "../h/currency.h"
#include <iostream>
#include <string>
#include <vector>

// Currency
Currency::Currency(double value, double course, std::string name)
    : value(value), course(course), name(name) {}
//  Dollar
Dollar::Dollar(double value, double course)
    : Currency(value, course, "Dollar") {}

void Dollar::print() {
  std::cout << value << " dollars (" << to_cent() << " cents)";
}
double Dollar::to_cent() { return value * 100; }

double Dollar::to_ruble() { return value * course; }

// Euro
Euro::Euro(double value, double course) : Currency(value, course, "Euro") {}

void Euro::print() { std::cout << value << " euro (" << to_cent() << "cents)"; }

double Euro::to_ruble() { return value * course; }
double Euro::to_cent() { return value * 100; }

// Pound
Pound::Pound(double value, double course) : Currency(value, course, "Pound") {}

void Pound::print() {
  std::cout << value << "Pounds (" << to_cent() << " pence)";
}

double Pound::to_ruble() { return value * course; }

double Pound::to_cent() { return value * 100; }

// Purse

Purse::Purse(Currency *currency, const std::string &datetime) {
  values = new std::vector<Currency *>();
  history = new std::map<Datetime, Currency *>();
  values->push_back(currency);
  history->insert(std::make_pair(Datetime(datetime), currency));
}
Purse::~Purse() {
  delete values;
  delete history;
}

double Purse::sum() {
  double total = 0;
  for (Currency *c : *values) {
    total += c->to_ruble();
  }
  return total;
}
bool Purse::is_empty() { return values->size() > 0; }

void Purse::print() {
  std::cout << "Purse contains: ";
  for (Currency *c : *values) {
    c->print();
    std::cout << "; ";
  }
  std::cout << std::endl;
}

void Purse::print_history() {
  std::cout << "History of purse:" << std::endl;
  for (const auto &entry : *history) {
    std::cout << entry.first.str() << " : ";
    entry.second->print();
    std::cout << std::endl;
  }
}
