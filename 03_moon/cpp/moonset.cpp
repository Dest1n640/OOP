#include "../h/moonset.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

string find_moonset(const string &filtered_data) {
  stringstream ss(filtered_data);
  string line;
  string moonset_time = "not found";
  double prev_elevation = numeric_limits<double>::lowest();
  bool moonset_found = false;

  while (getline(ss, line)) {
    stringstream line_ss(line);
    string ymd, hms_str;
    double t, r, el, az, fi, lg;

    if (!(line_ss >> ymd >> hms_str >> t >> r >> el >> az >> fi >> lg)) {
      cout << "Error parsing line: " << line << endl;
      continue;
    }

    if (!moonset_found && prev_elevation >= 0 && el < 0) {
      moonset_time = hms_str;
      moonset_found = true;
    }
    prev_elevation = el;
  }

  if (moonset_time != "not found" && moonset_time.length() >= 6) {
    moonset_time = moonset_time.substr(0, 2) + ":" + moonset_time.substr(2, 2) +
                   ":" + moonset_time.substr(4, 2);
  } else if (moonset_time != "not found") {
    moonset_time = "invalid time format";
  }
  return moonset_time;
}
