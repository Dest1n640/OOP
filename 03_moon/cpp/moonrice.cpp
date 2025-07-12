#include "../h/moonrice.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

string find_moonrise(const string &filtered_data) {
  stringstream ss(filtered_data);
  string line;
  string moonrise_time = "not found";
  double prev_elevation = numeric_limits<double>::lowest();
  bool moonrise_found = false;

  while (getline(ss, line)) {
    stringstream line_ss(line);
    string ymd, hms_str;
    double t, r, el, az, fi, lg;

    if (!(line_ss >> ymd >> hms_str >> t >> r >> el >> az >> fi >> lg)) {
      cerr << "Error parsing line: " << line << endl;
      continue;
    }

    if (!moonrise_found && prev_elevation < 0 && el >= 0) {
      moonrise_time = hms_str;
      moonrise_found = true;
    }
    prev_elevation = el;
  }

  if (moonrise_time != "not found" && moonrise_time.length() >= 6) {
    moonrise_time = moonrise_time.substr(0, 2) + ":" +
                    moonrise_time.substr(2, 2) + ":" +
                    moonrise_time.substr(4, 2);
  } else if (moonrise_time != "not found") {
    moonrise_time = "invalid time format";
  }
  return moonrise_time;
}
