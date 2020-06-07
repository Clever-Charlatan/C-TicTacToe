/**************************************************************************
 *   Author    :  John Chen
 *   Assn #10  :  Tic Tac Toe
 *   CLASS     :  CS 002
 *   SECTION   :  MTRF: 7a - 12p
 *   Due Date  :  7/21/19
 *************************************************************************/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
/**************************************************************************
 *
 * TIC TAC TOE
 * ________________________________________________________________________
 * This program accepts multiple letters that correlate with a location on
 * a tic-tac-tow grid. Then, based on the turn, those letters become either
 * an 'x' or an 'o'. The first to get three in a row wins.
 * ________________________________________________________________________
 * INPUT:
 *   letter: Letter of the character in a certain board position
 *           -> input from user
 *
 * OUTPUT:
 *   Will output the a board grid with letters and 'x' and 'o'
 *************************************************************************/

//Global constant for the clearScreen function
const bool CLEAR_SCREEN = true;

/**************************************************************************
* clearScreen
*  This function clears the screen with an output.
*   - returns nothing -> It will simply clear the screen
* ************************************************************************/
void clearScreen();

/**************************************************************************
* drawBoard
*  This function receives a board vector and then will draw the board with
*  the grid along with the letters and 'x' and 'o' based on the board.
*   - returns nothing -> It will output the board (grid and letters)
* ************************************************************************/
void drawBoard(const vector <char> &board); //IN - the board state

/**************************************************************************
* initVector
*  This function receives a vector and initializes the elements of the
*  vector to the letters of the alphabet up to 26 elements.
*   - returns nothing -> It will initialize board to the alphabet
* ************************************************************************/
void initVector(vector <char> &v); //In - the board vector initialized

/**************************************************************************
* convertPosition
*  This function receives a letter from the grid based on the vector and
*  then it will return the numerical position of that letter in the board
*  vector.
*   - returns int -> This will be numerical position of the letter
* ************************************************************************/
int convertPosition(char position); //IN - the letter to be converted

/**************************************************************************
* validPlacement
*  This function receives the board vector and the position on the vector
*  and then it will test for whether it is possible for input.
*   - returns bool -> This will be whether the position is possible
* ************************************************************************/
bool validPlacement(const vector <char> &board, //IN - the board tested
                    int position);              //IN - the board position

/**************************************************************************
* getPlay
*  This function prompts the user for a letter position, convert it into a
*  numerical position on the vector. Then, it wil be tested for whether it
*  is a valid position for input, later returning that position if valid.
*   - returns int -> This will be the position of the selected one
* ************************************************************************/
int getPlay(const vector <char> &board); //IN - the board vector selected

/**************************************************************************
* gameWon
*  This function receives a board vector and then it will test whether at
*  any point the game has any winning combinations.
*   - returns bool -> This will be whether the game has been won
* ************************************************************************/
bool gameWon(const vector <char> &board); //IN - the board vector tested

/**************************************************************************
* boardFull
*  This function receives a board vector and test whether all the slots are
*  filled with 'x' or 'o' and will return whether it is full or not.
*   - returns bool -> This will be whether the vector board is full
* ************************************************************************/
bool boardFull(const vector <char> &board); //IN - the board vector tested

// Global constants for player representation
const int PLAYER1 = 0;
const int PLAYER2 = 1;

