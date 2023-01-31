#include <iostream>
#include <vector>
#include <string>

int main() {
  std::string input = "Get me my fishing fuel";
  std::vector<char> whale = {'a','e','i','o','u'};
  std::vector<char> results;

  for (int i = 0; i < input.size(); i++){
    for (int j = 0; j < whale.size(); j++){
      if (input[i] == whale[j]){
        results.push_back(input[i]);
        if (input[i] == 'e' or input[i] == 'u'){
          results.push_back(input[i]);
        }
      }
    }
  }
  for (int i = 0; i < results.size(); i++){
    std::cout << results[i];
  }
}
