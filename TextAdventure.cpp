// Text Adventure
#include <iostream>

int main(){
  std::cout << "==============================\n";
  std::cout << "======= Text Adventure =======\n";
  std::cout << "==============================\n\n";

  std::string name;
  std::cout << "Enter your name: ";
  std::cin >> name;

  std::cout << "Welcome " << name << "!\n";
  std::cout << "Let the adventure begin!\n";
  std::cout << "You wake from a deep slumber in a panic.\n";
  std::cout << "You look around in the dark room, finding yourself alone\n";
  int choice1;
  std::cout << "Exhausted, you... \n";
  std::cout << "1) go back to sleep\n";
  std::cout << "2) get up and go to the bathroom";
  std::cin >> choice1;

  if (choice1 == 1){
      std::cout << "You rest your head back on your pillow, and sleep peacefully through the night.\n";
      std::cout << "==============================\n";
      std::cout << "=========== The End ==========\n";
      std::cout << "==============================\n\n";

      return 0;
  }
  else if (choice1 == 2){
      std::cout << "You groan and get out of bed. The clock blinks 2 a.m. Scratching your head. you walk towards the bathroom.\n";
      std::cout << "As you appraoch the bathroom door, you notice the light is already on.\n";
      std::cout << "Confused, you... \n";
      int choice2;
      std::cout << "1) enter the bathroom anyway. You really have to pee afterall.\n";
      std::cout << "2) turn around and return to bed. Not risking being ambushed in the bathroom at night.\n";
      std::cin >> choice2;
      if (choice2 == 1){
        std::cout << "Inside the bathroom you find a piss gremlin standing atop the toilet!\n";
        std::cout << "'Hark!' shouts the gremlin. '" << name << ", you are finally here!'\n";
        std::cout << "'Answer me these questions three, and I shall allow you to pee' the gremlin mused.\n";
        std::cout << "'Question the first: what is my favorite color?'\n";
        int choice3;
        int lives = 2;
        std::cout << "1) Yellow! You are the piss gremlin after all!\n";
        std::cout << "2) Brown! You are the poo gremlin after all!\n";
        std::cout << "3) Green! You are a green gremlin after all!\n";
        std::cin >> choice3;

        while (lives > 0){
          if (choice3 == 1){
            std::cout << "Correct!\n";
            break;
          }
          else{
            std::cout << "Incorrect! Try Again!\n";
            std::cin >> choice3;
            lives--;
            if (lives <= 0){
              std::cout << "'You lose!' yells the gremlin\n";
              std::cout << "The gremlin leaps with glee, before lunging and eating you whole!\n";
              return 0;
            }
          }
        }
        std::cout << "'Question the second: What time is it now?'\n";
        int choice4;
        std::cout << "1) 12 a.m.\n";
        std::cout << "2) 1 a.m.\n";
        std::cout << "3) 2 a.m.\n";
        lives = 2;
        while (lives > 0){
          if (choice4 == 3){
            std::cout << "Correct!\n";
            break;
          }
          else{
            std::cout << "Incorrect! Try Again!\n";
            std::cin >> choice4;
            lives--;
            if (lives <= 0){
              std::cout << "'You lose!' yells the gremlin\n";
              std::cout << "The gremlin leaps with glee, before lunging and eating you whole!\n";
              return 0;
            }
          }
        }
        std::cout << "'Question the third: How did you awake?\n";
        std::cout << "1) Calmly\n";
        std::cout << "2) In a panic\n";
        std::cout << "3) In a cold sweat\n";
        int choice5;
        lives = 2;
        while (lives > 0){
          if (choice5 == 2){
            std::cout << "Correct!\n";
            break;
          }
          else{
            std::cout << "Incorrect! Try Again!\n";
            std::cin >> choice5;
            lives--;
            if (lives <= 0){
              std::cout << "'You lose!' yells the gremlin\n";
              std::cout << "The gremlin leaps with glee, before lunging and eating you whole!\n";
              return 0;
            }
          }
        }
        std::cout << "'Arghhh' yells the gremlin 'you win this time " << name << "!'\n";
        std::cout << "The gremlin disappears into thin air, and finally you are free to do as you wish.\n";
        std::cout << "You ...\n";
        std::cout << "1) finally pee.\n";
        std::cout << "2) return to bed without peeing.\n";
        int choice6;
        std::cin >> choice6;
        
        if (choice6 == 1){
          std::cout << "You finally pee and feel your whole body relax. You return to bed and sleep peacflly through the night.\n";
          std::cout << "==============================\n";
          std::cout << "=========== The End ==========\n";
          std::cout << "==============================\n\n";

          return 0;
        }
        else if (choice6 == 2){
          std::cout << "You return to bed without going to the bathroom. You awake again in hour, having peed the bed in your sleep.\n";
          std::cout << "==============================\n";
          std::cout << "=========== The End ==========\n";
          std::cout << "==============================\n\n";

          return 0;
        }
        else{
          std::cout << "Invalid Input";

          return 0;
        }
      }
      else if (choice2 == 2){
        std::cout << "You return back to bed, and sleep peacefully through the night.\n";
        std::cout << "==============================\n";
        std::cout << "=========== The End ==========\n";
        std::cout << "==============================\n\n";
      }
  }
  else{
      std::cout << "Invalid Input";
      return 0;
  }

}
