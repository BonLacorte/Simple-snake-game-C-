#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

bool gameOver;
const int width = 118;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    for ( int i = 0; i < width + 2; i++ )               // horizontal wall
        cout << "#";
    
    cout << endl;

    for ( int i = 0; i < height; i++)
    {
        for ( int j = 0; j < width; j++)
        {
            if ( j == 0)                                // vertical wall
                cout << "#";
            if ( i == y && j == x )                     // spawn snake
                cout << "O";
            else if ( i == fruitY && j == fruitX )      // spawn fruit
                cout << "F";
            else {
                bool print = false;
                for ( int k = 0; k < nTail; k++ ) {
                    if ( tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if ( !print) {
                   cout << " " ;
                }
            }
            if ( j == width - 1 )
                cout << "#";
        }
        cout << endl;
    }

    for ( int i = 0; i < width + 2; i++ )               // horizontal wall
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;                 // score tab
}

void Input() {

    if ( _kbhit())
    {
        switch ( _getch() )
        {
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
 
void Logic(){

    
    int prevX = tailX[0];           
    int prevY = tailY[0];            
    int prev2X, prev2Y;
    tailX[0] = x;                   // the first element of array tailX and array tailY is the dimension of the head
    tailY[0] = y;

    for ( int i = 1; i < nTail; i++ ) {     // this will start when the snake already eaten ATLEAST 2 fruits
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)    // logic for Input
    {
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
        default:
            break;
    }

    if ( x > width || x < 0 || y > height || y < 0 ) {  // when snake hit wall, game is over
        gameOver = true;
    }

    for ( int i = 0; i < nTail; i++ ) {     // when snake hit its body, game is over
        if ( tailX[i] == fruitX && tailY[i] == fruitY) {
            gameOver = true;
        }
    }

    if ( x == fruitX && y == fruitY ){      // when fruit was eaten
        score += 10;                        // plus score
        fruitX = rand() % width;            //spawn new fruit - x dimension
        fruitY = rand() % height;             //spawn new fruit - y dimension   
        nTail++;
    }

}

int main() {
    
    Setup();

    while ( !gameOver ) {
        Draw();
        Input();
        Logic();
    }
    return 0;
}
