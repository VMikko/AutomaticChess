#include <string>

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}
char i = "";

void loop() {
  // put your main code here, to run repeatedly:
  while (i = "") {
    i = Serial.readString()(0);
  }
  if (i == "m") {
    Serial.println(multiply(1,5));
  } else if (i == "s") {
    Serial.println(sum(1,7))
  }

}


char board[8][8] = {
  {r, h, b, q, k, b, h, r}
  {p, p, p, p, p, p, p, p}
  { ,  ,  ,  ,  ,  ,  ,  }
  { ,  ,  ,  ,  ,  ,  ,  }
  { ,  ,  ,  ,  ,  ,  ,  }
  { ,  ,  ,  ,  ,  ,  ,  }
  {p, p, p, p, p, p, p, p}
  [r, h, b, q, k, b, h, r]
};
// p = pawn, b = bishop, r = rook, h = horse(knight), q = queen, k = king 