int main()
{
    //constants
    vector <char> board(9); //CALC - the board vector with the letters
    int curPlay;            //CALC - the current vector position at play
    int turn = PLAYER1;     //CALC - the current turn, either 0 or 1
    bool val;               //CALC - te state of the game

    //PROCESSING: Initialize the state of the game to be true
    val = true;

    //PROCESSING: Initializes the state of the board to alphabetical order
    //            with no 'x' or 'o' yet
    //initVectr - Will give each vector element a corresponding letter in
    //            the alphabet
    initVector(board);

    //PROCESSING: Creates an empty board to display with letters
    //drawBoard - Draws the current state of the board in a grid
    drawBoard(board);

    //PROCESSING: Game will run until the state of the game is false
    while(val)
    {
        //PROCESSING: Will get a letter and test to see if it is within
        //            bounds, and if not it will run again
        /// TODO: Get a play
        do
        {
        //getPlay - Gets a letter from the user and converts to an integer
        //          position in the board vector to test if it is valid
        curPlay = getPlay(board);
        }
        while(curPlay == -1);

        //PROCESSING: Will determine which current play is is going to be
        //            on which player's turn and whether it will be an 'x'
        //            or an 'o'
        if(turn == PLAYER1)
            board.at(curPlay) = 'x';
        else if(turn == PLAYER2)
            board.at(curPlay) = 'o';

        //PROCESSING: Will switch the turn after the board has been set
        if(turn == PLAYER1)
            turn = PLAYER2;
        else
            turn = PLAYER1;

        //PROCESSING: Reouputs the board
        //drawBoard - Will redraw the board with the letters and signs
        drawBoard(board);

        //PROCESSING: End validation will stop the program if the board is
        //            full or if the game has been won
        //boardFull - Will check if the board is full
        if(boardFull(board))
            val = false;
        //gameWon - Will check if anybody has a winning combination
        else if(gameWon(board))
            val = false;
        else val = true;
    }

    //PROCESSING: Determine the winner and output the appropriate message
    //            based on who's turn it is
    if(gameWon(board))
    {
        if(turn == PLAYER1)
            cout << "Player 2 wins!!" << endl;
        else
            cout << "Player 1 wins!!" << endl;
    }
    else
        cout << "No one wins." << endl;
}

/**************************************************************************
 *
 * FUNCTION clearScreen
 *
 * ________________________________________________________________________
 * This function receives nothing and clears the screen by utilizing an
 * escape character sequence - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      None
 *
 * POST-CONDITIONS
 *      This function will clear the screen.
 *
 * ***********************************************************************/
void clearScreen()
{
    cout << endl;

    //PROCESSING: Will always clear the screen using this escape sequence
    if (CLEAR_SCREEN)
        //OUTPUT: Escape sequence will clear the screen
        cout << "\033c";

    cout << endl;
}

/**************************************************************************
 *
 * FUNCTION drawBoard
 *
 * ________________________________________________________________________
 * This function receives the board vector then outputs the board with the
 * elements of the vector in a grid - returns board grid.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      board: the board vector with the character and sign elements
 *
 * POST-CONDITIONS
 *      This function will output a board grid with letters and signs.
 *
 * ***********************************************************************/
void drawBoard(const vector <char> &board) //IN - the board state
{
    //clearScreen - Will clear the screen
    clearScreen();

    //PROCESSING: Will cycle through all of the elements by three
    for (int i = 0; i < 9; i += 3)
    {
        //OUTPUT: Display the grid with the elements from the vector
        cout << "  " << board.at(i) << "  |  " << board.at(i + 1) << "  |  "
            << board.at(i + 2) << "  " << endl;
        if (i < 6)
            cout << "-----|-----|-----" << endl;
    }
    cout << endl;
}

/**************************************************************************
 *
 * FUNCTION initVector
 *
 * ________________________________________________________________________
 * This function receives the board vector then returns it initialized with
 * the letters of the alphabet - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      v: the board vector with a size not over 26

 * POST-CONDITIONS
 *      This function will initialize the vector with the letters of the
 *      alphabet
 *
 * ***********************************************************************/
void initVector(vector <char> &v) //In - the board vector initialized
{
    //contants
    char alphabet[27];
    size_t size;

    //Initialize the constants appropriately
    strcpy(alphabet, "abcdefghijklmnopqrstuvwxyz");
    size = v.size();

    //PROCESSING: Runs through all of the elements in the alphabet
    for(unsigned int i = 0; i < size; i++)
        //PROCESSING: Assigns the elements of the vector with the letters
        //            of the a;phabet
        v.at(i) = (alphabet[i]);
}

/**************************************************************************
* convertPosition
*  This function receives a letter from the grid based on the vector and
*  then it will return the numerical position of that letter in the board
*  vector.
*   - returns int -> This will be numerical position of the letter
* ************************************************************************/

/**************************************************************************
 *
 * FUNCTION convertPosition
 *
 * ________________________________________________________________________
 * This function receives the letter position of a certain square in the
 * grid then it will output the numerical position of that letter
 *  - returns int.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      position: the selected character in the grid
 *
 * POST-CONDITIONS
 *      This function will output an int that represents the position of
 *      letter in the vector elements
 *
 * ***********************************************************************/
