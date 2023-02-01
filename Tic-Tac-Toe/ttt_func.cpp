#include <iostream>
#include <vector>
#include "ttt_func.hpp"

std::string board[9] = {" "," "," "," "," "," "," "," "," "};
int player = 1;
int pos = 0;

void introduction() {
  std::cout << "Press Enter to begin: ";
  std::cin.ignore();
  std::cout << "\n";
  std::cout << "===========\n";
  std::cout << "Tic-Tac-Toe\n";
  std::cout << "===========\n";
  std::cout << "Player 1: X\n";
  std::cout << "Player 2: O\n\n";
  std::cout << "Here's the 3 x 3 grid:\n\n";

  std::cout << "     |     |      \n";
  std::cout << "  1  |  2  |  3   \n";
  std::cout << "_____|_____|_____ \n";
  std::cout << "     |     |      \n";
  std::cout << "  4  |  5  |  6   \n";
  std::cout << "_____|_____|_____ \n";
  std::cout << "     |     |      \n";
  std::cout << "  7  |  8  |  9   \n";
  std::cout << "     |     |      \n\n";
}

bool is_winner() {
  bool winner = false;
  if (board[0] == board[1] and board[1] == board[2] and board[0] != " "){
    winner = true;
  }
  else if (board[3] == board[4] and board[3] == board[5] and board[3] != " "){
    winner = true;
  }
  else if (board[6] == board[7] and board[6] == board[8] and board[6] != " "){
    winner = true;
  }
  else if (board[0] == board[3] and board[0] == board[6] and board[0] != " "){
    winner = true;
  }
  else if (board[1] == board[4] and board[1] == board[7] and board[1] != " "){
    winner = true;
  }
  else if (board[2] == board[5] and board[2] == board[8] and board[2] != " "){
    winner = true;
  }
  else if (board[0] == board[4] and board[0] == board[8] and board[0] != " "){
    winner = true;
  }
  else if (board[2] == board[4] and board[2] == board[6] and board[2] != " "){
    winner = true;
  }
  return winner;
}

bool filled_in() {
  bool filled = true;
  
  for (int i = 0; i < 9; i++){
    if (board[i] == " "){
      filled = false;
    }
  }
  return filled;
}

void draw_board(){
  std::cout << "     |     |      \n";

  std::cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";

  std::cout << "_____|_____|_____ \n";
  std::cout << "     |     |      \n";

  std::cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";

  std::cout << "_____|_____|_____ \n";
  std::cout << "     |     |      \n";

  std::cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
  std::cout << "     |     |      \n";

  std::cout << "\n";
}

void set_pos(){
  std::cout << "Player" << player << "'s Turn (Enter 1-9): ";
  while (!(std::cin >> pos)){
    std::cout << "Player " << player << ", enter a valid number between 1 and 9: ";
    std::cin.clear();
    std::cin.ignore();
  }
  
  std::cout << "\n";

  while (board[pos - 1] != " "){
    std::cout << "Oops, there's already something in that position!\n\n";
    std::cout << "Player " << player << "'s Turn (Enter 1-9): ";
    std::cin >> pos;
    std::cout << "\n";
  }
}

void update_board() {
  if (player % 2 == 1){
    board[pos - 1] = "X";
  }
  else{
    board[pos - 1] = "O";
  }
}

void change_player() {
  if (player == 1){
    player++;
  }
  else{
    player--;
  }
}

void take_turns() {
  while (!is_winner() and !filled_in()){
    set_pos();
    update_board();
    change_player();
    draw_board();
  }
}

void end_game() {
  if (is_winner()){
    std::cout << "There's a winner!\n";
  }
  else if (filled_in()){
    std::cout << "There's a tie!\n";
  }
}
