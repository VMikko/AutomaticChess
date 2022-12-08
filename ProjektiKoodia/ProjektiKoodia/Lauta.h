#pragma once
#include "nappulat.h"
#include <string>
#include <iostream>
using namespace std;

class Board {
	// constructor, at the beginning the board is full of empty squares
	Square board[8][8]{
		{Square(), Square(),Square(),Square(),Square(),Square(),Square(),Square()},
		{Square(), Square(),Square(),Square(),Square(),Square(),Square(),Square()},
		{Square(), Square(),Square(),Square(),Square(),Square(),Square(),Square()},
		{Square(), Square(),Square(),Square(),Square(),Square(),Square(),Square()},
		{Square(), Square(),Square(),Square(),Square(),Square(),Square(),Square()},
		{Square(), Square(),Square(),Square(),Square(),Square(),Square(),Square()},
		{Square(), Square(),Square(),Square(),Square(),Square(),Square(),Square()},
		{Square(), Square(),Square(),Square(),Square(),Square(),Square(),Square()}
	};
public:
	// the methods that the class has, they're defined below
	void printBoard();
	void setUp();
	bool tryMove(Color color);
	bool move(int x, int y);

};


// Sets up the board, the whites are at the bottom (in the rows 6 & 7), blacks at the top (rows 0 & 1)
// This doesnt do a complete reset, any piece thats in the middle of the board does not get removed
void Board::setUp() {
	//First the rooks
	for (int i = 0; i < 8; i++) {
		board[1][i].setPieceColor(Pawn, Black);
		board[6][i].setPieceColor(Pawn, White);
	}
	// The rest
	board[0][0].setPieceColor(Rook, Black);
	board[0][1].setPieceColor(Knight, Black);
	board[0][2].setPieceColor(Bishop, Black);
	board[0][3].setPieceColor(Queen, Black);
	board[0][4].setPieceColor(King, Black);
	board[0][5].setPieceColor(Bishop, Black);
	board[0][6].setPieceColor(Knight, Black);
	board[0][7].setPieceColor(Rook, Black);

	board[7][0].setPieceColor(Rook, White);
	board[7][1].setPieceColor(Knight, White);
	board[7][2].setPieceColor(Bishop, White);
	board[7][3].setPieceColor(Queen, White);
	board[7][4].setPieceColor(King, White);
	board[7][5].setPieceColor(Bishop, White);
	board[7][6].setPieceColor(Knight, White);
	board[7][7].setPieceColor(Rook, White);
}


// Prints out the board
void Board::printBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			string piece = pieceNames.at(board[i][j].getPiece());
			cout << piece << " ";
		}
		cout << "\n";
	}
}


bool Board::move(int x, int y) {
	int x1;
	int y1;
	x1 = x;
	y1 = y;
	int x2;
	int y2;
	int i;

	cout << "Where to move (x-coordinate) - dont you dare type non-integers\n";
	cin >> i;
	x2 = i;
	cout << "Where to move (y-coordinate)\n";
	cin >> i;
	y2 = i;

	if (x2 >= 0 && x2 <= 7 && y2 >= 0 && y2 <= 7) {
		// does nothing,	
	}
	else {
		cout << "Incorrect coordinates - type better\n";
		return false;
	}
	// if the player chooses to move to the same square where the piece is, the piece just gets removed, fix
	Square &p1 = board[y1][x1];
	Square &p2 = board[y2][x2];
	p2.setPieceColor(p1.getPiece(), p1.getColor());	
	p1.removePiece();
		
	return true;
	
}


//Tries to select a piece for the next move
bool Board::tryMove(Color color) {
	int x;
	int y;
	int apu;
	string n;

	cout << "Select an x-coordinate(0-7)\n";
	cin >> x;
	if (cin.fail() || x < 0 || x >7) {
		cout << "Invalid coordinate (or not int)\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	cout << "Select an y-coordinate(0-7)\n";
	cin >> y;
	if (cin.fail() || y < 0 || y > 7) {
		cout << "Invalid coordinate (or not int)\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	if (board[y][x].getPiece() != Empty && board[y][x].getColor() == color) {
		cout << "Valid piece!\n";
		// make this return bool value of the move
		while (!move(x, y)) {
		}
	}
	else {
		cout << "Either an empty square, or not your piece.\n";
		return false;
	}
	return true;
}

/*
int* findSquare(int x, int y) {

}*/