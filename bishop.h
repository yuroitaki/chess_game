#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

using namespace std;

class Bishop: public ChessPiece{
 public:
  Bishop(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~Bishop();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file) override;
};

#endif
