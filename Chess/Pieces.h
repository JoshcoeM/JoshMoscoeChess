#pragma once
#include <cmath>
#include <iostream>

// white = true

class Pieces {

	int yPos;
	int xPos;
	char rep;
	int score;
	bool colour;
	bool empty;

public:

	Pieces() {
		yPos = -1;
		xPos = -1;
		score = 0;
		rep = 'x';
		colour = true;
		empty = true;
	}
	void notEmpty() { empty = false; }
	bool isEmpty() { return empty; }

	void setCord(int x, int y) {
		xPos = x;
		yPos = y;
	}
	void setScore(int s) { score = s; }
	void setColour(bool c) { colour = c; }
	void setRep(char r) { rep = r; }
	bool getColour() { return colour; }
	int getX() { return xPos; }
	int getY() { return yPos; }
	int getScore() { return score; }
	char getRep() { return rep; }

	void isCaptured() {
		yPos = -1;
		xPos = -1;
		rep = 'x';
		empty = true;
	}

	~Pieces() {}

};


class Pawn : public Pieces {

	bool spawn;
public:
	Pawn() {
		Pieces();
		setScore(1);
		spawn = true; 
		notEmpty();
	}



	bool move(int x, int y) {
		if (this->isEmpty())
			return false;
		if(this->getColour())
			if (x == this->getX() && y == this->getY() - 1 )
				return true;
			else if (x == this->getX()  && y== this->getY() - 2  && spawn) 
				return true;
			else
				return false;
		else
			if (x == this->getX() && y == this->getY() +1)
				return true;
			else if (x == this->getX() && y ==  this->getY() + 2 && spawn)
				return true;
			else
				return false;
	}

	bool clear(int x, int y, int a, int b) {
		if (x == a && y == b)
			return false;
		else
			return true;
	}

	bool cap(int x, int y) {
		if (this->isEmpty())
			return false;
		if (this->getColour())
			if ((x + 1 == this->getX() && y == this->getY() - 1) || (x - 1 == this->getX() && y == this->getY() - 1))
				return true;
			else
				return false;
		else
			if ((x + 1 == this->getX() && y == this->getY() + 1) || (x - 1 == this->getX() && y == this->getY() + 1))
				return true;
			else
				return false;
	}

	void moved() { spawn = false; }




};

class Bishop : public Pieces {
public:
	Bishop() {
		Pieces();
		setScore(3);
		notEmpty();
	}

	bool move(int x, int y) {
		if (this->isEmpty())
			return false;
		if (abs(this->getX() - x) == abs(this->getY() - y)) 
			return true;
		else
			return false;
	}

	bool clear(int x, int y, int a, int b) {
		if (x == a && y == b)
			return false;
		else
			return true;
	}
};

class Knight : public Pieces {
public:
	Knight() {
		Pieces();
		setScore(3);
		notEmpty();
	}
	bool move(int x, int y) {
		if (this->isEmpty())
			return false;
		if (abs(this->getX() - x) == 2 && abs(this->getY() - y) == 1)
			return true;
		else if (abs(this->getX() - x) == 1 && abs(this->getY() - y) == 2)
			return true;
		else
			return false;
	}
};

class Rook : public Pieces {
	bool spawn;
public:
	Rook() {
		Pieces();
		setScore(5);
		notEmpty();
		spawn = true;
	}
	void moved() { spawn = false; }
	bool hasMoved() { return spawn; }


	bool move(int x, int y) {
		if (this->isEmpty())
			return false;
		if (x == this->getX() && y != this->getY())
			return true;
		else if (y == this->getY() && x != this->getX())
			return true;
		else
			return false;
	}
};

class Queen : public Pieces {
public:
	Queen() {
		Pieces();
		setScore(9);
		notEmpty();
	}
	bool move(int x, int y) {
		if (this->isEmpty())
			return false;
		if (x == this->getX() && y == this->getY())
			return true;
		else if (x == this->getX() || y == this->getY())
			return true;
		else if (abs(this->getX() - x) == abs(this->getY() - y))
			return true;
		else
			return false;
	}
};

class King : public Pieces {
	bool spawn;
public:


	King() { 
		Pieces();
		notEmpty();
		spawn = true;
	}

	void moved() { spawn = false; }

	bool move(int x, int y) {
		if (x == this->getX() && y == this->getY())
			return false;
		else if ((x == this->getX() || x + 1 == this->getX() || x - 1 == this->getX()) && (y == this->getY() || y + 1 == this->getY() || y - 1 == this->getY()))
			return true;
		else 
			return false;
		
	}

	bool castle(Rook* r, bool c, int x, int y) {
		for (int i = 0; i < 2; i++) {
			if (spawn && r[i].hasMoved())
				if (c) {
					if (i == 0 && x == 2 && y == 7)
						return true;
					else if (i == 1 && x == 6 && y == 7)
						return true;
				}
				else {
					if (i == 0 && x == 2 && y == 0)
						return true;
					else if (i == 1 && x == 6 && y == 0)
						return true;
				}
		}
		return false;
	}
	
};