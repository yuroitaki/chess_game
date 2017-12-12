#ifndef ROOK_H
#define ROOK_H

#include "royal_rider.h"

using namespace std;

class Rook: public RoyalRider{
 public:
  Rook(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Rook();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file) override;
  void build_possible_moves() override;
};

#endif
