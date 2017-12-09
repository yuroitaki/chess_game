#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

using namespace std;

class King: public ChessPiece{
 public:
  King(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr);
  ~King();
  
};

#endif
