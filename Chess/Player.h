#pragma once
//white = true

#include "Pieces.h"
#include "Board.h"

class Player {

	int score;
	bool colour;

	Pawn pawn[8];
	Bishop bishop[2];
	Knight knight[2];
	Rook rook[2];
	Queen queen;
	King king;

public:

	int getScore() { return score; }
	bool getColour() { return colour; }
	void addToScore(int x) { 
		score += x;
		if (colour)
			cout << "White has ";
		else
			cout << "Black has ";
		cout << score << " points!" << endl;
	}
	King getKing() { return king; }
	

	Player(){
		score = 0;
		colour = true;
		}
	Player(bool c) {
		score = 0;
		colour = c;
		for (int i = 0; i < 8; i++) {
			pawn[i].setColour(c);
			pawn[i].setRep(c ? 'P' : 'p');
			pawn[i].setCord(i, colour ? 6 : 1);
		}
		for (int i = 0; i < 2; i++) {
			bishop[i].setColour(c);
			knight[i].setColour(c);
			rook[i].setColour(c);

			bishop[i].setRep(c ? 'B' : 'b');
			knight[i].setRep(c ? 'N' : 'n');
			rook[i].setRep(c ? 'R' : 'r');

			bishop[i].setCord(i == 0 ? 5 : 2, c ? 7 : 0);
			knight[i].setCord(i == 0 ? 6 : 1, c ? 7 : 0);
			rook[i].setCord(i == 0 ? 7 : 0, c ? 7 : 0);
		}
		queen.setColour(c);
		queen.setRep(c ? 'Q' : 'q');
		queen.setCord(3, c ? 7 : 0);
		king.setColour(c);
		king.setRep(c ? 'K' : 'k');
		king.setCord(4, c ? 7 : 0);

	}


	void populate(Board* board) {
		for (int i = 0; i < 8; i++) {
			board->placePiece(pawn[i], pawn[i].getX(), pawn[i].getY());
		}
		for (int i = 0; i < 2; i++) {
			board->placePiece(bishop[i], bishop[i].getX(), bishop[i].getY());
			board->placePiece(knight[i], knight[i].getX(), knight[i].getY());
			board->placePiece(rook[i], rook[i].getX(), rook[i].getY());
		}

		board->placePiece(queen, queen.getX(), queen.getY());
		board->placePiece(king, king.getX(), king.getY());

	}

	bool play(Board *b,Player *opp, char p, int x, int y){
		switch (p) {
		case 'P':
			for (int i = 0; i < 8; i++)
				if (this->legalMove(b, opp, pawn[i], x, y)) {
					pawn[i].setCord(x, y);
					pawn[i].moved();
					return true;
				}
				return false;
			break;
		case 'B':
			for (int i = 0; i < 2; i++)
				if (this->legalMove(b, opp, bishop[i], x, y)){
					bishop[i].setCord(x, y);
					return true;
				}
			return false;
			break;
		case 'N':
			if (knight[0].move(x, y) && knight[1].move(x, y)) {
				int n = -1;
				cout << "Which Knight should move? Enter 0 for the knight at " << knight[0].getX() << ", " << knight[0].getY() << " or enter 1 for the knight at " << knight[1].getX() << ", " << knight[1].getY() << endl;
				cin >> n;
				if (this->legalMove(b, opp, knight[n], x, y)) {
					knight[n].setCord(x, y);
					return true;
				}
			}
			for (int i = 0; i < 2; i++)
				if (this->legalMove(b, opp, knight[i], x, y)){
					knight[i].setCord(x, y);
					return true;
				}
			return false;
			break;
		case 'R':
			if (rook[0].move(x, y) && rook[1].move(x, y) && b->clearPath(rook[0], rook[0].getX(), rook[0].getY(), x, y) && b->clearPath(rook[1], rook[1].getX(), rook[1].getY(), x, y)){
				int n = -1;
				cout << "Which Rook should move? Enter 0 for the rook at " << rook[0].getX() << ", " << rook[0].getY() << " or enter 1 for the rook at " << rook[1].getX() << ", " << rook[1].getY() << endl;
				cin >> n;
				if (this->legalMove(b, opp, rook[n], x, y)) {
					rook[n].setCord(x, y);
					return true;
				}
			}
			for (int i = 0; i < 2; i++)
				if (this->legalMove(b, opp, rook[i], x, y)){
					rook[i].setCord(x, y);
					return true;
				}
			return false;
			break;
		case 'Q':
			if (this->legalMove(b, opp, queen, x, y)){
				queen.setCord(x, y);
				return true;
			}
			else
				return false;
			break;
		case 'K':
			if (this->legalMove(b, opp, king, x, y)){
				king.setCord(x, y);
				return true;
			}else
				return false;
			break;
		default:
			return false;
		}
	}




