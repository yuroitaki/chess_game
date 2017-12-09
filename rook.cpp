#include <iostream>
#include <string>

#include "rook.h"

Rook::Rook(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

Rook::~Rook(){
  cout << "Rook is deleted!" << " ";
}
