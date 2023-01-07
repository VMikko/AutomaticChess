#pragma once
#include "Pieces.h"
#include "AccelStepper.h"

// to get the absolute of the value
long ab(long x) {
  if (x < 0 ) {
    return ((-1)*x);
  } else {
    return x;
  }
}


long xStep; // Not in use
long yStep; // Not in use
long stepsSquare = 205;  // How many steps a single square is in the physical chessboard

// correct pins -- not in use
bool readX() {
  return digitalRead(12) != 0;
}
bool readY() {
  return digitalRead(13) != 0;
}

// For controlling the steppers, check the documentation of the AccelStepper library
AccelStepper stepperX(1, 3, 2);
AccelStepper stepperY(1, 5, 4);

// To get the correct speed for the steppers according to the goal coordinate
long nopeus(AccelStepper stepper, long x) {
  if (x - stepper.currentPosition() > 0 ) {
    return 500;
  } else {
    return -500;
  }
}
// exactly the same as above, could be removed
long nopeusY(AccelStepper stepper, long x) {
  if (x - stepper.currentPosition() > 0 ) {
    return 500;
  } else {
    return -500;
  }
}

// Move the piece in a straight line in the x-axis
void straightX(AccelStepper stepper, long x) {
  long xDiff =(xStep + x*stepsSquare) ;
  if (xDiff < 0 ) {
    stepper.setSpeed(500);
  } else {
    stepper.setSpeed(-500);
  }
  while (-x*stepsSquare != xStep) {
    delay(2);
    if (stepper.runSpeed()) {
      if (xDiff > 0 ) {
        xStep--;
      }   else {
        xStep++;
    }
  }
  }
  Serial.print(xStep);
}

// Move the piece in a straight line in the y-axis
void straightY(AccelStepper stepper, long y) {
  long yDiff = y*stepsSquare - yStep;
  if (yDiff > 0 ) {
    stepper.setSpeed(500);
  } else {
    stepper.setSpeed(-500); }
  while (y*stepsSquare != yStep) {
    delay(2);
    if (stepper.runSpeed()) {
      if (yDiff > 0 ) {
        yStep++;
      } else {
        yStep--;
    }
  }
  }
}

//Move the piece in a diagonal line -- assumes that the difference in the x- and y-coordinates is the same - as in moves the piece the same amount in x- and y-axis
void diagonal(AccelStepper stepperX, AccelStepper stepperY, long x, long y) {
  long yDiff = y*stepsSquare - yStep;
  if (yDiff > 0 ) {
    stepperY.setSpeed(500);
  } else {
    stepperY.setSpeed(-500); }

  long xDiff =(xStep + x*stepsSquare) ;
  if (xDiff < 0 ) {
    stepperX.setSpeed(500);
  } else {
    stepperX.setSpeed(-500);
  }

  while (y*stepsSquare != yStep) {
    delay(2);
    if (stepperY.runSpeed()) {
      if (yDiff > 0 ) {
        yStep++;
      } else {
        yStep--;
      }
      }
      if (stepperX.runSpeed()) {
      if (xDiff > 0 ) {
        xStep--;
      }   else {
        xStep++;
    }
  }
  }
}

/* Any other move that is not a straight line or a diagonal is moved with this
* First moves the piece to the corner of the square
* Then moves the piece along the edges of the squares to the correct square's corner
* Then moves the piece back into the middle of the square */
void otherMove(AccelStepper stepperX, AccelStepper stepperY, long x, int y) {
  int i = 0;
  stepperX.setSpeed(-500);
  stepperY.setSpeed(500);
  while (i < 102) {
    if (stepperX.runSpeed()) {
      stepperY.runSpeed();
      i++;
    }
  }
  straightX(stepperX, (x));
  straightY(stepperY, (y));

  i = 0;
  stepperX.setSpeed(500);
  stepperY.setSpeed(-500);
  while (i < 102) {
    if (stepperX.runSpeed()) {
      stepperY.runSpeed();
      i++;
    }
  }


}

// this can prolly be removed, doubt that its used in arduino (was in c++)
using namespace std;


// The class for the simulation chessboard
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


/* Sets up the board, the whites are at the bottom (in the rows 6 & 7), blacks at the top (rows 0 & 1)
* This doesnt do a complete reset, any piece thats in the middle of the board does not get removed
* Then physically moves the rotors to the 'beginning' position (square (0,0)), the upper left corner */
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

  
  stepperX.setSpeed(500);
  while (!readX()) {
    stepperX.runSpeed();
  }
  xStep = 0;
  stepperY.setSpeed(-500);
  while (!readY()) {
    stepperY.runSpeed();
  }
  yStep = 0;

  stepperX.setSpeed(-500);
  int i = 0;
  while (i < 170) {
    if (stepperX.runSpeed()) {
      i++;
    }
  }
  i = 0;
  stepperY.setSpeed(500);
  while ( i <200) {
    if (stepperY.runSpeed()) {
      i++;
    }
  }
  
}


// Prints out the board in the serial monitor
void Board::printBoard() {
  Serial.print("\n Board \n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece piece = (board[i][j].getPiece());
      Serial.print(piece);
      Serial.print(" ");
		}
		Serial.print("\n");
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

  Serial.print("Where to move (x-coordinate):\n");
	x2 = input();
  Serial.print("Where to move (y-coordinate):\n");
  y2 = input();

	if (x2-48 >= 0 && x2-48 <= 7 && y2-48 >= 0 && y2-48 <= 7) {
		// does nothing,	
	}
	else {
    Serial.print("Incorrect coordinates.\n");
		return false;
	}
	// if the player chooses to move to the same square where the piece is, the piece just gets removed, fix
	Square &p1 = board[y1-48][x1-48];
	Square &p2 = board[y2-48][x2-48];
	p2.setPieceColor(p1.getPiece(), p1.getColor());	
	p1.removePiece();

  if (ab(x2 - x) == ab(y2 -y)) {
    diagonal(stepperX, stepperY, (x2-48), (y2-48));
  } else if (x == x2 ||y == y2) {
    straightX(stepperX, (x2-48));
    straightY(stepperY, (y2-48));
    }
    else {
      otherMove(stepperX, stepperY, (x2-48), (y2-48));
    }
  

	return true;	
}



//Tries to select a piece for the next move, takes the color of the current player as the parameter
bool Board::tryMove(Color color) {
	char x;
	char y;
	int apu;
	char n;

  Serial.print("Select an x-coordinate(0-7):\n");
	x = input();

	if (x < 48  || x > 55 ) {
    Serial.print("Invalid coordinate (or not int)\n");
		return false;
	}
  Serial.print("Select a y-coordinate(0-7):\n");
	y = input();
	if (y < 48 || y > 55) {
    Serial.print("Invalid coordinate (or not int)\n");
		return false;
	}
  // Currently doesn't care about the color of the chosen piece, remove the comment characters from the line below to take the color into account
	if (board[y-48][x-48].getPiece() != Empty /*&& board[y-48][x-48].getColor() == color*/) {
    Serial.print("Valid piece!\n");
		// make this return bool value of the move -- not needed
    straightX(stepperX, (x-48));
    straightY(stepperY, (y-48));
		while (!move(x, y)) {
		}
	}
	else {
    Serial.print("Either an empty square, or not your piece.\n");
		return false;
	}
	return true;
}
