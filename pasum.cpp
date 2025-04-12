#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

const char wall = '#';
const char lantai = '.';
const char player = 'P';
const char fogofwar = ' '; // Ni tak sure tbd
const int normalView = 3;

void deleteInput();
void mainGame(const vector<vector<char>>&map, int pX, int pY, int radius);


int main(){
    vector<vector<char>> map = {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','P','.','#','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','#','.','#','#','#','#','.','#','#','#','.','.','#'},
        {'#','#','.','#','.','.','.','.','#','.','.','.','#','.','#','#'},
        {'#','.','.','.','.','#','#','.','#','#','#','.','#','.','.','#'},
        {'#','.','#','#','#','#','.','.','.','.','.','.','#','.','.','#'},
        {'#','.','.','.','.','.','.','#','#','#','#','.','#','#','.','#'},
        {'#','#','#','#','.','#','.','.','.','.','#','.','.','.','.','#'},
        {'#','.','.','.','.','#','#','#','#','.','#','.','#','#','#','#'},
        {'#','.','#','.','.','.','.','.','#','.','#','.','.','.','.','#'},
        {'#','.','#','#','#','.','#','.','#','.','#','#','#','.','.','#'},
        {'#','.','.','.','#','.','#','.','.','.','.','.','.','.','D','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
    };
    int mapHeight = map.size();
    int mapWidth;
    if (mapHeight > 0) {
        mapWidth = map[0].size();
    } else {
        mapWidth = 0;
    }

    int playerX = 1;
    int playerY = 1;

    while(true){
        mainGame(map,playerX,playerY,normalView);

        char playinput;
        if(!(cin >> playinput)) {
            cout << "Please input correctly." << endl;
            break;
        }
        deleteInput();

        int nextX = playerX;
        int nextY = playerY;
        bool move;

        if(playinput == 'q' || playinput == 'Q') {
            break;
        }

        if (playinput == 'w' || playinput == 'W' || playinput == 'A' || playinput == 'a' || playinput == 's' || playinput == 'S' || playinput == 'd' || playinput == 'D' ){
            if (playinput == 'w' || playinput == 'W') { nextY--; move = true;}
            else if (playinput == 's' || playinput == 'S') { nextY++; move = true;}
            else if (playinput == 'a' || playinput == 'A') { nextX--; move = true;}
            else if (playinput == 'd' || playinput == 'D') { nextX++; move = true;}
        }

        if(move){
            if(nextY >= 0 && nextY < mapHeight && nextX >= 0 && nextX<mapWidth && map[nextY][nextX] != wall){
                playerX = nextX;
                playerY = nextY;

                //Ayra (door + key)
                //Ezryn (trap)
                //Aasim (Timer)


            } else {
                cout << "Cannot move there." << endl;
            }

            //Ezryn (sweeper)

        }

        //Aasim (Game over/Win)
    }

    cout << "\nGame Over!" << endl;
    return 0;
}

void deleteInput() {
    char huruf;
    while (cin.get(huruf) && huruf != '\n');
}

void mainGame(const vector<vector<char>>& map, int pX, int pY, int radius)
{
    system("cls"); 
    int mapHeight = map.size();
    int mapWidth = 0;
    if (mapHeight > 0) {
        mapWidth = map[0].size();
    }

    cout << "Position: (" << pX << "," << pY << ")" << endl;

    cout << "+";
    for (int i = 0; i < mapWidth; ++i) {
        cout << "-"; 
    }
    cout << "+" << endl; 

    for (int y = 0; y < mapHeight; ++y) {
        cout << "|"; 
        for (int x = 0; x < mapWidth; ++x) {
            int distance = abs(pX - x) + abs(pY - y);

            if (distance <= radius) {
                if (x == pX && y == pY) {
                    cout << player; 
                }
                // Sini display door/key/traps (ezryn,ayra)
                else {
                    cout << map[y][x];
                    //sweeper + revealed traps kt sini kot (ezryn)
                }
            } else {
                cout << fogofwar; 
            }
        }
        cout << "|" << endl; 
    }

    cout << "+"; 
    for (int i = 0; i < mapWidth; ++i) {
        cout << "-";
    }
    cout << "+" << endl; 

    //sweeper aku buat ikut ah nk tukar ke x (ezryn)
    cout << "Move (w/a/s/d) | Sweeper (e) | Quit (q): ";
}
