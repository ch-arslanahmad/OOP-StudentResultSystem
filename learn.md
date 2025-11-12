# Learnings

## std::ostringstream & std::istringstream

Date: 2025-11-12

Topic: Using string streams in C++ to build and parse strings

- `std::ostringstream` — like `cout` but for building dynamic strings.
- `std::istringstream` — like `cin` but for extracting multiple values from a single string.

```cpp
// like cout but for making dynamic strings
std::ostringstream oss;

// like cin getting multiple inputs/variables from one string
std::istringstream iss(text);
```

Example (simple usage)

```cpp
#include <sstream>
#include <string>
#include <iostream>

int main() {
        // Build a string dynamically
        std::ostringstream oss;
        int score = 95;
        std::string name = "Alex";
        oss << "Name: " << name << ", Score: " << score;
        std::string result = oss.str();
        std::cout << result << "\n"; // prints: Name: Alex, Score: 95

        // Parse a string into variables
        std::string text = "42 3.14 Alice";
        std::istringstream iss(text);
        int id; double value; std::string person;
        iss >> id >> value >> person; // id == 42, value == 3.14, person == "Alice"
        std::cout << id << ", " << value << ", " << person << "\n";

        return 0;
}
```

### Why this is useful

- `ostringstream` is handy when you want to format or concatenate (combine) data into a string without manually converting types.
- `istringstream` is great for parsing input received as a single string (e.g., reading a line then extracting multiple values).

### Notes

This file is for small learning notes.
