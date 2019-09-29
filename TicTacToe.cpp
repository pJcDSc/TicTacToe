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
    cout << "Please enter a row followed by a column" << endl;

    //Read input
    char in[4] = "";
    while(!isValid) {
      cin.get(in, 4);
      cin.clear();
      cin.ignore(999, '\n');

      //Ensure input is 2 characters
      if (strlen(in) != 2) {
	cout << "Please enter exactly two characters" << endl;
	continue;
      }

      //Make sure input is valid
      if(toupper(in[0]) - 'A' > 2 || toupper(in[0]) - 'A' < 0 ||
	 in[1] - '1' > 2 || in[1] - '1' < 0) {
	cout << "Please enter a valid row / column" << endl;
	continue;
      }

      //Get corresponding row and column
      rowInd = toupper(in[0]) - 'A';
      colInd = in[1] - '1';
      
      //Make sure the spot is not taken
      if(board[rowInd][colInd] != BLANK) {
	cout << "That spot is taken!" << endl;
	continue;
      }

      isValid = true;
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

      //Loop until break
      while(true) {

	//Read again
	char again;
	cin >> again;
	cin.clear();
	cin.ignore(999, '\n');
      
	//If they don't want to play again set 'playing' variable to false to exit while loop
	cout << again << endl;
	if (again == 'n') {
	  cout << "Thanks for playing!" << endl;
	  playing = false;
	  break;
	} else if (again != 'y') {
	  cout << "Please enter either \"y\" or \"n\"." << endl;
	} else break;
	
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
      if (playing){
	printBoard(board);
      }
    }

    turn %= 2;
  }
}
