#include <iostream>
#include <string>

#include "knight.h"

Knight::Knight(string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(fig,id,init_rank,init_file,bod_ptr){
}

Knight::~Knight(){
  cout << "Knight is deleted!" << " ";
}
