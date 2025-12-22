// a converter that gives us int, float, double, boolean from strings
#include <algorithm>
#include <iostream>
#include <string>
class Converter {
public:
  void trim(std::string &a) {
    // Trim whitespace from both ends
    a.erase(std::remove_if(a.begin(), a.end(),
                           [](unsigned char c) { return std::isspace(c); }),
            a.end());
  }

  // convert to int
  int toInt(std::string a) {
    try {

      trim(a);
      return std::stoi(a);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << '\n';
      return -1; // error code
    }
  }

  // convert to float
  float toFloat(std::string a) {
    try {

      trim(a);

      return std::stof(a);
    } catch (const std::invalid_argument &e) {
      // Return error code quietly without printing
      return -1.0f;
    }
  }

  // convert to double
  double toDouble(std::string a) {
    try {
      trim(a);
      return std::stod(a);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << '\n';
      return -1.0; // error code
    }
  }

  bool toBool(std::string a) {
    try {
      trim(a);
      // return false if string empty
      if (a.empty()) {
        return false;
      }

      // std::cout << "Size: " << a.size() << "\n"; // debug - to see the size
      // of string passed

      // removes spaces, to handle - ' false' or ' false '
      // a.erase(std::remove(a.begin(), a.end(), ' '), a.end());

      // remove all whitespace (spaces, tabs, CR, LF, etc.)  its implementation
      // explained in learn.md
      a.erase(std::remove_if(a.begin(), a.end(),
                             [](unsigned char c) { return std::isspace(c); }),
              a.end());

      // ? convert string to lowercase, regardless of case to see if true,
      // false
      // convert string to lower case
      std::transform(a.begin(), a.end(), a.begin(), ::tolower);

      // ! for testing
      // std::cout << "Status: " << a << "\n";

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
