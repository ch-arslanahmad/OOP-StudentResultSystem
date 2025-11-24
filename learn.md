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


## Try-Catch

Try-catch is the building block when developing anything in programming and one important part of it are types of exception like in java there is, `NumberFormatException`, `NullPointerException` and many more in C++, for invalid input, there is `invalid_argument`.

The syntax of Try-catch in C++ is:

```cpp
try:
// actual code

catch(const std::invalid_argument &e ) { // e stores the error message if found, in
        std::cerr << e.what() << '\n'; // prints the error message in console using cerr which is simply cout for errors.
}

```


## Strings & Array

### String <-> Char (Array)

What i have learnt, even though later dropped the idea in `converter.h`, is that to convert a string to an char you do not have any built in function to easily convert like `stoi` for string to int, rather there is a built-in complex function for read/mutable/recommended seperately, each has its own rules to follow, otherwise you have to do it manually.

To convert from char array to string, its simple if char array has null at the end, 

if char arrays are c-type (null-terminated) then there is simple assignment, otherwise you have to do manually again.


>[!NOTE]
> In C++ char is c-type, C-style strings (char[]) are null-terminated: the last element is '\0' to mark the end of the string.


### Cannot Return Arrays

2nd thing you cannot simply return arrays in C++, as if they are generated locally, they will be deleted even if you return them, hence we use a pointer, we make a pointer to an array, dynamically, or we use a reference. and return pointer/reference to array,

```cpp
// converts char array to string
  std::string char_to_string(const char *a) { return std::string(a); }
```

### Convert String to lowerCase


You use 2 imports, `algorithm`, `string`, and we use the following line/function in code,

```cpp
std::transform(a.begin(), a.end(), a.begin(), ::tolower);
```

## List

For starters,

- Use the `push_front()` method to insert an element at the front of the list
- Use the `push_back()` method to insert an element at the end of the list. 
- Use the `pop_front()` method to remove the first element from the list.
- Use the `pop_back()` method to remove the last element from the list.
- Use the `size()` method to get the number of elements in the list.
- Use the `remove()` method to remove elements by value.
Syntax:

```cpp
list_name.remove(value_to_remove);
list_name.remove(index, n); // removes n elements starting from index
```
## Vector Arrays

For starters,

- Use the `push_back()` method to insert an element at the end of the vector.
- Use the `pop_back()` method to remove the last element from the vector.
- Use the `size()` method to get the number of elements in the vector.
- Use the `at()` method to access elements at a specific index with bounds checking.
- find element using `std::find` from `<algorithm>` library.


I think vector is better than list as it provides random access, whereas list is sequential access only.

> [!NOTE]
> However along with it, we need to take care of hashmaps/unordered_map when we want to map key-value pairs for fast lookup and access, but for simplicity, only keep vector arrays.


## Whitespace Removal

This is a small note about removing whitespace from strings in C++.
```cpp
      a.erase(std::remove_if(a.begin(), a.end(),
                             [](unsigned char c) { return std::isspace(c); }),
              a.end());
```

This uses lambda function which are basically anonymous functions, explained later in this file.
```cpp
[](unsigned char c) { return std::isspace(c); }
```
This is function which looks over each character `c` in the string and checks if it is whitespace using `std::isspace(c)`, if so returns true, otherwise false.

Now which calls this function,

```cpp
      a.erase(std::remove_if(a.begin(), a.end(),lamda_function()),
              a.end());
```

So, the lamda function is called for each character in the string `a`, and if it returns true (i.e. the character is whitespace), that character is pushed to the end and marked by `remove_if` as garbage value and `a.erase` removes that garbage values from the string.

## Lambda Functions

### Notes

This file is for small learning notes.
