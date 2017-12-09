#include <iostream>
#include <string>

#include "pawn.h"

Pawn::Pawn(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

Pawn::~Pawn(){
  cout << "Pawn is deleted!" << " ";
}
