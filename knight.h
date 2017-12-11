#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

using namespace std;

class Knight: public ChessPiece{
 public:
  Knight(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Knight();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file) override;
  void chess_rule();
};

#endif
