#include <iostream>
#include <string>

#include "bishop.h"

Bishop::Bishop(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

Bishop::~Bishop(){
  cout << "Bishop is deleted!" << " ";
}
