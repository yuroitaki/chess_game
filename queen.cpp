#include <iostream>
#include <string>

#include "queen.h"

Queen::Queen(string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(fig,id,init_rank,init_file,bod_ptr){
}

Queen::~Queen(){
  cout << "Queen is deleted!" << " ";
}
