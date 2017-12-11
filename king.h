#ifndef KING_H
#define KING_H

#include "royal_infantry.h"

using namespace std;

class King: public RoyalInfantry{
 public:
  King(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~King();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file) override;
};

#endif
