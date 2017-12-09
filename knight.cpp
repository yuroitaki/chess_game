#include <iostream>
#include <string>

#include "knight.h"

Knight::Knight(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

Knight::~Knight(){
  cout << "Knight is deleted!" << " ";
}
