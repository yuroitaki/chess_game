#include <iostream>
#include <string>

#include "king.h"

King::King(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

King::~King(){
  cout << "King is deleted!" << " ";
}