int convertPosition(char position) //IN - the letter to be converted
{
    //constants
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int index;

    //PROCESSING: Initialized with the
    index = static_cast<int>(alphabet.find(position));

    //PROCESSING: As long as the index is found, it will be outputted
    if(index > -1)
        return index;
    return -1;
}

/**************************************************************************
 *
 * FUNCTION validPlacement
 *
 * ________________________________________________________________________
 * This function receives the boar vector and the integer position of the
 * selected placement then outputs whether the placement is valid
 *  - returns bool.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      board   : the boar vector with the characters
 *      position: the position of the character in the board vector
 *
 * POST-CONDITIONS
 *      This function will output whether the placement is possible
 *
 * ***********************************************************************/
/// @brief Predicate function to determine if a spot in board is available.
/// @param board the current tic-tac-toe board
/// @param position is an index into vector to check if available
/// @return true if position's state is available (not marked) AND is in bounds
bool validPlacement(const vector <char> &board, //IN - the board tested
                    int position)               //IN - the board position
{
    //PROCESSING: Checks to see if position is within bounds and then
    //            checks to see if it is not an 'x' or 'o' in order for a
    //            placement to be possible
    if(position < static_cast<int>(board.size()))
    {
        if(board.at(position) != 'x' && board.at(position) != 'o')
            return true;
    }
    return false;
}

/**************************************************************************
 *
 * FUNCTION upadteUnsolved
 *
 * ________________________________________________________________________
 * This function receives the board vector and prompts for a character then
 * outputs an integer position in the board vector - returns int.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      board: the board vector
 *
 * POST-CONDITIONS
 *      This function will the integer position of a letter in the board
 *
 * ***********************************************************************/
int getPlay(const vector <char> &board) //IN - the board vector selected
{
    //constants
    char letter;
    int position;

    //INPUT & OUTPUT: Prompt the user for a position on board and store it
    cout << "Please choose a position: ";
    cin >> letter;
    cout << endl;

    //converPosition - Wil convert the letter to the integer position
    position = convertPosition(letter);

    //validPlacement - Will check to see if the positon is valid for board
    //PROCESSING: Will only return the position if the position is valid
    if(validPlacement(board, position))
        return position;
    return -1;
}

/**************************************************************************
 *
 * FUNCTION gameWon
 *
 * ________________________________________________________________________
 * This function receives the board vector then outputs whether there is a
 * game winning combination on the board - returns bool.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      board: the board vector in its current state
 *
 * POST-CONDITIONS
 *      This function will output whether there is a game winning
 *      combination on the board.
 *
 * ***********************************************************************/
bool gameWon(const vector <char> &board) //IN - the board vector tested
{
    //PROCESSING: Looks through all possible game winning combos
    if(board.at(0) == board.at(1) && board.at(0) == board.at(2))
        return true;
    else if(board.at(3) == board.at(4) && board.at(3) == board.at(5))
        return true;
    else if(board.at(6) == board.at(7) && board.at(6) == board.at(8))
        return true;
    else if(board.at(0) == board.at(3) && board.at(0) == board.at(6))
        return true;
    else if(board.at(1) == board.at(4) && board.at(1) == board.at(7))
        return true;
    else if(board.at(2) == board.at(5) && board.at(2) == board.at(8))
        return true;
    else if(board.at(0) == board.at(4) && board.at(0) == board.at(8))
        return true;
    else if(board.at(2) == board.at(4) && board.at(2) == board.at(6))
        return true;
    return false;
}

/**************************************************************************
 *
 * FUNCTION boardFull
 *
 * ________________________________________________________________________
 * This function receives the board vector and tests to see if it is full
 * then outputs whether the board is full - returns bool.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      board: the board vector
 *
 * POST-CONDITIONS
 *      This function will output whether the board is full of plater signs
 *
 * ***********************************************************************/
bool boardFull(const vector <char> &board) //IN - the board vector tested
{
    //PROCESSING: Cycle through all the elements in the vector
    for(unsigned int i = 0; i < board.size(); i++)
    {
        //PROCESSING: Will check to see if any of the elements are an 'x'
        //            or an 'o'
        if(board.at(i) != 'x' && board.at(i) != 'o')
            return false;
    }
    return true;
}
