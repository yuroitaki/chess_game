#include <iostream>
#include <string>
#include <vector>

#include "queen.h"

Queen::Queen(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

Queen::~Queen(){
  cout << "Queen is deleted!" << " ";
}

bool Queen::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){
  
  int r_top = current_rank - 1;
  int r_mid = current_rank;
  int r_low = current_rank + 1;
  int f_left = current_file - 1;
  int f_mid = current_file;
  int f_right = current_file + 1;
  
  for(int i=0;i<3;i++){
    possible_rank.push_back(r_top);
    possible_rank.push_back(r_low);
    possible_file.push_back(f_left);
    if(i<2)
      possible_rank.push_back(r_mid);
  }
  for(int i=0;i<3;i++){
    possible_file.push_back(f_right);
    if(i<2)
      possible_file.push_back(f_mid);
  }
  ChessPiece::check_chess_move(source,desti,d_rank,d_file);
  verify_desti(d_rank,d_file,desti);
  possible_rank.clear();
  possible_file.clear();
  return true;
}
