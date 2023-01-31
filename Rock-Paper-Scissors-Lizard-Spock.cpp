#include <iostream>
#include <stdlib.h>

int main(){
  srand(time(NULL));
  int computer = rand() % 5 + 1;
  int user = 0;

  std::cout << "Rock Paper Scisors Lizard Spock!\n";

  std::cout << "1) Rock\n";
  std::cout << "2) Paper\n";
  std::cout << "3) Scissors\n";
  std::cout << "4) Lizard\n";
  std::cout << "5) Spock\n";
 
  std::cout << "Shoot!\n";

  std::cin >> user;

  if (user == computer){
    std::cout << "Tie!\n";
  }
  else if (user == 1 and computer == 3){
    std::cout << "Win!\n";
  }
  else if (user == 1 and computer == 4){
    std::cout << "Win!\n";
  }
  else if (user == 2 and computer == 1){
    std::cout << "Win!\n";
  }
  else if (user == 2 and computer == 5){
    std::cout << "Win!\n";
  }
  else if (user == 3 and computer == 2){
    std::cout << "Win!\n";
  }
  else if (user == 3 and computer == 4){
    std::cout << "Win!\n";
  }
  else if (user == 4 and computer == 2){
    std::cout << "Win!\n";
  }
  else if (user == 4 and computer == 5){
    std::cout << "Win!\n";
  }
  else if (user == 5 and computer == 3){
    std::cout << "Win!\n";
  }
  else if (user == 5 and computer == 1){
    std::cout << "Win!\n";
  }
  else{
    std::cout << "Lose!\n";
  }

}
