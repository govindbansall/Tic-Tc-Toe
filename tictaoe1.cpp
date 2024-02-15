#include <iostream>
#include <vector>
#include <random>

using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char COMPUTER = 'O'; // Computer always plays as 'O'

// Function to display the game board
void displayBoard(const vector<char>& board) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cout << board[i * 3 + j] << " ";
    }
    cout << endl;
  }
}

// Function to check if a player has won
bool checkWin(const vector<char>& board, char player) {
  // Check rows and columns
  for (int i = 0; i < 3; ++i) {
    if (board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player) {
      return true;
    }
    if (board[i] == player && board[i + 3] == player && board[i + 6] == player) {
      return true;
    }
  }

  // Check diagonals
  if (board[0] == player && board[4] == player && board[8] == player) {
    return true;
  }
  if (board[2] == player && board[4] == player && board[6] == player) {
    return true;
  }

  return false;
}

// Function to get a valid player move

int getPlayerMove(char player, const vector<char>& board) {
  int move;
  do {
    cout << "Player " << player << ", enter your move (1-9): ";
    cin >> move;

    // Check if the move is already occupied
    if (move < 1 || move > 9 || board[move - 1] != EMPTY) {
      cout << "This cell is already occupied. Please choose another move." << endl;
    }
  } while (move < 1 || move > 9 || board[move - 1] != EMPTY);
  return move - 1;
}

// Function to make a random computer move
int getComputerMove(const vector<char>& board) {
  vector<int> emptyCells;
  for (int i = 0; i < 9; ++i) {
    if (board[i] == EMPTY) {
      emptyCells.push_back(i);
    }
  }
  return emptyCells[rand() % emptyCells.size()];
}

// Function to play the game against the computer
void playOnePlayer(char player) {
  vector<char> board(9, EMPTY);
  char currentPlayer = player;

  while (true) {
    // Display the game board
    displayBoard(board);

    // Get player move
    int move;
    if (currentPlayer == player) {
      move = getPlayerMove(currentPlayer, board);
    } else {
      // Computer move
      move = getComputerMove(board);
      cout << "Computer plays move " << move + 1 << endl;
    }

    // Place the move on the board
    board[move] = currentPlayer;

    // Check for win or draw
    if (checkWin(board, currentPlayer)) {
      displayBoard(board);
      cout << "Player " << currentPlayer << " wins!" << endl;
      break;
    }

    bool isDraw = true;
    for (char cell : board) {
      if (cell == EMPTY) {
        isDraw = false;
        break;
      }
    }
    if (isDraw) {
      displayBoard(board);
      cout << "It's a draw!" << endl;
      break;
    }

    // Switch players
    currentPlayer = (currentPlayer == player) ? COMPUTER : player;
  }
}


void playTwoPlayer() {
  vector<char> board(9, EMPTY);
  char currentPlayer = PLAYER_X;

  while (true) {
    // Display the game board
    displayBoard(board);

    // Get player move
    int move = getPlayerMove(currentPlayer, board);

    // Place the move on the board
    board[move] = currentPlayer;

    // Check for win or draw
    if (checkWin(board, currentPlayer)) {
      displayBoard(board);
      cout << "Player " << currentPlayer << " wins!" << endl;
      break;
    }

    bool isDraw = true;
    for (char cell : board) {
      if (cell == EMPTY) {
        isDraw = false;
        break;
      }
    }
    if (isDraw) {
      displayBoard(board);
      cout << "It's a draw!" << endl;
      break;
    }

    // Switch players
    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
  }
}


int main() {
  // Prompt user to choose game mode
  char choice;
  do {
    cout << "Choose game mode:" << endl;
    cout << "1. One player vs computer (X)" << endl;
    cout << "2. Two players" << endl;
    cin >> choice;
  } while (choice != '1' && choice != '2');

  if (choice == '1') {
    playOnePlayer(PLAYER_X);
  } else {
    playTwoPlayer();
  }

  return 0;
}

