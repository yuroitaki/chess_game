#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "knight.h"

Knight::Knight(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr):RoyalInfantry(name,fig,id,init_rank,init_file,bod_ptr,chess_b_ptr){}

 Knight::~Knight(){}

bool Knight::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){
   
  int len_arr = 8;
  int buff_rank_arr[len_arr] = {-2,-1,1,2,-2,-1,1,2};     //basic moves
  int buff_file_arr[len_arr] = {-1,-2,-2,-1,1,2,2,1};
  int* rank_ptr = buff_rank_arr;
  int* file_ptr = buff_file_arr;
  
  chess_rule(rank_ptr,file_ptr);
  
  if(!RoyalInfantry::check_chess_move(source,desti,d_rank,d_file)){
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


void Knight::build_possible_moves(){
  
  int len_arr = 8;
  int buff_rank_arr[len_arr] = {-2,-1,1,2,-2,-1,1,2};
  int buff_file_arr[len_arr] = {-1,-2,-2,-1,1,2,2,1};
  int* rank_ptr = buff_rank_arr;
  int* file_ptr = buff_file_arr;
  
  chess_rule(rank_ptr,file_ptr);
  RoyalInfantry::build_possible_moves();
}
