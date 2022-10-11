/*
Conway's Game of Life (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells,
each of which is in one of two possible states, live or dead (or populated and unpopulated, respectively).
Every cell interacts with its eight neighbors, which are the cells that are horizontally, vertically,
or diagonally adjacent. At each step in time, the following transitions occur:

  Any live cell with fewer than two live neighbors dies, as if by underpopulation.
  Any live cell with two or three live neighbors lives on to the next generation.
  Any live cell with more than three live neighbors dies, as if by overpopulation.
  Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

*/

#include <iostream>
#include <string>
using namespace std;

// ROW, COL define the size of the current universe
const int ROW = 5;
const int COL = 4;
const bool SHOW_NEIGHBOR_COUNT = false;  //for debugging purposes

// Utility - Neighbors. Below arrays details all 8 possible movements 
// from a cell (top, right, bottom, left and 4 diagonal moves)
int rowCell[] = { -1, -1, -1,  0,  1, 0, 1, 1 };
int colCell[] = { -1,  1,  0, -1, -1, 1, 0, 1 };

// Prototypes
bool isSafe(int matrix[ROW][COL], int x, int y);
int  countNeighbors(int board[ROW][COL], int r, int c);
void printBoard(int board[ROW][COL], string msg);
bool generationsAreIdentical(int board1[ROW][COL], int board2[ROW][COL], int r);
void makeCurrentGenSameAsNextGen(int board1[][COL], int board2[][COL], int r);

// ------------------------------------------------------------------------------------
int main()
{

    int currentGen[ROW][COL];
    int nextGen[ROW][COL];

    //Randomly populate the first generation (Generation 1)
    //srand(time(NULL));
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            currentGen[i][j] = rand() % 2;  //assign 0 or 1
        }
    }
    int generationCounter = 1;
    printBoard(currentGen, "Generation " + to_string(generationCounter++));

    do
    {

        // Observe the current generation board, for each cell count its neighbors 
        // and make decisions about the future of the cell
        if (SHOW_NEIGHBOR_COUNT)  cout << "Count of neighbors\n";
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                nextGen[i][j] = 0;      //Default - assume this cell will be dead in the next generation

                int totalNeighbors = countNeighbors(currentGen, i, j);
                if (SHOW_NEIGHBOR_COUNT) cout << "  " << totalNeighbors << "   ";

                //tell what will happen to the next generation
                if (currentGen[i][j] == 1)  //consider a live cell
                {
                    if (totalNeighbors < 2)
                        nextGen[i][j] = 0;      //dies - underpopulation
                    if (totalNeighbors == 2 || totalNeighbors == 3)
                        nextGen[i][j] = 1;      //lives 
                    if (totalNeighbors > 3)
                        nextGen[i][j] = 0;      //dies - overpopulation
                }
                else
                {
                    //working with a dead cell
                    if (totalNeighbors == 3)
                        nextGen[i][j] = 1;      //lives - reproduction
                }


            }
            if (SHOW_NEIGHBOR_COUNT)  cout << endl;
        }

        printBoard(nextGen, "\nGeneration " + to_string(generationCounter++));

        cout << "\nType q to quit [any other to continue]: ";
        char c = cin.get();
        if (c == 'q' || c == 'Q') break;

        //copy nextGen board on top of currentGen, clear nextGen
        if (generationsAreIdentical(currentGen, nextGen, ROW))
        {
            cout << "Still life - No more generational changes\n";
            break;
        }
        else
        {
            makeCurrentGenSameAsNextGen(currentGen, nextGen, ROW);
        }
               

    } while (true);

    return 0;
}

//-----------------------------------------------------------------------------------------------
// Function to check if it is safe to go to position (x, y)
// from current position. The function returns false if (x, y)
// is not valid matrix coordinates or (x, y) represents water or
// position (x, y) is already visited
bool isSafe(int matrix[ROW][COL], int x, int y) {
    return (x >= 0) && (x < ROW)   		// inside of the board (valid row)
        && (y >= 0) && (y < COL);   	// inside of the board (valid column)
}

//Count neighbors of cell [r,c] using the utility arrays
int countNeighbors(int board[ROW][COL], int r, int c)
{
    int counter = 0;
    for (int i = 0; i < 8; i++)
    {
        int x = r + rowCell[i];
        int y = c + colCell[i];
        if (isSafe(board, x, y) && board[x][y] == 1)
        {
            counter++;
        }
    }
    return counter;
}

void printBoard(int board[ROW][COL], string msg)
{
    //print universe
    cout << msg << endl;

    for (int i = 0; i < ROW; i++) {
        cout << " ";
        for (int j = 0; j < COL; j++) {
            cout << "  " << board[i][j] << "   ";
        }
        cout << endl;
    }
}

bool generationsAreIdentical(int board1[ROW][COL], int board2[ROW][COL], int r)
{
    //return true if both boards are identical, false otherwise
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (board1[i][j] != board2[i][j])
                return false;
        }
    }
    return true;
}

void makeCurrentGenSameAsNextGen(int board1[][COL], int board2[][COL], int r)
{
    //copy nextGen data on top of currentGen, clear nextGen
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            board1[i][j] = board2[i][j];
            board2[i][j] = 0;
        }
    }

}
