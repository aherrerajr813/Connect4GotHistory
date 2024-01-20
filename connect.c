#include <stdio.h>
#include <stdlib.h>
#include "slist.h"
//include the below library package for sleep function
#include<windows.h>

//define Boolean type since C does not have it already
typedef enum { F = 0, T = 1 } Bool;
//define number of rows and columns
#define NUM_ROWS 6
#define NUM_COLS 7

// Declare functions up top
void PlayConnectFour(slist* list);
void PrintBoard(char board[][NUM_COLS]);
int GetEmptyRow(char board[][NUM_COLS], int col, char player);
Bool CheckBoardFull(char board[][NUM_COLS]);
char CheckWinner(char board[][NUM_COLS], int connect, char player);
int GetColumn(char player);

//new function declaration: replayConnectFour
void replayConnectFour(slist* list);

/*promts the user who started running the program if they want to play connect4 or quit the game.
has a loop so after playing the game, the users may continue playing*/
int main()
{
	printf("Welcome! Press 'q' to quit or any key to continue:\n");

	char c;
	Bool done = F;
	slist moves = { NULL, NULL };

	while (!done) {
		scanf_s("%c", &c, 1);

		//checks to see if user wants to quit
		if (c == 'q') {
			done = T;
			printf("Bye Bye\n");
		}else if (c == 'r') {
			replayConnectFour(&moves);
			clearList(&moves);
			printf("Press 'q' to quit or any other key to play again:\n");
			c = 'r';
			scanf_s("%c", &c, 1);
		} else{
			PlayConnectFour(&moves);
			printf("Press 'q' to quit or 'r' to replay or any other key to continue:\n");
		}
	}
	return 0;
}

/*this function creates a new game for the player to begin, asks for their names, and calls on several functions so that
* the players token can fall into the column they select, as well as checks if the game has a winner or if the game
* ends in a draw due to the board being full*/
void PlayConnectFour(slist* list) {
	//creates empty 2D array of chars
	char board[NUM_ROWS][NUM_COLS];
	char player1[30];
	char player2[30];
	Bool game_over = F;
	int connect_number;

	//prompts the current players for their names and assigns the color will play as
	printf("Please input the name of player 1 (team Red): ");
	scanf_s("%s", player1, 30);
	printf("Please input the name of player 2 (team Yellow): ");
	scanf_s("%s", player2, 30);
	//prompts the user to ask which variant of the game they want to play
	printf("Between 3-5, how many tokens would you like connecting to win the game? ");
	int num_values = scanf_s("%d", &connect_number);
	//clears the buffer
	while (getchar() != '\n');
	//checks to see whether or not the user put a value between 3-5
	while (connect_number != 3 && connect_number != 4 && connect_number != 5) {
		printf("Make sure the size you pick is between 3 and 5: \n");
		num_values = scanf_s("%d", &connect_number);
		while (getchar() != '\n');
	}

	/* initialize the array to have spaces (which represents the empty state): " "*/
	for (int r = 0; r < NUM_ROWS; r++)
	{
		for (int c = 0; c < NUM_COLS; c++) {
			board[r][c] = ' ';
		}
	}


	PrintBoard(board);
	//sets the first turn to be team Red
	char player = 'R';
	Bool fullBoard = F;
	char winner = ' ';

	while (!game_over) {
		int col = GetColumn(player);
			
		int row = GetEmptyRow(board, col, player);
		//checks condition if column is full before putting token in designated spot.
		//after getting col and row from respective columns, that array element is accessed
		if (row != 8) {
			board[row][col] = player;

			//only want to insert column number to linkedList if the column is not full
			insertTail(list, col);
		}
		//prints the board to show the player what it looks like after their turn
		PrintBoard(board);

		//checks if the current player has won after their turn. if they do, the game ends and they're prompted to play again
		winner = CheckWinner(board, connect_number, player);
		if (winner == 'R') {
			printf("Congratulations %s, you won connect %d!\n", player1, connect_number);
			game_over = T;
		}
		else if (winner == 'Y') {
			printf("Congratulations %s, you won connect %d!\n", player2, connect_number);
			game_over = T;
		}

		//after checking who has won, will then check if the board is full. if it's full, the game ends
		fullBoard = CheckBoardFull(board);

		if (fullBoard == T) {
			printf("The board is full and the game ends in a draw.\n");
			game_over = T;
		}

		//toggles to the next players turn before the while loop runs again
		player = (player == 'R' ? 'Y' : 'R');


	}
}

//need to access elements in the linkedList, starting with Head element then moving 
//sequentially to nextNodes
void replayConnectFour(slist* list) {
	
	//create another 2D array and initialize to being empty
	char board[NUM_ROWS][NUM_COLS];
	//the game always begins with Red team
	char player = 'R';
	int col;

	for (int r = 0; r < NUM_ROWS; r++)
	{
		for (int c = 0; c < NUM_COLS; c++) {
			board[r][c] = ' ';
		}
	}
	PrintBoard(board);
	//sleep for a little after printing the empty board
	Sleep(1350);

	//create a node that will traverse the linkedList
	struct node* tmp = list->head;
	while (tmp != NULL)
	{
		//gets the column number stored in the linkedList
		col = tmp->data;
		//with the column, will look for available row
		int row = GetEmptyRow(board, col, player);
		//insert at proper place in board
		board[row][col] = player;
		//print the board to show the move
		PrintBoard(board);

		//use the sleep function so that the game may be rewatched at a reasonable rate
		Sleep(1350);

		//moves to the next element in the array
		tmp = tmp->next;
		
		//toggles to the next players turn before the while loop runs again
		player = (player == 'R' ? 'Y' : 'R');

	}


}