	bool emptySpot(int x, int y) {
		for (int i = 0; i < 8; i++) {
			if (pawn[i].getX() == x && pawn[i].getY() == y)
				return false;
		}
		for (int i = 0; i < 2; i++) {
			if (bishop[i].getX() == x && bishop[i].getY() == y)
				return false;
			else if (knight[i].getX() == x && knight[i].getY() == y)
				return false;
			else if (rook[i].getX() == x && rook[i].getY() == y)
				return false;
		}

		if (queen.getX() == x && queen.getY() == y)
			return false;
		else if (king.getX() == x && king.getY() == y)
			return false;
		else 
			return true;
	}

	Pieces check(Board* b, Player *opp, int x, int y) {
		for (int i = 0; i < 8; i++) {
			if (pawn[i].cap(x, y)) {
				return pawn[i];
			}
		}
		for (int i = 0; i < 2; i++) {
			if (bishop[i].move( x, y)) 
				if(b->clearPath(bishop[i], bishop[i].getX(), bishop[i].getY(), x, y)){
					return bishop[i];
			}else if(knight[i].move(x, y))
				if (b->clearPath(knight[i], knight[i].getX(), knight[i].getY(), x, y)) {
					return knight[i];
			}else if (rook[i].move(x, y))
				if (b->clearPath(rook[i], rook[i].getX(), rook[i].getY(), x, y)) {
					return rook[i];
				}
			}

		if (queen.move(x, y))
			if (b->clearPath(queen, queen.getX(), queen.getY(), x, y)) {
				return queen;
		}else if (king.move(x, y))
			if (b->clearPath(king, king.getX(), king.getY(), x, y)) {
				return king;
			}
			else {
				Pieces empty;
				return empty;
			}
			
	}

	bool stale(King k, Board* b, Player *opp) {

		for(int i=-1;i<2;i++)
			for(int j=-1;j<2;j++)
				if (!(i == 0 && j == 0))
					if(k.getX() +i >= 0 && k.getX()+ i <8 && k.getY() + j >=0 && k.getY()+j < 8)		// if in bounds
						if(b->clearPath(k,k.getX(),k.getY(), k.getX()+i,k.getY()+j))
							if (!check(b, opp, k.getX() + i, k.getY() + j).isEmpty() && !(i == 0 && j == 0))
								return false;
		return true;
	}

	bool mate(King k, Board* b, Player *opp) {
		Pieces checker = check(b, opp, k.getX(), k.getY());
		if (!checker.isEmpty())
			if (stale(k, b, opp)) {
				if(!canBlock(b,opp))
					return true;
				else {
					cout << "Check" << endl;
					return false;
				}
			}else {
				cout << "Check" << endl;
				return false;
			}
		else
			return false;

	}

	bool canBlock(Board* b, Player* opp) {
		for (int i = 0; i < 8; i++) {
			if (block(pawn[i], b, opp))
				return true;
		}
		for (int i = 0; i < 2; i++) {
			if (block(bishop[i], b, opp))
				return true;
			else if (block(knight[i], b, opp))
				return true;
			else if (block(rook[i], b, opp))
				return true;
		}
		if (block(queen, b, opp))
			return true;
		else
			return false;
	}
	

	bool block(Pawn p, Board* b, Player* opp) {
		if (capCheck(p, b, opp))
			return true;
		else
			return false;
	}

