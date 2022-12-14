#include "nappulat.h"
#include "lauta.h"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
    Board lauta;
    lauta.setUp();

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
