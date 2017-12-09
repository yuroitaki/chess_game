#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

using namespace std;

class Pawn: public ChessPiece{
 public:
  Pawn(string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Pawn();
  
};

#endif
