#include <iostream>
using namespace std;

char board[3][3];

void resetBoard()
{
    char number = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = number;
            number++;
        }
    }
}

void displayBoard()
{
    cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if (j < 2)
            {
                cout << " | ";
            }
        }

        cout << "\n";

        if (i < 2)
        {
            cout << "---+---+---\n";
        }
    }

    cout << "\n";
}

bool checkWin()
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
        {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
        {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        return true;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        return true;
    }

    return false;
}

bool checkDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' &&
                board[i][j] != 'O')
            {
                return false;
            }
        }
    }

    return true;
}

bool makeMove(int choice, char player)
{
    if (choice < 1 || choice > 9)
    {
        return false;
    }

    int row = (choice - 1) / 3;
    int column = (choice - 1) % 3;

    if (board[row][column] == 'X' ||
        board[row][column] == 'O')
    {
        return false;
    }

    board[row][column] = player;

    return true;
}

int main()
{
    char playAgain;

    do
    {
        resetBoard();

        char currentPlayer = 'X';
        int choice;
        bool gameOver = false;

        cout << "=============================\n";
        cout << "       TIC TAC TOE GAME       \n";
        cout << "=============================\n";

        while (!gameOver)
        {
            displayBoard();

            cout << "Player " << currentPlayer
                 << ", enter your choice (1-9): ";

            cin >> choice;

            if (!makeMove(choice, currentPlayer))
            {
                cout << "\nInvalid Move! Try Again.\n";
                continue;
            }

            if (checkWin())
            {
                displayBoard();

                cout << "Player " << currentPlayer
                     << " Wins!\n";

                gameOver = true;
            }
            else if (checkDraw())
            {
                displayBoard();

                cout << "Game Draw!\n";

                gameOver = true;
            }
            else
            {
                if (currentPlayer == 'X')
                {
                    currentPlayer = 'O';
                }
                else
                {
                    currentPlayer = 'X';
                }
            }
        }

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "\nThank You For Playing Tic Tac Toe!\n";

    return 0;
}