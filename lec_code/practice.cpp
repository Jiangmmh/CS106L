/*
 * Credit to Sarah McCarthy '23 for this example
 */

//compile with: g++ -std=c++20 practice.cpp -o practice
//run with: ./practice (on mac)

#include <iostream>
#include <optional>

std::optional<int> divide(int numerator, int denominator) {
    /* FILL IN HERE */
    if (denominator != 0) {
        return numerator / denominator;
    }
        
    return std::nullopt;
}

int main() {
  /* CALL HERE WITH (10, 2)*/
  auto result1 = divide(10, 2);
  if (result1) {
      std::cout << "Result: " << *result1 << std::endl;
  } else {
      std::cout << "Division by zero!" << std::endl;
  }
  
  /* CALL HERE WITH (10, 0)*/
  auto result2 = divide(10, 0);
  if (result2) {
    std::cout << "Result: " << *result2 << std::endl;
  } else {
    std::cout << "Division by zero!" << std::endl;
  }

  return 0;
}