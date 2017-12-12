#ifndef ROYAL_RIDER_H
#define ROYAL_RIDER_H

#include "ChessPiece.h"

using namespace std;

class RoyalRider: public ChessPiece{
 public:
  RoyalRider(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~RoyalRider();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file);
  void chess_rule(vector<int>& rank_vec, vector<int>& file_vec);
  bool check_unwanted_index(int index, vector<int>& unwanted_index);
  virtual void build_possible_moves();
};

#endif
