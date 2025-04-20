/*
This code can also be copied from
https://raw.githubusercontent.com/ReiPrea/Hafil/refs/heads/main/pasum.cpp
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
/*
Check whether the system is Windows or Linux
If Windows, include conio.h for _getch()
If anything else, define a function to get character input 
*/
#ifdef _WIN32
    #include <conio.h>
    #define GET_CHAR _getch()
#else
    #define GET_CHAR getCharInput()
    char getCharInput() {
        char ch;
        cin >> ch;
        return ch;
    }
#endif

const char wall = '#';
const char lantai = '.';
const char player = 'P';
const char fogofwar = ' ';
const char trap = 'T';
const char keySym = 'K';
const char doorSym = 'D';
const int normalView = 3;
const int maxPenalty = 10;

void mainGame(const vector<vector<char>>&map, int pX, int pY, int radius, bool hasKey, int trapPenalty, int turnsLeft, pair<int, int> keyPos, pair<int, int> doorPos, vector<pair<int, int>>* traps);
void clearScreen();

// Quiz function
bool selectQuiz(int turnsLeft) {
    //Quiz decided by the amount of turns left
    int questionNum = turnsLeft % 5;
    
    cout << "\nQUIZ CHALLENGE!\n";
    
    switch(questionNum) {
        case 0:
            cout << "What's 7 * 3!?\n";
            cout << "A. 21\nB. 42\nC. 49\nD. 28\n";
            cout << "Your answer: ";
            {
                char answer;
                cin >> answer;
                return (answer == 'B' || answer == 'b');
            }
            
        case 1:
            cout << "Which planet is the 3rd from the sun?\n";
            cout << "A. Mars\nB. Earth\nC. Venus\nD. Jupiter\n";
            cout << "Your answer: ";
            {
                char answer;
                cin >> answer;
                return (answer == 'B' || answer == 'b');
            }
            
        case 2:
            cout << "What is the name of the First Prime Minister of Malaysia?\n";
            cout << "A. Dasuk Seri Anwar Ibrahim\nB. Tun Abdullah Ahmad Badawi\nC. Tunku Abdul Rahman Putra Al-Haj\nD. Tun Hussein Onn\n";
            cout << "Your answer: ";
            {
                char answer;
                cin >> answer;
                return (answer == 'C' || answer == 'c');
            }
            
        case 3:
            cout << "What is the derivative of f(x)=sech(x)?\n";
            cout << "A. sinh(x)\nB. -sech(x)tanh(x)\nC. -csch(x)coth(x)\nD. cosh(x)\n";
            cout << "Your answer: ";
            {
                char answer;
                cin >> answer;
                return (answer == 'B' || answer == 'b');
            }
            
        case 4:
            cout << "What year was Universiti Malaya established?\n";
            cout << "A. 1909\nB. 1949\nC. 1957\nD. 1975\n";
            cout << "Your answer: ";
            {
                char answer;
                cin >> answer;
                return (answer == 'B' || answer == 'b');
            }
            
        default:
            cout << "What is 2 + 2?\n";
            cout << "A. 3\nB. 4\nC. 5\nD. 6\n";
            cout << "Your answer: ";
            {
                char answer;
                cin >> answer;
                return (answer == 'B' || answer == 'b');
            }
    }
}


