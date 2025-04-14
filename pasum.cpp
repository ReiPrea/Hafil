#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
//letak const char revealed trap ngan symbol kt sini (ezryn)
const char wall = '#';
const char lantai = '.';
const char player = 'P';
const char fogofwar = ' ';
const int normalView = 3;


void deleteInput();
void mainGame(const vector<vector<char>>&map, int pX, int pY, int radius);
void clearScreen();

int main(){
    // Initialiaze door + key punya position + variable kt sini (Ayra)

    // Initialiaze trap punya position + variable kt sini (ezryn)
    
    // Initialiaze timer + game punya status + variable kt sini (Aasim)
    

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
    int mapWidth = 0;
    if (mapHeight > 0) {
        mapWidth = map[0].size();
    }

    int playerX = 1;
    int playerY = 1;

    bool gameOver = false;
    // Variable number of turns letak kt sini (Aasim)
    // Status pun sama 

    while(true){
        // Ni mungkin tempat korg letak function
        mainGame(map,playerX,playerY,normalView);

        char playinput;
        cin >> playinput;
        deleteInput();

        int nextX = playerX;
        int nextY = playerY;
        bool move = false; 

        if(playinput == 'q' || playinput == 'Q') {
            break;
        }

        // // Sweeper punya button apa nk guna on kt sini (e) (Ezryn)
        // Kena ada status sweeper active, sweeper berapa turn tinggal, berapa lama sweeper
        if (playinput == 'e' || playinput == 'E') {
             // Sweeper punya button apa nk guna on kt sini (Ezryn)
             move = false;
        }
        else if (playinput == 'w' || playinput == 'W' || playinput == 'a' || playinput == 'A' || playinput == 's' || playinput == 'S' || playinput == 'd' || playinput == 'D' ){
            if (playinput == 'w' || playinput == 'W') { nextY--; move = true;}
            else if (playinput == 's' || playinput == 'S') { nextY++; move = true;}
            else if (playinput == 'a' || playinput == 'A') { nextX--; move = true;}
            else if (playinput == 'd' || playinput == 'D') { nextX++; move = true;}
        } else {
             // Set status kalau salah input (Aasim)
             move = false;
        }


        if(move){
            if(nextY >= 0 && nextY < mapHeight && nextX >= 0 && nextX < mapWidth && map[nextY][nextX] != wall){
                playerX = nextX;
                playerY = nextY;

                // Door + key (Ayra)
                // Check if player position sama dgn key so key = true
                // Check position player dgn door kalau key = false lock kalau true boleh bukak
                // Kalau door boleh bukak prompt quiz

                // Trap (Ezryn)
                // Check if position player sama dgn trap and turunkan masa kalau sama

                // Timer (Aasim)
                /* 
                Timer (number of turns turun/move) kalau boleh buat in seconds
                timer without library lain buat la kalau x just ikut turn je
                */ 


            } else {
                cout << "Cannot move there." << endl;
            }

             // Sweeper (Ezryn)
             // Sweeper duration dgn reveal (??)

        }

        //(Aasim) (Game over/Win)
        // Check for Win Condition (depends if Ayra set wincon door or not) Kalau x set xyah buat 
        // Check timer kalau timer 0 break;

    } 

    cout << "\nGame Over!" << endl;
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

void mainGame(const vector<vector<char>>& map, int pX, int pY, int radius)
{
    clearScreen();
    int mapHeight = map.size();
    int mapWidth = 0;
    if (mapHeight > 0) {
        mapWidth = map[0].size();
    }

    // Status (key/time left) (Aasim)
    cout << "Position: (" << pX << "," << pY << ")" << endl; // Basic info

    //Border
    cout << "+";
    for (int i = 0; i < mapWidth; ++i) { cout << "-"; }
    cout << "+" << endl;

    //Map
    for (int y = 0; y < mapHeight; ++y) {
        cout << "|";
        for (int x = 0; x < mapWidth; ++x) {
            int distance = abs(pX - x) + abs(pY - y);
            // Radius tukar after sweeper active/not (tbd)
            int currentRadius = radius; 

            if (distance <= currentRadius) {
                if (x == pX && y == pY) {
                    cout << player;
                }
                //Ezryn & Ayra: Location key+trap
                // Key data location + revealed/not + found/not (Ayra)
                // Trap data on or off + location (ezryn)
                // Sweeper status (ezryn) On or off
            
                else {
                    cout << map[y][x]; 
                }
            } else {
                cout << fogofwar;
            }
        }
        cout << "|" << endl;
    }

    cout << "+";
    for (int i = 0; i < mapWidth; ++i) { cout << "-"; }
    cout << "+" << endl;

    //sini print status (Aasim)


    cout << "Move (w/a/s/d) | Sweeper (e) | Quit (q): ";
}
