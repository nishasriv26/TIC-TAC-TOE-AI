#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

char player = 'X', ai = 'O';

// Function to print the board
void printBoard(vector<char>& board) {
    for (int i = 0; i < 9; i += 3) {
        cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |" << endl;
    }
}

// Function to check for a winner
bool isWinner(vector<char>& board, char c) {
    vector<vector<int>> winConditions = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
                                         {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
                                         {0, 4, 8}, {2, 4, 6}};
    for (auto& condition : winConditions) {
        if (board[condition[0]] == c && board[condition[1]] == c && board[condition[2]] == c) {
            return true;
        }
    }
    return false;
}

// Function to check if the board is full
bool isBoardFull(vector<char>& board) {
    for (char c : board) {
        if (c == ' ') {
            return false;
        }
    }
    return true;
}

// Function to get available moves
vector<int> getAvailableMoves(vector<char>& board) {
    vector<int> moves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            moves.push_back(i);
        }
    }
    return moves;
}

// Minimax algorithm
int minimax(vector<char>& board, int depth, bool isMaximizing) {
    if (isWinner(board, ai)) {
        return 1;
    }
    if (isWinner(board, player)) {
        return -1;
    }
    if (isBoardFull(board)) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int move : getAvailableMoves(board)) {
            board[move] = ai;
            int score = minimax(board, depth + 1, false);
            board[move] = ' ';
            bestScore = max(score, bestScore);
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int move : getAvailableMoves(board)) {
            board[move] = player;
            int score = minimax(board, depth + 1, true);
            board[move] = ' ';
            bestScore = min(score, bestScore);
        }
        return bestScore;
    }
}

// Function to get the best move for the AI
int getBestMove(vector<char>& board) {
    int bestScore = INT_MIN;
    int bestMove = -1;
    for (int move : getAvailableMoves(board)) {
        board[move] = ai;
        int score = minimax(board, 0, false);
        board[move] = ' ';
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

// Function to make a move
void makeMove(vector<char>& board, int move, char c) {
    board[move] = c;
}

// Main function to play the game
void playGame() {
    vector<char> board(9, ' ');
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    printBoard(board);

    while (true) {
        // Human turn
        int humanMove;
        cout << "Enter your move (1-9): ";
        cin >> humanMove;
        humanMove -= 1;
        if (board[humanMove] != ' ') {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        makeMove(board, humanMove, player);
        printBoard(board);
        if (isWinner(board, player)) {
            cout << "Congratulations! You won!" << endl;
            break;
        }
        if (isBoardFull(board)) {
            cout << "It's a tie!" << endl;
            break;
        }

        // AI turn
        cout << "AI is making a move..." << endl;
        int aiMove = getBestMove(board);
        makeMove(board, aiMove, ai);
        printBoard(board);
        if (isWinner(board, ai)) {
            cout << "AI wins!" << endl;
            break;
        }
        if (isBoardFull(board)) {
            cout << "It's a tie!" << endl;
            break;
        }
    }
}

int main() {
    playGame();
    return 0;
}
