#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

using namespace std;

class Rook: public ChessPiece{
 public:
  Rook(string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Rook();
  
};

#endif
