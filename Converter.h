// a converter that gives us int, float, double, boolean from strings
#include <algorithm>
#include <iostream>
#include <string>
class Converter {
public:
  // convert to int
  int toInt(std::string a) {
    try {
      return std::stoi(a);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << '\n';
      return -1; // error code
    }
  }

  // convert to float
  float toFloat(std::string a) {
    try {
      return std::stof(a);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << '\n';
      return -1.0f; // error code
    }
  }

  // convert to double
  double toDouble(std::string a) {
    try {
      return std::stod(a);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << '\n';
      return -1.0; // error code
    }
  }

  bool toBool(std::string a) {
    try {

      // return false if string empty
      if (a.empty()) {
        return false;
      }

      // ? convert string to lowercase, regardless of case to see if true,
      // false

      // convert string to lower case
      std::transform(a.begin(), a.end(), a.begin(), ::tolower);

      /* if after lower case its
      true -> true otherwise,
      false -> false
      */
      if (a == "true")
        return true;
      if (a == "false")
        return false;

      // convert string to number
      int num = toInt(a);
      // if number is 0
      if (num == 0) {
        return false;
      }

      // if not a number (not-empty, not false) then true.
      return true;

    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << '\n';
      return false; // error code - it will be difficult debugging - hope not
    }
  }
};
