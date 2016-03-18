/* Taylor Tobin
 * CECS 282 - Homework 6
 * 3/8/16
 *
 * Purpose: Create the Game BattleShip
 */

#include <iostream>
#include <cstdlib> //allows for the use of rand()

using namespace std;

//Prototypes
char validChar();
int getCharVal(char entry);
int validInt();
void blankBoard(char arr [] [15]);
void placeFleet(char arr [] [15]);
void fire(int &tcount, int &fcount, int &dcount, int &ccount, int &Ccount, int x, int y, char arr [] [15]);
void checkSink(int &tcount, int &fcount, int &dcount, int &ccount, int &Ccount);
int fleetSink(char arr [][15]);
void printBoard(char board[][15]);

int main(int argc, const char * argv[])
{
    srand(time(NULL));
    
    cout << "This is the game BattleShip" << endl;
    
    //Create and populate blank board
    char gameBoard[15][15];
    char playerBoard[15][15];
    blankBoard(gameBoard);
    blankBoard(playerBoard);
    
    //randomly place pieces on the board
    placeFleet(gameBoard);
    
    printBoard(playerBoard);
    
    cout << endl;
    
    //for testing random board generation
    printBoard(gameBoard);
    
    cout << "Gameboard has been generated -- time to play" << endl;
    cout << "you get 60 shots before game over" << endl;
    //enter something to quit
    int count=0;
    int x=0, y=0;
    int tcount=0, fcount=0, dcount=0, ccount=0, Ccount=0;
    for(int i=0; i < 60; i++)
    {
        cout << "Enter an x-coordinate for target point (a-o)" << endl;
        x = getCharVal(validChar());
        x--;
        
        cout << "Enter an y-coordinate for target point" << endl;
        y = validInt();
        y--;
        
        playerBoard[y][x] = 'X';
        fire(tcount,fcount,dcount,ccount,Ccount,x,y,gameBoard);
        checkSink(tcount,fcount,dcount,ccount,Ccount);
        
        if(fleetSink(gameBoard) == 1)
        {
            cout << "You won the Battle" << endl;
            printBoard(gameBoard);
            break;
        }
        printBoard(playerBoard);
        count++;
    }
    if(count == 59)
    {
        cout << "Exceeded number of shots, you loose" << endl;
        printBoard(gameBoard);
    }
}

