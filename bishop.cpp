#include <iostream>
#include <string>
#include <vector>

#include "bishop.h"

Bishop::Bishop(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):RoyalRider(name,fig,id,init_rank,init_file,bod_ptr){
}

Bishop::~Bishop(){
  cout << "Bishop is deleted!" << " ";
}

bool Bishop::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){

  vector<int> rank_move = {1,-1,1,-1};
  vector<int> file_move = {1,1,-1,-1};

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

void Bishop::build_possible_moves(){
  
  vector<int> rank_move = {1,-1,1,-1};
  vector<int> file_move = {1,1,-1,-1};
  
  chess_rule(rank_move,file_move);

  RoyalRider::build_possible_moves();
}
