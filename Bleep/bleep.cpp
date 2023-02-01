#include <iostream>
#include <string>
#include "functions.hpp"

int main() {
  std::string new_word = "fuck";
  std::string new_text = "I like eating fuck";

  bleep(new_word, new_text);

  for (int i = 0; i < new_text.size(); i++){
    std::cout << new_text[i];
  }
  std::cout << "\n";
}
