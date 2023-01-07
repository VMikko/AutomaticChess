#pragma once

// A way to get user input when needed
char input() {
  char input;
  char apu;
  while (!Serial.available()) {
    delay(50);
  }
  input = Serial.read();
  delay(50);
  Serial.println(input);
  while (Serial.available() > 0) {
    char apu = Serial.read();
  }
  Serial.flush();
  return input;
}
//using namespace std;

// Pieces and colors can only be these specific values
enum Piece {Empty, Pawn, Bishop, Rook, Knight, Queen, King};
enum Color {None, White, Black};


//A singular square in the chessboard simulation
class Square {
public:
    Piece piece;
    Color color;

    // default constructor, every Square that isn't given any parameters will be like this
    Square() {
        piece = Empty;
        color = None;
    }
    // Methods for manipulating the square's piece and color
    void setPieceColor(Piece p, Color c) {
        piece = p;
        color = c;
    }
    Piece getPiece() {
        return piece;
    }
    // useless
    void setColor(Color c) {
        color = c;
    }
    Color getColor() {
        return color;
    }
    void removePiece() {
        piece = Empty;
        color = None;
        // TODO: in arduino make the piece go off the board, if there is a piece there that is
    }

};