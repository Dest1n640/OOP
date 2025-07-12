#include "../h/culmination.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

string find_moon_culmination(const string &filtered_data) {
  stringstream ss(filtered_data);
  string line;
  string culmination_time = "not found";
  double max_elevation = numeric_limits<double>::lowest();

  while (getline(ss, line)) {
    stringstream line_ss(line);
    string ymd, hms_str;
    double t, r, el, az, fi, lg;

    if (!(line_ss >> ymd >> hms_str >> t >> r >> el >> az >> fi >> lg)) {
      cout << "Error parsing line: " << line << endl;
      continue;
    }

    if (el > max_elevation) {
      max_elevation = el;
      culmination_time = hms_str;
    }
  }

  if (culmination_time != "not found" && culmination_time.length() >= 6) {
    culmination_time = culmination_time.substr(0, 2) + ":" +
                       culmination_time.substr(2, 2) + ":" +
                       culmination_time.substr(4, 2);
  } else if (culmination_time != "not found") {
    culmination_time = "invalid time format";
  }
  return culmination_time;
}
