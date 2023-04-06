#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// Global Variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int tailX[400], tailY[400];
int nTail;
enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir;

void setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

void draw(){
    system("cls");
    for (int i = 0; i < width + 2; i++){
        cout << '#';
    }
    cout << endl;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (j == 0){
                cout << '#';
            }
            
            if (i == y && j == x){
                cout << 'O';
            }
            else if (i == foodY && j == foodX){
                cout << 'F';
            }
            else{
                bool prints = false;
                for (int k = 0; k < nTail; k++){
                    if (tailX[k] == j && tailY[k] == i){
                        cout << "o";
                        prints = true;
                    }
                }
                if (!prints){
                        cout << ' ';
                    }
            }

            if (j == width - 1){
                cout << '#';
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++){
        cout<< '#';
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void input(){
    if (_kbhit()){
        switch (_getch()){
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;    
        
    }

    if (x < 0 || x > width || y > height || y < 0){
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++){
        if (tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }

    if (x == foodX && y == foodY){
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}

int main(){
    setup();

    while (!gameOver){
        draw();
        input();
        logic();
        Sleep(20);
    }

    return 0;
}