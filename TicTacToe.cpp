/*
 * Author: Peter Jin
 * Date: 9/9/19
 * TicTacToe: Simple console game of tictactoe. normal rules. X starts.
 */

#include <iostream>
#include <cstring>

using namespace std;

//Function to print board 
void printBoard(int board[3][3]) {

  //change icons here
  char letters[3] = {' ', 'X', 'O'};

  //print column indicators
  cout << "  1 2 3" << endl;

  //for each row print row indicator followed by plays
  for(int i = 0; i < 3; i++){
    cout << (char)(i + 65) << " ";
    for(int j = 0; j < 3; j++){
      cout << letters[board[i][j]] << " ";
    }
    cout << endl;
  }
}
//Function to check for win, using every combination of win
bool checkWin (int board[3][3], int player) {
  if (board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] == player) return true;
  if (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] == player) return true;
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == player) return true;
  if (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] == player) return true;
  if (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] == player) return true;
  if (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] == player) return true;
  if (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] == player) return true;
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == player) return true;
  return false;
}

//Note: This function does not check for wins. Call checkwin before calling this
//Function to check for ties. checks if every spot is NOT empty
bool checkTie (int board[3][3]){
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if (board[i][j] == 0) return false;
    }
  }
  return true;
}

int main() {
  int BLANK = 0;
  int X = 1;
  int O = 2;

  //Make a new board, initialize it to all blank
  int board[3][3];
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      board[i][j] = BLANK;
    }
  }

  //Print the board before game starts
  printBoard(board);
  
  bool playing = true;
  int xWins = 0;
  int oWins = 0;
  int turn = 0;

  //Continue looping while playing
  while (playing) {
    char inRow = ' ';
    char inCol = ' ';
    bool isValid = false;
    int rowInd = 0;
    int colInd = 0;

    //Tell user whose turn it is
    cout << "It is " << (turn ? 'O' : 'X') << "'s turn." << endl;

    //Loop while the input is invalid
    while (!isValid) {

      //Prompt user to input a row letter
      do {
        cout << "Please enter the row (A-C)." << endl;
        cin >> inRow;
	cin.clear();
	cin.ignore(999, '\n');
	inRow = toupper(inRow);
      } while (inRow != 'A' && inRow != 'B'&& inRow != 'C');

      //Prompt user to input a column number
      do {
        cout << "Please enter the column (1-3)." << endl;
        cin >> inCol;
	cin.clear();
	cin.ignore(999, '\n');
      } while (inCol != '1' && inCol != '2'&& inCol != '3');

      //Translate input to row and column indeces
      rowInd = inRow - 'A';
      colInd = inCol - '1';

      //If the spot is taken prompt user to input a new spot
      if (board[rowInd][colInd] != BLANK) {
	cout << "That spot is taken! Please choose another spot." << endl;
      }
      else{
	isValid = true;
      }
    }

    //Add the play to the board
    board[rowInd][colInd] = ++turn;

    //Print the board
    printBoard(board);

    //Boolean flag activated by game ending (tie or win)
    bool gameEnd = false;

    //Only the person whose turn it is can win
    if(checkWin(board, turn)) {
      if (turn == X) xWins ++;
      else oWins ++;

      //Tell user who won and current win counts
      cout << (turn - 1 ? 'O' : 'X') << " WINS! X has " << xWins << " win(s) and O has " << oWins << " win(s)." << endl;
      gameEnd = true;
    }
    else if (checkTie(board)) {
      
      //Tell user its a tie and current win counts
      cout << "It's a tie! X has " << xWins << " win(s) and O has " << oWins << " win(s)." << endl;
      gameEnd = true;
    }

    //Once the game is over
    if (gameEnd) {

      //Prompt user if they want to play again
      cout << "Play again? (y/n)" << endl;

      char again;
      cin >> again;

      //If they don't set playing variable to false to exit while loop
      if (again == 'n') {
	cout << "Thanks for playing!" << endl;
	playing = false;
      } 

      //Reset turn
      turn = 0;

      //Reset the board
      for(int i = 0; i < 3; i++) {
	for(int j = 0; j < 3; j++) {
	  board[i][j] = BLANK;
	}
      }

      //Print pregame board
      if (again != 'n'){
	printBoard(board);
      }
    }

    turn %= 2;
  }
}
