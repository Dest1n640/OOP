#include "./h/culmination.h"
#include "./h/moonrice.h"
#include "./h/moonset.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string find_data(const string &file_name, const string &age, const string &data,
                 const string &month);

int main() {
  string age, data, month;
  cout << "Input the age, day, and month (age day month, e.g., 2000 01 01): ";
  cin >> age >> data >> month;
  if (age.length() != 4 || data.length() != 2 || month.length() != 2) {
    cerr << "Error: Invalid input format.  Please use YYYY DD MM." << endl;
    return 1;
  }
  for (char c : age + data + month) {
    if (!isdigit(c)) {
      cerr << "Error: Input must contain only digits." << endl;
      return 1;
    }
  }

  string file_name = "./moon/Moon/moon" + age + ".dat";

  cout << "Trying to open file: " << file_name << endl;

  string filtered_data = find_data(file_name, age, data, month);

  if (filtered_data.rfind("Error:", 0) == 0) {
    cerr << filtered_data << endl;
    return 1;
  } else if (filtered_data.empty()) {
    cout << "No data found for the specified date in the file." << endl;
    return 0;
  } else {
    cout << "\n--- Filtered Data from File ---" << endl;
    cout << filtered_data << endl;
    cout << "--- End of Filtered Data ---" << endl;

    string date_dd_mm_yyyy = data + "." + month + "." + age;
    string moonrise_time = find_moonrise(filtered_data);
    string culmination_time = find_moon_culmination(filtered_data);
    string moonset_time = find_moonset(filtered_data);

    cout << "\n--- Moon Event Times ---" << endl;
    cout << "Date: " << date_dd_mm_yyyy << endl;
    cout << "Moonrise: " << moonrise_time << endl;
    cout << "Culmination: " << culmination_time << endl;
    cout << "Moonset: " << moonset_time << endl;
    cout << "--- End of Moon Event Times ---" << endl;
  }

  return 0;
}

string find_data(const string &file_name, const string &age, const string &data,
                 const string &month) {
  ifstream file(file_name);
  string result = "";
  string full_data = age + month + data;

  if (!file.is_open()) {
    cerr << "Error: Could not open file " << file_name << endl;
    return "Error: Could not open file " + file_name;
  }

  string line;
  getline(file, line);

  while (getline(file, line)) {
    if (line.rfind(full_data, 0) == 0) {
      result += line + "\n";
    }
  }

  file.close();
  return result;
}
