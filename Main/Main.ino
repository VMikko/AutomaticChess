#include "Pieces.h"
#include "Board.h"
//#include <AccelStepper.h>
#include <MultiStepper.h>

const int magnetPinPos = 10;  // Not in use
const int magnetPinNeg = 11;  // Not in use
const int nappiX = 8;
const int nappiY = 9;
/*
const int stepPinX = 3;
const int stepDirX = 4;
const int stepPinY = 5;
const int stepDirY = 6;
not in use */




void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(nappiX, INPUT);
  pinMode(nappiY, INPUT);
  pinMode(magnetPinPos, OUTPUT); // not in use
  pinMode(magnetPinNeg, OUTPUT); // not in use

  // x-coordinate stepper
  stepperX.setMaxSpeed(500);
  // y-coordinate stepper
  stepperY.setMaxSpeed(500);

}

void loop() {
  // sets up the board
    Serial.print("Ready\n");
    Board lauta;
    lauta.setUp();
    // Keeps asking the user for moves.
    // After two moves the user gets a choice to either reset the game to the start (ending the while-loop) or continue with the same game
    while (true) {
        char in;
        lauta.printBoard();
        Serial.print("White moves \n");
        while (!lauta.tryMove(White)) {
          Serial.print("Still white\n");
        }  
        Serial.print("Black moves\n");
        lauta.printBoard();
        while (!lauta.tryMove(Black)) {
          Serial.print("Still black\n");
        }
        lauta.printBoard();

        Serial.print("Continue? (n for no, anything else for yes)\n");
        in = input();
        if (in == 'n') {
            Serial.print("__________________\n");
            Serial.print("Game ended from user input \n\n");
            break;
        }
    }
}
