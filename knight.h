#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

using namespace std;

class Knight: public ChessPiece{
 public:
  Knight(string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Knight();
  
};

#endif