char validChar()
{
    char input;
    while(true)
    {
        cin >> input;
        if(cin.fail() || input > 'o')
        {
            cout << "Invalid input, must be an integer between 1-15, please re-enter" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            break;
    }
    return input;
}

int getCharVal(char entry)
{
    if(entry == 'a')
        return 1;
    if(entry == 'b')
        return 2;
    if(entry == 'c')
        return 3;
    if(entry == 'd')
        return 4;
    if(entry == 'e')
        return 5;
    if(entry == 'f')
        return 6;
    if(entry == 'g')
        return 7;
    if(entry == 'h')
        return 8;
    if(entry == 'i')
        return 9;
    if(entry == 'j')
        return 10;
    if(entry == 'k')
        return 11;
    if(entry == 'l')
        return 12;
    if(entry == 'm')
        return 13;
    if(entry == 'n')
        return 14;
    if(entry == 'o')
        return 15;
    return 0;
}

int validInt()
{
    int input;
    while(true)
    {
        cin >> input;
        if(cin.fail() || input > 15)
        {
            cout << "Invalid input, must be an integer between 1-15, please re-enter" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            break;
    }
    return input;
}

void blankBoard(char arr [] [15])
{
    for( int i = 0; i < 15; i++ )
    {
        for( int j = 0; j < 15; j++)
        {
            arr[i][j] = '~';
        }
    }
}

void placeFleet(char arr [] [15])
{
    int size=14, two=2, three=3, four=4;
    
    //frigate
    while (true)
    {
        int fx = two + rand() % ((two-size) +1); //provides a random number between 2-12
        int fy = two + rand() % ((two-size) +1);
        //makes sure piece isn't placed of the boarder
        int dir = rand() % 4+1; //uses the rand() method to get a random value between 1-4 inclusive
        //provides piece orientation
        if (arr[fy][fx] == '~')
        {
            arr[fy][fx] = 'f';
            
            if (dir == 1 && arr[++fy][fx] == '~')
                arr[fy][fx] = 'f';
            if (dir == 2 && arr[--fy][fx] == '~')
                arr[fy][fx] = 'f';
            if (dir == 3 && arr[fy][++fx] == '~')
                arr[fy][fx] = 'f';
            if (dir == 4 && arr[fy][--fx] == '~')
                arr[fy][fx] = 'f';
            break;
        }
        
    }
    
    //tender
    while (true)
    {
        int tx = two + rand() % ((two-size) +1); //uses the rand() method to get a random value between 2-12
        int ty = two + rand() % ((two-size) +1);
        //makes sure piece isn't placed of the boarder
        int dir = rand() % 4+1; //uses the rand() method to get a random value between 1-4 inclusive
        //provides piece orientation
        if(arr[ty][tx] == '~')
        {
            arr[ty][tx] = 't';
            
            if (dir == 1 && arr[++ty][tx] == '~')
                arr[ty][tx] = 't';
            if (dir == 2 && arr[--ty][tx] == '~')
                arr[ty][tx] = 't';
            if (dir == 3 && arr[ty][++tx] == '~')
                arr[ty][tx] = 't';
            if (dir == 4 && arr[ty][--tx] == '~')
                arr[ty][tx] = 't';
            break;
        }
    }
    
    //destroyer
    while (true)
    {
        int dx = three + rand() % ((three-size) +1); //uses the rand() method to get a random value between 3-11
        int dy = three + rand() % ((three-size) +1);
        //makes sure piece isn't placed of the boarder
        int dir = rand() % 4+1; //uses the rand() method to get a random value between 1-4 inclusive
        //provides piece orientation
        if(arr[dy][dx] == '~')
        {
            arr[dy][dx] = 'd';
            
            if (dir == 1 && arr[++dy][dx] == '~'){
                arr[dy][dx] = 'd';
                if(arr[++dy][dx] == '~')
                    arr[dy][dx] = 'd';
            }
            if (dir == 2 && arr[--dy][dx] == '~'){
                arr[dy][dx] = 'd';
                if(arr[--dy][dx] == '~')
                    arr[dy][dx] = 'd';
            }
            if (dir == 3 && arr[dy][++dx] == '~'){
                arr[dy][dx] = 'd';
                if(arr[dy][++dx] == '~')
                    arr[dy][dx] = 'd';
            }
            if (dir == 4 && arr[dy][--dx] == '~'){
                arr[dy][dx] = 'd';
                if(arr[dy][--dx] == '~')
                    arr[dy][dx] = 'd';
            }
            break;
        }
    }
    
    //cruiser
    while (true)
    {
        int cx = three + rand() % ((three-size) +1); //uses the rand() method to get a random value between 3-11
        int cy = three + rand()  % ((three-size) +1);
        //makes sure piece isn't placed of the boarder
        int dir = rand() % 4+1; //uses the rand() method to get a random value between 1-4 inclusive
        //provides piece orientation
        if(arr[cy][cx] == '~')
        {
            arr[cy][cx] = 'c';
            if (dir == 1 && arr[++cy][cx] == '~'){
                arr[cy][cx] = 'c';
                if(arr[++cy][cx] == '~')
                    arr[cy][cx] = 'c';
            }
            if (dir == 2 && arr[--cy][cx] == '~'){
                arr[cy][cx] = 'c';
                if(arr[--cy][cx] == '~')
                    arr[cy][cx] = 'c';
            }
            if (dir == 3 && arr[cy][++cx] == '~'){
                arr[cy][cx] = 'c';
                if(arr[cy][++cx] == '~')
                    arr[cy][cx] = 'c';
            }
            if (dir == 4 && arr[cy][--cx] == '~'){
                arr[cy][cx] = 'c';
                if(arr[cy][--cx] == '~')
                    arr[cy][cx] = 'c';
            }
            break;
        }
    }
    
    //carrier
    while (true)
    {
        int cax = four + rand()  % ((four-size) +1); //uses the rand() method to get a random value between 4-10
        int cay = four + rand()  % ((four-size) +1);
        //makes sure piece isn't placed of the boarder
        int dir = rand() % 4+1; //uses the rand() method to get a random value between 1-4 inclusive
        //provides piece orientation
        if(arr[cay][cax] == '~')
        {
            arr[cay][cax] = 'C';
            if (dir == 1 && arr[++cay][cax] == '~'){
                arr[cay][cax] = 'C';
                if(arr[++cay][cax] == '~')
                    arr[cay][cax] = 'C';
                if(arr[++cay][cax] == '~')
                    arr[cay][cax] = 'C';
            }
            if (dir == 2 && arr[--cay][cax] == '~'){
                arr[cay][cax] = 'C';
                if(arr[--cay][cax] == '~')
                    arr[cay][cax] = 'C';
                if(arr[--cay][cax] == '~')
                    arr[cay][cax] = 'C';
            }
            if (dir == 3 && arr[cay][++cax] == '~'){
                arr[cay][cax] = 'C';
                if(arr[cay][++cax] == '~')
                    arr[cay][cax] = 'C';
                if(arr[cay][++cax] == '~')
                    arr[cay][cax] = 'C';
            }
            if (dir == 4 && arr[cay][--cax] == '~'){
                arr[cay][cax] = 'C';
                if(arr[cay][--cax] == '~')
                    arr[cay][cax] = 'C';
                if(arr[cay][--cax] == '~')
                    arr[cay][cax] = 'C';
            }
            break;
        }
    }
}

void fire(int &tcount, int &fcount, int &dcount, int &ccount, int &Ccount, int x, int y, char arr [] [15])
{
    if(arr[y][x] == 't')
    {
        tcount++;
        arr[y][x] = 'H';
        cout << "HIT" << endl;
    }
    else if(arr[y][x] == 'f')
    {
        fcount++;
        arr[y][x] = 'H';
        cout << "HIT" << endl;
    }
    else if(arr[y][x] == 'd')
    {
        dcount++;
        arr[y][x] = 'H';
        cout << "HIT" << endl;
    }
    else if(arr[y][x] == 'c')
    {
        ccount++;
        arr[y][x] = 'H';
        cout << "HIT" << endl;
    }
    else if(arr[y][x] == 'C')
    {
        Ccount++;
        arr[y][x] = 'H';
        cout << "HIT" << endl;
    }
    else
    {
        arr[y][x] = 'M';
        cout << "MISS" << endl;
    }
}

void checkSink(int &tcount, int &fcount, int &dcount, int &ccount, int &Ccount)
{
    if(tcount == 2)
        cout << "You sunk the Tender!" << endl;
    if(fcount == 2)
        cout << "You sunk the Frigate!" << endl;
    if(dcount == 3)
        cout << "You sunk the Destroyer!" << endl;
    if(ccount == 3)
        cout << "You sunk the Cruiser!" << endl;
    if(Ccount ==4)
        cout << "You sunk the Carrier!" << endl;
}

int fleetSink(char arr [][15])
{
    for( int i = 0; i < 25; i++ )
    {
        for( int j = 0; j < 25; j++)
        {
            if(arr[i][j] == 't' || arr[i][j] == 'f' || arr[i][j] == 'd' || arr[i][j] == 'c' || arr[i][j] == 'C')
            {
                return 0;
            }
        }
    }
    cout << "FLEET SUNK" << endl;
    return 1;
}

void printBoard(char board[][15])
{
    for( int i = 0; i < 15; i++ )
    {
        for( int j = 0; j < 15; j++)
        {
            cout << board[i][j] << " ";
            
        }
        cout << endl;
    }
}


