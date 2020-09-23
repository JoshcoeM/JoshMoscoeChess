#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include "Player.h"



using namespace std;

int letterToNum(char x) {
	switch (x) {
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		case 'd':
			return 3;
		case 'e':
			return 4;
		case 'f':
			return 5;
		case 'g':
			return 6;
		case 'h':
			return 7;
		default:
			return -1;
	}
}


int main() {
	Player white(true);
	Player black(false);

	bool turn = false;
	bool badMove = true;

	char moving;
	char cordX;
	int cordY;

	Board *board = new Board();


	white.populate(board);
	black.populate(board);

	

	do {

		board->printBoard();

		turn = turn ? false : true;

		do {
			badMove = true;
			if (turn)
				cout << "White's turn, ";
			else
				cout << "Black's turn, ";

			cout << "enter piece to move and its new location" << endl;
			cin >> moving;
			cin >> cordX;
			cin >> cordY;
		
			if (turn) {
				if (white.play(board, &black, toupper(moving), letterToNum(tolower(cordX)), 8-cordY))
					badMove = false;
			}else{
				if (black.play(board, &white, toupper(moving), letterToNum(tolower(cordX)), 8 - cordY))
					badMove = false;
			}
			if (badMove)
				cout << "Please enter a legal play." << endl;
		} while (badMove);



		
	} while (!white.mate(black.getKing(), board, &black) && !black.mate(white.getKing(), board, &white));

	if (turn)
		cout << "Black in check mate, white wins! " << endl;
	else
		cout << "White in check mate, black wins! " << endl;

	cout << "Final scores " << endl << "White: " << white.getScore() << endl << "Black: " << black.getScore() << endl;



}



