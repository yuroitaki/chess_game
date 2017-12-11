#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

using namespace std;

class Queen: public ChessPiece{
 public:
  Queen(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Queen();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file) override;
};

#endif
