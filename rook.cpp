#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "rook.h"

Rook::Rook(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr):RoyalRider(name,fig,id,init_rank,init_file,bod_ptr,chess_b_ptr){}

Rook::~Rook(){}

bool Rook::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){

  vector<int> rank_move = {1,0,0,-1};     //basic moves
  vector<int> file_move = {0,1,-1,0};
  
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


void Rook::build_possible_moves(){
  
  vector<int> rank_move = {1,0,0,-1};
  vector<int> file_move = {0,1,-1,0};

  chess_rule(rank_move,file_move);

  RoyalRider::build_possible_moves();
}