	bool block(Bishop p, Board* b, Player* opp) {
		if (capCheck(p, b, opp))
			return true;
		else if(opp->getKing().getX() < p.getX() && opp->getKing().getY() < p.getY()) {
			for (int i = 1; i <= abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX()+i,p.getY()+i).isEmpty())
					return true;

			}
			return false;
		}else if (opp->getKing().getX() < p.getX() && opp->getKing().getY() > p.getY()) {
			for (int i = 1; i <= abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() + i, p.getY() - i).isEmpty())
					return true;

			}
			return false;
		}else if (opp->getKing().getX() > p.getX() && opp->getKing().getY() < p.getY()) {
			for (int i = 1; i <= abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() - i, p.getY() + i).isEmpty())
					return true;

			}
			return false;
		}else {
			for (int i = 1; i <= abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() - i, p.getY() - i).isEmpty())
					return true;
			}
			return false;
		}
		
	}

	bool block(Knight p, Board* b, Player* opp) {
		if (capCheck(p, b, opp))
			return true;
		else
			return false;
	}

	bool block(Rook p, Board* b, Player* opp) {
		if (capCheck(p, b, opp))
			return true;
		else if (opp->getKing().getX() < p.getX()) {
			for (int i = 1; i < abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() + i, p.getY()).isEmpty())
						return true;
			}
			return false;
		}
		else if (opp->getKing().getX() > p.getX()) {
			for (int i = 1; i < abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() - i, p.getY()).isEmpty())
					return true;
			}
			return false;
		}
		else if (opp->getKing().getY() < p.getY()) {
			for (int i = 1; i < abs(opp->getKing().getY() - p.getY()); i++) {
				if (!opp->blockCheck(b, opp, p.getX(), p.getY() + i).isEmpty())
					return true;
			}
			return false;
		}
		else {
			for (int i = 1; i < abs(opp->getKing().getY() - p.getY()); i++) {
				if (!opp->blockCheck(b, opp, p.getX(), p.getY()- i).isEmpty())
					return true;
			}
			return false;
		}
	}

	bool block(Queen p, Board* b, Player* opp) {
		if (capCheck(p, b, opp))
			return true;
		else if (opp->getKing().getX() < p.getX() && opp->getKing().getY() < p.getY()) {
			for (int i = 1; i <= abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() + i, p.getY() + i).isEmpty())
					return true;

			}
			return false;
		}
		else if (opp->getKing().getX() < p.getX() && opp->getKing().getY() > p.getY()) {
			for (int i = 1; i <= abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() + i, p.getY() - i).isEmpty())
					return true;

			}
			return false;
		}
		else if (opp->getKing().getX() > p.getX() && opp->getKing().getY() < p.getY()) {
			for (int i = 1; i <= abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() - i, p.getY() + i).isEmpty())
					return true;

			}
			return false;
		}
		else if(opp->getKing().getX() > p.getX() && opp->getKing().getY() > p.getY()){
			for (int i = 1; i <= abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() - i, p.getY() - i).isEmpty())
					return true;
			}
			return false;
		}else if (opp->getKing().getX() < p.getX()) {
			for (int i = 1; i < abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() + i, p.getY()).isEmpty())
					return true;
			}
			return false;
		}
		else if (opp->getKing().getX() > p.getX()) {
			for (int i = 1; i < abs(opp->getKing().getX() - p.getX()); i++) {
				if (!opp->blockCheck(b, opp, p.getX() - i, p.getY()).isEmpty())
					return true;
			}
			return false;
		}
		else if (opp->getKing().getY() < p.getY()) {
			for (int i = 1; i < abs(opp->getKing().getY() - p.getY()); i++) {
				if (!opp->blockCheck(b, opp, p.getX(), p.getY() + i).isEmpty())
					return true;
			}
			return false;
		}
		else {
			for (int i = 1; i < abs(opp->getKing().getY() - p.getY()); i++) {
				if (!opp->blockCheck(b, opp, p.getX(), p.getY() - i).isEmpty())
					return true;
			}
			return false;
		}
		return true;
	}

	bool capCheck(Pawn p, Board* b, Player* opp) {
		Pieces canCap = opp->check(b, this, p.getX(), p.getY());
		if (canCap.isEmpty())
			return false;
		else if (toupper(canCap.getRep()) == 'K'){
			if (check(b, opp, p.getX(), p.getY()).isEmpty())
				return true;
			else
				return false;
		}else
			return true;
	}

	bool capCheck(Bishop p, Board* b, Player* opp){
		Pieces canCap = opp->check(b, this, p.getX(), p.getY());
		if (canCap.isEmpty())
			return false;
		else if (toupper(canCap.getRep()) == 'K') {
			if (check(b, opp, p.getX(), p.getY()).isEmpty())
				return true;
			else
				return false;
		}
		else
			return true;
	}

	bool capCheck(Knight p, Board* b, Player* opp) {
		Pieces canCap = opp->check(b, this, p.getX(), p.getY());
		if (canCap.isEmpty())
			return false;
		else if (toupper(canCap.getRep()) == 'K') {
			if (check(b, opp, p.getX(), p.getY()).isEmpty())
				return true;
			else
				return false;
		}
		else
			return true;
	}

	bool capCheck(Rook p, Board* b, Player* opp){
		Pieces canCap = opp->check(b, this, p.getX(), p.getY());
		if (canCap.isEmpty())
			return false;
		else if (toupper(canCap.getRep()) == 'K') {
			if (check(b, opp, p.getX(), p.getY()).isEmpty())
				return true;
			else
				return false;
		}
		else
			return true;
	}

	bool capCheck(Queen p, Board* b, Player* opp) {
		Pieces canCap = opp->check(b, this, p.getX(), p.getY());
		if (canCap.isEmpty())
			return false;
		else if (toupper(canCap.getRep()) == 'K') {
			if (check(b, opp, p.getX(), p.getY()).isEmpty())
				return true;
			else
				return false;
		}
		else
			return true;
	}

	Pieces blockCheck(Board* b, Player* opp, int x, int y) {
		for (int i = 0; i < 8; i++)
			if (pawn[i].cap(x, y))
				return pawn[i];
		for (int i = 0; i < 2; i++) {
			if (bishop[i].move(x, y))
				if (b->clearPath(bishop[i], bishop[i].getX(), bishop[i].getY(), x, y)) {
					return bishop[i];
				}
				else if (knight[i].move(x, y))
					if (b->clearPath(knight[i], knight[i].getX(), knight[i].getY(), x, y)) {
						return knight[i];
					}
					else if (rook[i].move(x, y))
						if (b->clearPath(rook[i], rook[i].getX(), rook[i].getY(), x, y)) {
							return rook[i];
						}
		}

		if (queen.move(x, y))
			if (b->clearPath(queen, queen.getX(), queen.getY(), x, y)) {
				return queen;
			}
			else if (king.move(x, y))
				if (b->clearPath(king, king.getX(), king.getY(), x, y)) {
					return king;
				}
				else {
					Pieces empty;
					return empty;
				}
	}



 	bool legalMove(Board* b, Player *opp, Pawn p, int x, int y) {
		if (!p.move(x, y) && !p.cap(x,y)) {
			return false;
		}else if (p.cap(x,y) && b->oppPieces(p, x, y) && !b->emptySquare(x,y)){
			this->addToScore(b->pieceScore(x, y));
			opp->hidePiece(b->returnPiece(x,y).getRep(), x, y);
			b->removePiece(x, y);
			b->placePiece(p, x, y);
			b->removePiece(p.getX(), p.getY());
		}else if (b->clearPath(p, p.getX(), p.getY(), x, y) && !p.cap(x,y)) {
			b->placePiece(p, x, y);
			b->removePiece(p.getX(), p.getY());
		}
		else
			return false;

		return true;

	}

	bool legalMove(Board* b, Player* opp, Bishop p, int x, int y) {
		if (!p.move(x, y)) {
			return false;
		}
		else if (b->clearPath(p, p.getX(), p.getY(), x, y)) {
			if (b->oppPieces(p, x, y)) {
				this->addToScore(b->pieceScore(x, y));
				opp->hidePiece(b->returnPiece(x, y).getRep(), x, y);
				b->removePiece(x, y);
			}
			b->placePiece(p, x, y);
			b->removePiece(p.getX(), p.getY());
		}
		else
			return false;

		return true;

	}

	bool legalMove(Board* b, Player* opp, Knight p, int x, int y) {
		if (!p.move(x, y)) {
			return false;
		}
		else if (b->clearPath(p, p.getX(), p.getY(), x, y)) {
			if (b->oppPieces(p, x, y)) {
				this->addToScore(b->pieceScore(x, y));
				opp->hidePiece(b->returnPiece(x, y).getRep(), x, y);
				b->removePiece(x, y);
			}
			b->placePiece(p, x, y);
			b->removePiece(p.getX(), p.getY());
		}
		else
			return false;

		return true;

	}

	bool legalMove(Board* b, Player* opp, Rook p, int x, int y) {
		if (!p.move(x, y)) {
			return false;
		}
		else if (b->clearPath(p, p.getX(), p.getY(), x, y)) {
			if (b->oppPieces(p, x, y)) {
				this->addToScore(b->pieceScore(x, y));
				opp->hidePiece(b->returnPiece(x, y).getRep(), x, y);
				b->removePiece(x, y);
			}
			b->placePiece(p, x, y);
			b->removePiece(p.getX(), p.getY());
		}
		else
			return false;

		return true;

	}

	bool legalMove(Board* b, Player* opp, Queen p, int x, int y) {
		if (!p.move(x, y)) {
			return false;
		}
		else if (b->clearPath(p, p.getX(), p.getY(), x, y)) {
			if (b->oppPieces(p, x, y)) {
				this->addToScore(b->pieceScore(x, y));
				opp->hidePiece(b->returnPiece(x, y).getRep(), x, y);
				b->removePiece(x, y);
			}
			b->placePiece(p, x, y);
			b->removePiece(p.getX(), p.getY());
		}
		else
			return false;

		return true;

	}

	bool legalMove(Board* b, Player* opp, King p, int x, int y) {
		if (!p.move(x, y)) {
			if(b->clearCastle(x, y))
				if (p.castle(rook, this->getColour(), x, y)){
					b->placePiece(p, x, y);
					b->removePiece(p.getX(), p.getY());
					if (x == 2){
						b->placePiece(rook[1], x + 1, y);
						b->removePiece(rook[1].getX(), rook[1].getY());
						rook[1].setCord(x + 1, y);
					}
					else {
						b->placePiece(rook[0], x - 1, y);
						b->removePiece(rook[0].getX(), rook[0].getY());
						rook[0].setCord(x - 1, y);
					}

			}else
				return false;
		}
		else if (b->clearPath(p, p.getX(), p.getY(), x, y)) {
			if (b->oppPieces(p, x, y)) {
				this->addToScore(b->pieceScore(x, y));
				opp->hidePiece(b->returnPiece(x, y).getRep(), x, y);
				b->removePiece(x, y);
			}
			b->placePiece(p, x, y);
			b->removePiece(p.getX(), p.getY());
		}
		else
			return false;

		return true;

	}

	void hidePiece(char p, int x, int y) {
		switch (toupper(p)) {
		case 'P':
			for (int i = 0; i < 8; i++)
				if (pawn[i].getX() == x && pawn[i].getY()== y)
					pawn[i].isCaptured();
			break;
		case 'B':
			for (int i = 0; i < 2; i++)
				if (bishop[i].getX() == x && bishop[i].getY() == y)
					bishop[i].isCaptured();

			break;
		case 'N':
			for (int i = 0; i < 2; i++)
				if (knight[i].getX() == x && knight[i].getY() == y)
					knight[i].isCaptured();
			break;
		case 'R':
			for (int i = 0; i < 2; i++)
				if (rook[i].getX() == x && rook[i].getY() == y)
					rook[i].isCaptured();
			break;
		case 'Q':
			if (queen.getX() == x && queen.getY() == y)
				queen.isCaptured();
			break;
		case 'K':
			cout << colour << "'s king captured" << endl;
			break;
		}
	}
};