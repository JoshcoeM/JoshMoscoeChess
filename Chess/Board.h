#pragma once

#include "Pieces.h"
#include <iostream>
#include <vector>


using namespace std;

class Board {

	vector<vector<Pieces>> square;
public:

	Board() {
		for (int i = 0; i < 8; i++) {
			vector <Pieces> x;
			for (int j = 0; j < 8; j++) {
				Pieces y;
				x.push_back(y);
			}
			square.push_back(x);
		}
	}
	Pieces returnPiece(int x, int y) { return square[x][y]; }

	bool emptySquare(int x, int y) { return square[x][y].isEmpty(); }

	void placePiece(Pieces p, int x, int y) {
		square[x].erase(square[x].begin() +y);
		square[x].insert(square[x].begin() +y, p);
	}

	void printBoard() {

		cout << "   a  b  c  d  e  f  g  h" << endl;\
		for (int i = 1; i <= 8; i++) {
			cout << 9-i << "  ";
			for (int j = 1; j <= 8; j++)
				std::cout << square[j-1][i-1].getRep() << "  ";
			std::cout << std::endl;
		}
	}

	int pieceScore(int x, int y) {
		return square[x][y].getScore();
	}


	void removePiece(int x, int y) {
		Pieces empty;
		square.at(x).erase(square.at(x).begin() + y);
		square.at(x).insert(square[x].begin() + y, empty);

	}

	bool oppPieces(Pieces p, int a, int b) {
		if (p.getColour() != square[a][b].getColour() && !square[a][b].isEmpty())
			return true;
		else 
			return false;
	}

	//checks if there are pieces in the way; overload for each piece type

	bool clearPath(Pieces p, int x, int y, int a, int b) {
		std::cout << "Something went awry" << std::endl;
		return false;
	}

	bool clearPath(Pawn p, int x, int y, int a, int b) {
		if (square[a][b].isEmpty())
			return true;
		else if (square[a][b].getColour() != p.getColour())
			return true;
		else if(abs(y-b)==2 ){
			if (p.getColour() && square[a][b-1].isEmpty()) 
				return true;
			else if (!p.getColour() && square[a][b+1].isEmpty())
				return true;
		}else 
			return false;
	}

	bool clearPath(Bishop p, int x, int y, int a, int b) {
		if (x < a && y < b) {
			for (int i = 1; i <= abs(x - a); i++) {
				if (!square[x + i][y + i].isEmpty())
					if (abs(x - a) == i && (square[a][b].getColour() != p.getColour()))
						return true;
					else
						return false;
			}
		}else if (x < a && y > b) {
			for (int i = 1; i <= abs(x - a); i++) {
				if (!square[x + i][y - i].isEmpty())
					if (abs(x - a) == i && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}else if (x>a && y<b) {
			for (int i = 1; i <= abs(x - a); i++) {
				if (!square[x - i][y + i].isEmpty())
					if (abs(x - a) == i && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}else {
			for (int i = 1; i <= abs(x - a); i++) {
				if (!square[x - i][y - i].isEmpty())
					if (abs(x-a) == i && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		return true;
			
	}
	bool clearPath(Knight p, int x, int y, int a, int b) {
		if (square[a][b].isEmpty())
			return true;
		else if (square[a][b].getColour() != p.getColour())
			return true;
		else
			return false;
	}

	bool clearPath(Rook p, int x, int y, int a, int b) {
		if (x < a ) {
			for (int i = 1; i < abs(x - a); i++) {
				if (!square[x + i][y].isEmpty())
					if (x + i == a && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else if (x >a ) {
			for (int i = 1; i < abs(x - a); i++) {
				if (!square[x - i][y].isEmpty())
					if (x + i == a && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else if (y < b) {
			for (int i = 1; i < abs(y - b); i++) {
				if (!square[x][y + i].isEmpty())
					if (y + i == b && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else {
			for (int i = 1; i < abs(y-b); i++) {
				if (!square[x][y - i].isEmpty())
					if (y + i == b && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		return true;
	}
	bool clearPath(Queen p, int x, int y, int a, int b) {
		if (x < a && y < b) {
			for (int i = 1; i < abs(x - a); i++) {
				if (!square[x + i][y + i].isEmpty())
					if (x + i == a && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else if (x < a && y > b) {
			for (int i = 1; i < abs(x - a); i++) {
				if (!square[x + i][y - i].isEmpty())
					if (x + i == a && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else if (x > a&& y < b) {
			for (int i = 1; i < abs(x - a); i++) {
				if (!square[x - i][y + i].isEmpty())
					if (x + i == a && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else if(x > a && y > b) {
			for (int i = 1; i < abs(x - a); i++) {
				if (!square[x - i][y - i].isEmpty())
					if (x + i == a && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}else if (x < a) {
			for (int i = 1; i < abs(x - a); i++) {
				if (!square[x + i][y].isEmpty())
					if (x + i == a && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else if (x > a) {
			for (int i = 1; i < abs(x - a); i++) {
				if (!square[x - i][y].isEmpty())
					if (x + i == a && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else if (y < b) {
			for (int i = 1; i < abs(y - b); i++) {
				if (!square[x][y + i].isEmpty())
					if (y + i == b && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		else {
			for (int i = 1; i < abs(y - b); i++) {
				if (!square[x][y - i].isEmpty())
					if (y + i == b && square[a][b].getColour() != p.getColour())
						return true;
					else
						return false;
			}
		}
		return true;
	}
	bool clearPath(King p, int x, int y, int a, int b) {
		if (x < a && y < b) {
				if (square[x +1][y +1].isEmpty())
					return true;
				else if (square[a][b].getColour() == p.getColour())
					return false;
		}else if (x < a && y > b) {
				if (square[x +1][y -1].isEmpty())
					return true;
				else if (square[a][b].getColour() == p.getColour())
					return false;
		}else if (x > a&& y < b) {
				if (square[x -1][y +1].isEmpty())
					return true;
				else if (square[a][b].getColour() == p.getColour())
					return false;
		}else if (x > a&& y > b) {
				if (square[x -1][y -1].isEmpty())
					return true;
				else if (square[a][b].getColour() == p.getColour())
					return false;
		}else if (x < a) {
				if (square[x +1][y].isEmpty())
					return true;
				else if (square[a][b].getColour() == p.getColour())
					return false;
		}
		else if (x > a) {
				if (square[x -1][y].isEmpty())
					return true;
				else if (square[a][b].getColour() == p.getColour())
					return false;
		}
		else if (y < b) {
			if (square[x][y +1].isEmpty())
				return true;
			else if (square[a][b].getColour() == p.getColour())
				return false;
		}
		else {
			if (square[x][y -1].isEmpty())
				return true;
			else if (square[a][b].getColour() == p.getColour())
				return false;
		}
		return true;
	}

	bool clearCastle( int x, int y) {
		if (x == 2)
			if (square[1][y].isEmpty() && square[2][y].isEmpty() && square[3][y].isEmpty())
				return true;
			else
				return false;
		else if (x == 6)
			if (square[5][y].isEmpty() && square[6][y].isEmpty())
				return true;
			else
				return false;
		else
			return false;
	}


};