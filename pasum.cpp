#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
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

void deleteInput();
void mainGame(const vector<vector<char>>&map, int pX, int pY, int radius, bool hasKey, int trapPenalty, int turnsLeft, pair<int, int> keyPos, pair<int, int> doorPos, vector<pair<int, int>> traps);
void clearScreen();

// Quiz function
bool selectQuiz(int turnsLeft) {
    //Quiz decided by the amount of turns left
    int questionNum = turnsLeft % 5;
    
    cout << "\nQUIZ CHALLENGE!\n";
    
    switch(questionNum) {
        case 0:
            cout << "What's 7 + 3?\n";
            cout << "A. 9\nB. 10\nC. 11\nD. 12\n";
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
            cout << "What is the capital of France?\n";
            cout << "A. London\nB. Berlin\nC. Paris\nD. Madrid\n";
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
            cout << "What is the largest mammal?\n";
            cout << "A. African Elephant\nB. Blue Whale\nC. Giraffe\nD. Gorilla\n";
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

    int mapHeight = map.size();
    int mapWidth = (mapHeight > 0) ? map[0].size() : 0;

    int playerX = 1;
    int playerY = 1;

    bool hasKey = false;
    int trapPenalty = 0;
    int turnsLeft = 40;
    pair<int, int> keyPos = {9, 9};
    pair<int, int> doorPos = {14, 11};
    vector<pair<int, int>> traps = {{4, 4}, {3, 7}, {6, 9}};
    
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

        if(playinput == 'q' || playinput == 'Q') {
            break;
        }
        else if (playinput == 'e' || playinput == 'E') {
            move = false;
        }
        else if (playinput == 'w' || playinput == 'W') { nextY--; move = true; }
        else if (playinput == 's' || playinput == 'S') { nextY++; move = true; }
        else if (playinput == 'a' || playinput == 'A') { nextX--; move = true; }
        else if (playinput == 'd' || playinput == 'D') { nextX++; move = true; }

        if(move){
            if(nextY >= 0 && nextY < mapHeight && nextX >= 0 && nextX < mapWidth && map[nextY][nextX] != wall){
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
                for (auto& trapLoc : traps) {
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

    cout << "\nGame Over!" << endl;
    cout << "\n Try again? (y if yes, press any to exit): ";
    char retry;
    cin >> retry;
    if (retry == 'y' || retry == 'Y') {
        goto tryagain;
    } else {
        cout << "\nThanks for playing!\n";
    }
    return 0;
}

void deleteInput() {
    char huruf;
    while (cin.get(huruf) && huruf != '\n');
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mainGame(const vector<vector<char>>& map, int pX, int pY, int radius, bool hasKey, int trapPenalty,int turnsLeft, pair<int, int> keyPos, pair<int, int> doorPos, vector<pair<int, int>> traps)
{
    clearScreen();
    int mapHeight = map.size();
    int mapWidth = (mapHeight > 0) ? map[0].size() : 0;

    cout << "Position: (" << pX << "," << pY << ")\n";
    cout << "Key: " << (hasKey ? "Yes" : "No") << " | Trap Penalty: " << trapPenalty << " / " << maxPenalty << " | Time left : "<< turnsLeft<<" turns\n";
    cout << "Key Location: (" << keyPos.first << "," << keyPos.second << ")\n";
    cout << "Door Location: (" << doorPos.first << "," << doorPos.second << ")\n";

    cout << "+";
    for (int i = 0; i < mapWidth; ++i) { cout << "-"; }
    cout << "+\n";

    for (int y = 0; y < mapHeight; ++y) {
        cout << "|";
        for (int x = 0; x < mapWidth; ++x) {
            int distance = abs(pX - x) + abs(pY - y);
            if (distance <= radius) {
                if (x == pX && y == pY) {
                    cout << player;
                } else if (make_pair(x, y) == keyPos) {
                    cout << keySym;
                } else if (make_pair(x, y) == doorPos) {
                    cout << doorSym;
                } else {
                    bool isTrap = false;
                    for (auto& trapLoc : traps) {
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
        cout << "|\n";
    }

    cout << "+";
    for (int i = 0; i < mapWidth; ++i) { cout << "-"; }
    cout << "+\n";

    cout << "Move (w/a/s/d) | Quit (q): ";
}
