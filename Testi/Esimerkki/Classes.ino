#include <string>

class piece {
  virtual bool alive = 0;
};

class white {
  // moves up
  public:
    int direction = -1;

};

class black {
  // Moves down
  public:
    int direction = 1;
};



class pawn { 
};

class bishop {

};

class rook {

};

// 
class knight {

};

class queen {

};

class king {
  
}
