#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

using namespace std;

class Queen: public ChessPiece{
 public:
  Queen(string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Queen();
  
};

#endif