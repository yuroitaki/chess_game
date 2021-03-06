#ifndef ROYAL_INFANTRY_H
#define ROYAL_INFANTRY_H

#include "ChessPiece.h"

using namespace std;

class RoyalInfantry: public ChessPiece{
 public:
  RoyalInfantry(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr);
  ~RoyalInfantry();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file);
  void chess_rule(int* buff_rank_arr, int* buff_file_arr);
  void build_possible_moves();
};

#endif
