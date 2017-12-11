#include <iostream>
#include <string>
#include <vector>

#include "queen.h"

Queen::Queen(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):RoyalRider(name,fig,id,init_rank,init_file,bod_ptr){
}

Queen::~Queen(){
  cout << "Queen is deleted!" << " ";
}

bool Queen::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){

  vector<int> rank_move = {1,-1,1,-1,1,0,0,-1};
  vector<int> file_move = {1,1,-1,-1,0,1,-1,0};

  chess_rule(rank_move,file_move);
  
  if(!RoyalRider::check_chess_move(source,desti,d_rank,d_file)){
    possible_rank.clear();
    possible_file.clear();
    return false;
  }
  if(!verify_desti(d_rank,d_file,desti)){
    possible_rank.clear();
    possible_file.clear();
    return false;
  }
  possible_rank.clear();
  possible_file.clear();
  return true;
}