int main(){
    tryagain:
    // Set up the game map
    vector<vector<char>> map = {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','P','.','#','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','#','.','#','#','#','#','.','#','#','#','.','.','#'},
        {'#','#','.','#','.','.','.','T','#','.','.','.','#','.','#','#'},
        {'#','.','.','.','.','#','#','.','#','#','#','.','#','.','.','#'},
        {'#','.','#','#','#','#','.','.','.','.','.','.','#','.','.','#'},
        {'#','.','.','.','.','.','.','#','#','T','#','.','#','#','.','#'},
        {'#','#','#','#','.','#','.','.','.','.','#','.','.','.','.','#'},
        {'#','.','.','.','.','#','#','#','#','.','#','.','#','#','#','#'},
        {'#','.','#','.','.','.','.','.','#','K','#','.','.','.','.','#'},
        {'#','.','#','#','#','.','#','.','#','.','#','#','#','.','.','#'},
        {'#','.','.','.','.','#','.','.','.','.','.','.','.','.','.','D','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
    };

    // Set up the game variables
    int mapHeight = map.size();
    int mapWidth = (mapHeight > 0) ? map[0].size() : 0;

    int playerX = 1;
    int playerY = 1;

    bool hasKey = false;
    int trapPenalty = 0;
    int turnsLeft = 40;
    pair<int, int> keyPos = {9, 9};
    pair<int, int> doorPos = {14, 11};

    // Dynamically allocate memory for traps
    vector<pair<int, int>>* traps = new vector<pair<int, int>>({{4, 4}, {3, 7}, {6, 9}});
    
    bool gameOver = false;

    while(!gameOver){
        if (turnsLeft <= 0) {
            cout << "\nTime's up! You couldn't escape in time. Game Over.\n";
            break;
        }
        if (trapPenalty >= maxPenalty) {
            cout << "\nYou ran out of time due to trap penalties! Game Over.\n";
            break;
        }

        mainGame(map, playerX, playerY, normalView, hasKey, trapPenalty, turnsLeft, keyPos, doorPos, traps);
        char playinput = GET_CHAR;

        int nextX = playerX;
        int nextY = playerY;
        bool move = false;

        // Quit command
        if (playinput == 'q' || playinput == 'Q') {
            break;
        } else if (playinput == 'w' || playinput == 'W') { nextY--; move = true; }
        else if (playinput == 's' || playinput == 'S') { nextY++; move = true; }
        else if (playinput == 'a' || playinput == 'A') { nextX--; move = true; }
        else if (playinput == 'd' || playinput == 'D') { nextX++; move = true; }

        // Run after a move
        if (move) {
            if (nextY >= 0 && nextY < mapHeight && nextX >= 0 && nextX < mapWidth && map[nextY][nextX] != wall) {
                turnsLeft--;

                // Door check
                if (make_pair(nextX, nextY) == doorPos) {
                    if (hasKey) {
                        cout << "\nYou unlocked the door! Answer a quiz to escape the maze.";
                        if (selectQuiz(turnsLeft)) {
                            cout << "\nCorrect! You escaped the maze! You win!\n";
                            break;
                        } else {
                            cout << "\nWrong answer! You need to try again.\n";
                            continue;
                        }
                    } else {
                        cout << "\nThe door is locked. You need a key.\n";
                        continue;
                    }
                }

                playerX = nextX;
                playerY = nextY;

                // Key check
                if (make_pair(playerX, playerY) == keyPos) {
                    hasKey = true;
                    cout << "\nYou picked up the key!\n";
                }

                // Trap check
                for (auto& trapLoc : *traps) {
                    if (make_pair(playerX, playerY) == trapLoc) {
                        trapPenalty += 2;
                        turnsLeft -= 2; 
                        cout << "\n===========================\n";
                        cout << "You stepped on a trap door!\n";
                        cout << "Time left = -2\n";
                        cout << "Penalty +2 turns and restart!\n";
                        cout << "===========================\n";
                        playerX = 1;
                        playerY = 1;
                        break;
                    }
                }

            } else {
                cout << "\nCannot move there.\n";
            }
        }
    }

    // Game over message
    cout << "\nGame Over!" << endl;
    cout << "\nTry again? (y if yes, press any to exit): ";
    char retry;
    cin >> retry;
    if (retry == 'y' || retry == 'Y') {
        delete traps; // Free memory before restarting
        goto tryagain;
    } else {
        cout << "\nThanks for playing!\n";
    }

    // Free dynamically allocated memory
    delete traps;

    return 0;
}

// A function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// A function to display the game map and player status
void mainGame(const vector<vector<char>>& map, int pX, int pY, int radius, bool hasKey, int trapPenalty,int turnsLeft, pair<int, int> keyPos, pair<int, int> doorPos, vector<pair<int, int>>* traps)
{
    clearScreen();
    int mapHeight = map.size();
    int mapWidth = (mapHeight > 0) ? map[0].size() : 0;
    // Display the status bar
    cout << "Position: (" << pX << "," << pY << ")\n";
    cout << "Key: " << (hasKey ? "Yes" : "No") << " | Trap Penalty: " << trapPenalty << " / " << maxPenalty << " | Time left : "<< turnsLeft<<" turns\n";
    cout << "Key Location: (" << keyPos.first << "," << keyPos.second << ")\n";
    cout << "Door Location: (" << doorPos.first << "," << doorPos.second << ")\n";
    // Display the map with fog of war
    cout << "+";
    for (int i = 0; i < mapWidth; ++i) { cout << "-"; }
    cout << "+\n";
    //
    for (int y = 0; y < mapHeight; ++y) { // Loop through each row of the map
        cout << "|"; // Print the left boundary of the map
        for (int x = 0; x < mapWidth; ++x) { // Loop through each column of the map
            int distance = abs(pX - x) + abs(pY - y);
            if (distance <= radius) { // Check if the current cell is within the player's visibility radius
                if (x == pX && y == pY) { 
                    cout << player;
                } else if (make_pair(x, y) == keyPos) { // If the current cell is the key's position
                    cout << keySym; // Display the key symbol
                } else if (make_pair(x, y) == doorPos) { // If the current cell is the door's position
                    cout << doorSym; // Display the door symbol
                } else {
                    bool isTrap = false;
                    for (auto& trapLoc : *traps) { // Loop through all trap locations
                        /*
                        If the current cell is a trap, Display the trap symbol
                        use break to exit the loop after stepping on a trap
                        */
                        if (trapLoc.first == x && trapLoc.second == y) {
                            cout << trap;
                            isTrap = true; 
                            break;
                        }
                    }
                    if (!isTrap) cout << map[y][x];
                }
            } else {
                cout << fogofwar;
            }
        }
        cout << "|\n"; // Print the right boundary of the map
    }

    cout << "+";
    for (int i = 0; i < mapWidth; ++i) { cout << "-"; }
    cout << "+\n";

    cout << "Move (w/a/s/d) | Quit (q): ";
}
