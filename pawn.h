#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

using namespace std;

class Pawn: public ChessPiece{
 public:
  Pawn(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr);
  ~Pawn();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file) override;
  void chess_rule();
  void build_possible_moves() override;
};

#endif