//prints the current state of the board so the players may see the progression of the game
void PrintBoard(char board[][NUM_COLS]) {
	for (int r = 0; r < NUM_ROWS; r++)
	{
		printf("|");
		for (int c = 0; c < NUM_COLS; c++) {
			/*due to the nature of how printing works, want to print the most top-left array element.
			So this impacted the way in which the array is printed, as it starts with the top row*/
			printf("%c|", board[(NUM_ROWS - r - 1)][c]);
		}
		printf("\n");//moves down next row to print
	}
	printf("---------------\n");
}

//after the player picks a column, this function checks for the lowest row that is empty and returns that value
int GetEmptyRow(char board[][NUM_COLS], int col, char player) {
	int row = 0;
	//given the column being passed, checks that column and the lowest row first to see if there is a space, which indicates its empty
	while (board[row][col] != ' ') {
		row++;
		//if the row is full, it prompts the user to input a new column, and utilizes recursion so that the current player may properly get their turn
		//will pass an 8 back to the function call, which fails the condition that the array is updated
		if (row == NUM_COLS) {
			printf("Please select a column that is not full\n");
			int col2 = GetColumn(player);
			int row2 = GetEmptyRow(board, col2, player);
			board[row2][col2] = player;
			return row = 8;
		}
	}
	return row;
}

//this function checks to see if the board is full. If it encounters a space anywhere in the array, then the board is not full
//if it does not encounter a space, then the board is full
Bool CheckBoardFull(char board[][NUM_COLS]) {
	Bool full = F;
	for (int r = 0; r < NUM_ROWS; r++)
	{
		for (int c = 0; c < NUM_COLS; c++) {
			if (board[r][c] == ' ') {
				return full;
			}
		}
	}
	full = T;
	return full;
}


/*this function checks four win conditions: horizontal, vertical, diagonal upwards and diagonal downwards
it utilizes the same structure for each for loop, just changing how the next array element is indexed*/
char CheckWinner(char board[][NUM_COLS], int connect, char player) {
	int countH = 0;
	int countV = 0;
	int countDU = 0;
	int countDD = 0;

	//will check horizontal win condition first
	//everytime the for loop is iterated through, the respective count is set back to 0
	for (int r = 0; r < NUM_ROWS; r++)
	{
		countH = 0;
		for (int c = 0; c < (NUM_COLS - connect + 1); c++) {
			countH = 0;
			if (board[r][c] == player) {
				countH++;
				for (int k = 1; k < connect; k++) {
					if (board[r][c + k] == player) {
						countH++;
						if (countH == connect) {
							return player;
						}
					}
				}

			}
		}
	}

	//will check vertical win condition next
	//everytime the for loop is iterated through, the respective count is set back to 0
	for (int c = 0; c < NUM_COLS; c++)
	{
		countV = 0;
		for (int r = 0; r < (NUM_ROWS - connect + 1); r++) {
			countV = 0;
			if (board[r][c] == player) {
				countV++;
				for (int k = 1; k < connect; k++) {
					if (board[r + k][c] == player) {
						countV++;
						if (countV == connect) {
							return player;
						}
					}
				}

			}
		}
	}

	//will check diagonal up win condition next
	//everytime the for loop is iterated through, the respective count is set back to 0
	for (int c = 0; c < (NUM_COLS - connect + 1); c++)
	{
		countDU = 0;
		for (int r = 0; r < (NUM_ROWS - connect + 1); r++) {
			countDU = 0;
			if (board[r][c] == player) {
				countDU++;
				for (int k = 1; k < connect; k++) {
					if (board[r + k][c + k] == player) {
						countDU++;
						if (countDU == connect) {
							return player;
						}
					}
				}

			}
		}
	}

	//will check diagonal up win condition next
	//everytime the for loop is iterated through, the respective count is set back to 0
	for (int c = 0; c < (NUM_COLS - connect + 1); c++)
	{
		countDD = 0;
		for (int r = NUM_ROWS - 1; r >= connect - 1; r--) {
			countDD = 0;
			if (board[r][c] == player) {
				countDD++;
				for (int k = 1; k < connect; k++) {
					if (board[r - k][c + k] == player) {
						countDD++;
						if (countDD == connect) {
							return player;
						}
					}
				}

			}
		}
	}

	return ' ';


}

//prompts the current player to select a column they want to designate their token falls into
int GetColumn(char player) {
	int column;
	char current_player = player;

	printf("%s to play. Pick a column (1-7):", player == 'R' ? "Red" : "Yellow");

	int num_values = scanf_s("%d", &column);
	while (getchar() != '\n');

	//if the player picks a non-designated value or character, they are prompted to re-enter a value
	while (num_values != 1 || column<1 || column> NUM_COLS) {
		printf("Make sure the column is between 1 and 7: \n");
		num_values = scanf_s("%d", &column);
		while (getchar() != '\n');
	}
	//since arrays are indexed starting at 0, need to subtract 1
	return column - 1;
}