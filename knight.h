#ifndef KNIGHT_H
#define KNIGHT_H

#include "royal_infantry.h"

using namespace std;

class Knight: public RoyalInfantry{
 public:
  Knight(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Knight();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file) override;
  void build_possible_moves() override;
};

#endif
